`timescale 1ns / 1ps
/*MIPS指令处理模块：接收clk、rst、指令和数据
注意：controller为纯组合逻辑，不包含任何存储功能，datapath为时序逻辑，需要时钟信号控制。因为本实
    验是单周期CPU，将datapath视为一个整体(由同一个时钟信号控制)，指令寄存器取指令、datapath数据传
    输、Data memory存取数据都需要在同一个时钟周期内完成。因此Instruction memory和Data memory均采
    用下降沿触发，Datapath采用上升沿触发。当clk上升沿到来时，Datapath将传入的IR和各控制信号进行运
    算，输出PC、WriteData和ALUOut；clk下降沿来临时，Data memory将WriteData写回(sw)/ALUOut取出(lw)/
    ALUOut传出(R)，同时Instruction memory取指令传出；等到下一个clk上升沿来临，Datapath接收传回的
    ReadData(lw)/ALUOut(R)写回寄存器堆。但此处还会有一个冲突，即下一条指令需要用到上一条写回的寄
    存器堆内数据，本实验暂时不考虑此冲突。    
*/
module mips(
	input wire clk,rst,
	input wire[31:0] IR,
	output wire[31:0] pc_out,	
	output wire memwrite,
	output wire[31:0] aluout,writedata,
	input wire[31:0] readdata 
    );
	wire[2:0] aluctrl;
	wire memtoreg,alusrc,regdst,regwrite,branch,jump,pcsrc,zero;
	assign pcsrc=branch&zero;

	controller gate15(IR[31:26],IR[5:0],aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
	datapath gate16(clk,rst,aluctrl,memtoreg,alusrc,regdst,regwrite,pcsrc,jump,readdata,IR,aluout,writedata,pc_out,zero);

endmodule
