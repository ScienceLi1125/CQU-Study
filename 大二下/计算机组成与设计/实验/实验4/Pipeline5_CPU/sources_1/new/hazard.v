`timescale 1ns / 1ps
/*冒险解决：（数据冒险）数据前推+流水线暂停、（控制冒险）提前判断分支导致的数据前推、流水线暂停
    其中流水线暂停时需要清空下一级流水线。提前判断分支放在datapath里实现，并不在hazard中实现
*/
module hazard(
    input wire rst,
    input wire [4:0] rsD,       //instr2[25:21]（同一时刻rsD和rsE对应先后两条指令的rs字段，并不相同）
    input wire [4:0] rtD,       //instr2[20:15]
    input wire [4:0] rsE,       //instr1[25:21]
    input wire [4:0] rtE,       //instr1[20:15]
    input wire regwriteE,       //寄存器堆的写使能信号（E、M、W表示excute、memory和writeback阶段）
    input wire regwriteM,  
    input wire regwriteW,  
    input wire memtoregE,       //判断写回寄存器堆的数据是sw的ReadData(0)还是R的ALUOut(1)
    input wire memtoregM,
    input wire branchD,         //提前判断分支
    input wire [4:0] writeregE, //寄存器堆的写地址，连接wa3W
    input wire [4:0] writeregM,
    input wire [4:0] writeregW,
    output [1:0] forwordAE,     //在excute阶段控制mux3选择SrcA（数据冒险）
    output [1:0] forwordBE,     //在excute阶段控制mux3选择SrcB
    output [1:0] forwordAD,     //在decode阶段控制二选一选择regfile rd1出来的数据（控制冒险下的数据冒险）
    output [1:0] forwordBD,     //在decode阶段控制二选一选择regfile rd2出来的数据
    output reg stallF,          //instr fetch级暂停
    output reg stallD,          //decoder暂停
    output reg flushE           //excute读到的流水线需要清空
    );
//数据前推解决R指令和前两条lw指令的数据冒险
    /*ALU端口SrcAE的数据可能来自：（注意判断reE!=0，否则读保留寄存器直接输出）
        寄存器堆（无冒险情况下）：forwordAE=00、SrcAE=RsD
        数据存储器(lw的数据冒险)：forwordAE=01、SrcAE=ResultW（lw指令写回寄存器堆在MEM阶段，其后第二条指令如需要该数据会受影响）
        ALUOut（ALU运算的数据冒险）：forwordAE=10、SrcAE=ALUOutM（R型指令写回寄存器堆在WB阶段，其后一条指令如需要该数据都会受影响）
    */
    assign forwordAE = ((rsE != 5'b0) & (rsE == writeregM) & regwriteM) ? 2'b10:    //前一条指令是R型，直接将ALUOut传回
                       ((rsE != 5'b0) & (rsE == writeregW) & regwriteW) ? 2'b01:    //前两条指令是lw
                        2'b00;
    assign forwordBE = ((rtE != 5'b0) & (rtE == writeregM) & regwriteM) ? 2'b10:    //SrcBE同SrcAE
                       ((rtE != 5'b0) & (rtE == writeregW) & regwriteW) ? 2'b01:
                        2'b00;
//提前判断分支解决beq后2、3条指令的控制冒险时出现的数据冒险
    assign forwordAD = ((rsD != 5'b0) & (rsD == writeregE) & regwriteE);            //前一条指令要写回寄存器堆且该数据被beq指令所用
    assign forwordBD = ((rtD != 5'b0) & (rtD == writeregE) & regwriteE);
//流水线暂停解决lw后一条指令需要用寄存器堆数据带来的数据冒险、beq需要用前一条指令写回寄存器堆的数据
    /*lw指令写入寄存器堆的地址为rt，因此下一条指令若要用到rt则需要暂停，即rsD==rtE或rtD==rtE
      beq指令需要rs、rt号寄存器的数据，若上一条指令要写到该寄存器，则需要暂停流水线
    */
    wire lwstall,branch_stall;                                      //流水线暂停信号
    assign lwstall = (((rsD == rtE) | (rtD == rtE)) & memtoregE);   //判断前一条指令需要对寄存器堆写入(memturegE)并且写入地址rtE与被当前指令用到
    assign branch_stall=( branchD&regwriteE&((writeregE==rsD)|(writeregE==rtD)) )   //当前指令为branch、上一条指令要写寄存器堆且写的数据当前要用
                       |( branchD&memtoregM&((writeregM==rsD)|(writeregM==rtD)) );  //当前指令为branch、上2条指令要写寄存器堆且写的数据当前要用
    always @(*)begin
        stallF = rst? 1'b0 : (lwstall | branch_stall);      //若被重置则全部清零
        stallD = rst? 1'b0 : (lwstall | branch_stall);      //lw带来的数据冒险或提前判断分支带来的数据冒险都可以暂停流水线
        flushE = rst? 1'b0 : (lwstall | branch_stall);      //lw/beq下一条已经执行的需要清空
    end

endmodule

