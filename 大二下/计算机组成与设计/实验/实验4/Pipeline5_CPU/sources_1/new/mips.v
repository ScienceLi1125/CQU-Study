`timescale 1ns / 1ps

module mips(
	input wire clk,
    input wire rst,
    input wire [31:0] mem_rdata,
	input wire [31:0] instr,	
	output wire [31:0] mem_wdata,
    output wire [31:0] pc,
    output wire inst_ram_ena,
    output wire data_ram_ena,  //Dataram的读信号
    output wire data_ram_wea,  //原本data_ram的wea是4位，但controller中发出的指令是1位的，故此处设置为1位
    output wire [31:0] alu_result    
    );
	
	wire memtoreg,alusrc,regdst,regwrite,jump,regwriteM,memtoregE,regwriteE,memtoregM,branch;
	wire[2:0] alucontrol;
	wire [31:0] instrD;
	assign inst_ram_ena = 1'b1;    //由于cpu一直是在读指令的，所以instr--ram--ena恒为1
	//mips = datapath + controller
	controller c(.clka(clk),.rst(rst),.instr(instrD),.jump(jump),.branch(branch),.alusrc(alusrc),
		.memwrite(data_ram_wea),.memetoreg(memtoreg),.regwrite(regwrite),.regdst(regdst),
		.data_ram_ena(data_ram_ena),
    	.regwriteM(regwriteM),    //传入datapath中的hazard
		.memtoregE(memtoregE),    //传入datapath中的hazard
		.regwriteE(regwriteE),    //传入datapath中的hazard
		.memtoregM(memtoregM),    //传入datapath中的hazard
		.alucontrol(alucontrol)
	);
	datapath dp(.clka(clk),.rst(rst),.instr(instr),.mem_rdata(mem_rdata),.pc(pc),.writedataM(mem_wdata),
		.alu_resultM(alu_result),.memtoreg(memtoreg),.alusrc(alusrc),.regdst(regdst),
		.regwrite(regwrite),.jump(jump),.branch(branch),.regwriteM(regwriteM),.memtoregE(memtoregE),
		.regwriteE(regwriteE),.memtoregM(memtoregM),.alucontrol(alucontrol),.instrD_to_controller(instrD)
	);
	
endmodule


