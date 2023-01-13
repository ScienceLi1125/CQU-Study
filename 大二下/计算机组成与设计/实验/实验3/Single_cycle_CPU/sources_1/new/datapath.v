`timescale 1ns / 1ps
/*数据通路模块：将Controller解码的控制信号传入datapath（Controller输出的memwrite传给Data memory，其他
的均传入datapath），并接收Data memory输入的data和Instruction memory输入的IR，输出ALU计算结果、写回数
据、pc信号以及zero信号
    datapath模块包含许多模块：主要可以分为PC和Data两个部分：
        PC部分：PC->PC+4->判断branch(IR[15:0]<<2+PC+4)->判断jump({PCPlus4[31:28],IR[25:0]<<2})->更新PC
        Data部分：IR-寄存器堆->RD1、RD2(与SignImm选择)-ALU->ALUReult、WriteData-DataMem->ReadData、ALUResult->Result
*/

module datapath(
    input clk,rst,
    input[2:0] aluctrl,
    input memtoreg,alusrc,regdst,regwrite,pcsrc,jump,   //pcsrc=branch&zero，从外部传入
    input[31:0] readdata,               //lw指令从Data memory读出的指令
    input[31:0] IR,
    output[31:0] aluresult,
    output[31:0] writedata,
    output[31:0] pc_out,
    output zero
    );
    //PC部分
    wire[31:0] PC_1,PC_2,PC,PCPlus4;    //PC_1为判断branch后的地址信号，PC_2为判断jump后的地址信号
    assign pc_out=PC;
    pc gate1(clk,rst,PC_2,PC);          //PC模块
    adder gate2(PC,32'h00000004,PCPlus4);      //PC+4
    
    wire[31:0] SignImm;
    wire[15:0] tmp;
    assign tmp=IR[15:0];
    signext gate3(tmp,SignImm);    //lw、sw、addi、beq指令需要对IR[15:0]进行扩展
    
    wire[31:0] PCBranch_in;
    wire[31:0] PCBranch_out;
    sl2 gate4(SignImm,PCBranch_in);
    adder gate5(PCBranch_in,PCPlus4,PCBranch_out);      //计算branch跳转指令
    
    mux2 gate6(PCPlus4,PCBranch_out,pcsrc,PC_1);        //判断是否执行branch
    mux2 gate7(PC_1,{PCPlus4[31:28],IR[25:0],2'b00},jump,PC_2);    //判断是否执行jump
    
    //Data部分
    wire[4:0] WriteReg;                 //写寄存器号
    wire[31:0] Result;                  //写回寄存器数据
    wire[31:0] RD1,RD2;                 //寄存器堆读出数据
    assign writedata=RD2;
    mux2 #(5) gate8(IR[20:16],IR[15:11],regdst,WriteReg);    //判断写寄存器号
    regfile gate9(clk,regwrite,IR[25:21],IR[20:16],WriteReg,Result,RD1,RD2);
    
    wire[31:0] SrcB,ALUResult;
    assign aluresult=ALUResult;
    mux2 gate10(RD2,SignImm,alusrc,SrcB);               //判断RD2 or SignImm
    alu gate11(aluctrl,RD1,SrcB,ALUResult,zero);        //ALU运算
    
    mux2 gate12(ALUResult,readdata,memtoreg,Result);    //判断写回寄存器堆的是ALU的计算结果 or lw读取的data
        
endmodule
