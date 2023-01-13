`timescale 1ns / 1ps
/*Controller模块：解码部分原理同实验二，此处输出控制信号时不能直接输出8bit sigs，而是单独输出。
    本模块不仅负责解码，还需要操控每一级流水线和流水线寄存器之间的数据进出。下为各信号输出位置：
    jump、branch：Main Decoder后
    alucontrol、alusrc、regdst、regwriteE、memtoregE：流水线寄存器DE后
    memwrite、data_ram_ena、memtoregM、regwriteM：流水寄存器EM后
    regwrite、memtoreg：流水寄存器MW后
    其中regwriteE,memtoregM,regwriteM,memtoregE均为传入datapath中的hazard模块，处理冒险情况
*/
module controller(
    input clka,rst,
    input wire [31:0] instr,
    output wire jump,branch,alusrc,memwrite,memetoreg,regwrite,regdst,data_ram_ena,regwriteE,memtoregM,
    output wire regwriteM,  //regwriteE,memtoregM,regwriteM,memtoregE传入datapath中的hazard需要
    output wire memtoregE,
    output wire [2:0] alucontrol
    );
//根据instr[31:26]和instr[5:0]解码
    wire [1:0] aluop;       //Main Decode输出的aluop信号，传入ALU Decoder
    wire [7:0] sigsD;       //Main Decode输出的8bit控制信号
    //main_dec 实例化
    main_dec Main_Decoder(.op(instr[31:26]),.sigs(sigsD),.aluop(aluop));
    wire [2:0] alucontrolD; //ALU Decoder输出的ALU控制信号，传入流水线寄存器
    //alu_dec 实例化
    alu_dec ALU_Control(.funct(instr[5:0]),.op(aluop),.alucontrol(alucontrolD));
    assign jump = sigsD[7]; //jump和branch信号不用继续传输，直接传给下一条指令以减少控制冒险
    assign branch = sigsD[3];
    
//流水线寄存器DE间的数据进出：{regwrite,regdst,alusrc,memwrite,memetoreg,data_ram_ena}和ALUControlD
    wire [5:0] sigsE;       //{regwrite,regdst,alusrc,memwrite,memetoreg,data_ram_ena}
    wire [2:0] alucontrolE; //从流水线寄存器DE读出的ALU控制信号
    floprc #(6) r1E(.clk(clka),.rst(rst),.clear(1'b0),.d({sigsD[6:4],sigsD[2:0]}),.q(sigsE));
    floprc #(3) r2E(.clk(clka),.rst(rst),.clear(1'b0),.d(alucontrolD),.q(alucontrolE));
    assign regdst = sigsE[4];
    assign alusrc = sigsE[3];
    assign alucontrol = alucontrolE;
    assign memtoregE = sigsE[1];
    assign regwriteE = sigsE[5];
    
//流水线寄存器EM间的数据进出：{regwrite,memwrite,memetoreg,data_ram_ena}
    wire [3:0] sigsM;
    floprc #(4) r1M(.clk(clka),.rst(rst),.clear(1'b0),.d({sigsE[5],sigsE[2:0]}),.q(sigsM));
    assign memwrite = sigsM[2];
    assign data_ram_ena = sigsM[0];
    assign regwriteM = sigsM[3];  //传入datapath中的hazard需要
    assign memtoregM = sigsM[1]; //传入datapath中的hazard需要
    
//流水线寄存器MW间的数据进出：{regwrite,memwrite,memetoreg}
    wire [1:0] sigsW;
    floprc #(2) r1W(.clk(clka),.rst(rst),.clear(1'b0),.d({sigsM[3],sigsM[1]}),.q(sigsW));
    assign regwrite = sigsW[1];
    assign memetoreg = sigsW[0];

endmodule