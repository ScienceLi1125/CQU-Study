/*mycpu_top模块
    将datapath和controller连接，并连接mmu实现地址转换
*/
`timescale 1ns / 1ps

module mycpu_top(
	input wire clk,resetn,
	input wire [5:0] ext_int,
	//inst_ram信号
	output wire inst_sram_en,
	output wire [3:0] inst_sram_wen,
	output wire [31:0] inst_sram_addr,
	output wire [31:0] inst_sram_wdata,
	input wire [31:0] inst_sram_rdata,
	//data_ram信号
	output wire data_sram_en,
	output wire [3:0] data_sram_wen,
	output wire [31:0] data_sram_addr,
	output wire [31:0] data_sram_wdata,
	input wire [31:0] data_sram_rdata,
	//debug信号
	output wire [31:0] debug_wb_pc,
	output wire [3:0] debug_wb_rf_wen,
	output wire [4:0] debug_wb_rf_wnum,
	output wire [31:0] debug_wb_rf_wdata
    );
	// F 阶段
	wire [31:0] pcF,instrF;
	wire [31:0] pcconvertF;
	wire [31:0] dataadr;
	// D 阶段
	wire [5:0] opD,functD;
	wire [4:0] rtD;
	wire [7:0] alucontrolD;
	wire [31:0] instrD;	
	wire jumpD,jalD,jrD,balD,memenD,hiloD,equalD,stallD;
	wire branchD;
	wire breakD,syscallD,reserveD,eretD,pcsrcD;
	// E 阶段
	wire regdstE,alusrcE,memtoregE,regwriteE;
	wire jumpE,jalE,jrE,balE,memenE,hiloE;
	wire flushE,stallE;
	wire [7:0] alucontrolE;
	// M 阶段
	wire hiloM,memtoregM,regwriteM,memenM;
	wire [3:0] memwriteM;
	wire cp0weM,cp0selM,flushM;
	wire [31:0] aluoutM,writedataM,readdataM;
	// W 阶段
	wire flushW,hiloW,regwriteW,memtoregW;
	wire [31:0] pcW,result2W;
	wire [4:0] writereg2W;
	wire nocache;

	assign	inst_sram_en		= 1;
	assign	inst_sram_wen		= 4'b0; 
	assign	inst_sram_addr		= pcconvertF;
	assign	inst_sram_wdata		= 32'b0;
	assign	instrF				= inst_sram_rdata;

	assign	data_sram_en		= memenM;
	assign	data_sram_wen		= memwriteM;
	assign	data_sram_addr		= dataadr;
	assign	data_sram_wdata		= writedataM;
	assign	readdataM			= data_sram_rdata;

	assign	debug_wb_pc			= pcW;
	assign	debug_wb_rf_wen		= {4{regwriteW}};
	assign	debug_wb_rf_wnum	= writereg2W;
	assign	debug_wb_rf_wdata	= result2W;

	mmu mmu0(
		.inst_vaddr(pcF),
    	.inst_paddr(pcconvertF),
  		.data_vaddr(aluoutM),
   		.data_paddr(dataadr),
		.no_dcache(nocache)
		);

	controller c(
		.clk(~clk),
		.rst(~resetn),
		//decode stage
		.instrD(instrD),
		.opD(opD),
		.functD(functD),
		.rt(rtD),
		.pcsrcD(pcsrcD),
		.branchD(branchD),
		.equalD(equalD),
		.jumpD(jumpD),
		.jalD(jalD),
		.jrD(jrD),
		.balD(balD),
		.memenD(memenD),
		.hiloD(hiloD),
		.breakD(breakD),
		.syscallD(syscallD),
		.reserveD(reserveD),
		.eretD(eretD),
		.alucontrolD(alucontrolD),
		.stallD(stallD),
		//execute stage
		.flushE(flushE),
		.memtoregE(memtoregE),
		.alusrcE(alusrcE),
		.regdstE(regdstE),
		.regwriteE(regwriteE),	
		.alucontrolE(alucontrolE),
		.jumpE(jumpE),
		.jalE(jalE),
		.jrE(jrE),
		.balE(balE),
		.memenE(memenE),
		.hiloE(hiloE),
		//mem stage
		.flushM(flushM),
		.memtoregM(memtoregM),
		.regwriteM(regwriteM),
		.hiloM(hiloM),
		.memenM(memenM),
		.cp0weM(cp0weM),
		.cp0selM(cp0selM),
		//write back stage
		.flushW(flushW),
		.memtoregW(memtoregW),
		.regwriteW(regwriteW),
		.hiloW(hiloW)
		);

	datapath dp(
		.clk(~clk),
		.rst(~resetn),
		//fetch stage
		.pcF(pcF),
		.instrF(instrF),
		//decode stage
		.pcsrcD(pcsrcD),
		.branchD(branchD),
		.jumpD(jumpD),
		.jalD(jalD),
		.jrD(jrD),
		.balD(balD),
		.memenD(memenD),
		.breakD(breakD),
		.syscallD(syscallD),
		.reserveD(reserveD),
		.eretD(eretD),
		.equalD(equalD),
		.opD(opD),
		.functD(functD),
		.rtD(rtD),
		.alucontrolD(alucontrolD),
		.instrD(instrD),
		.stallD(stallD),
		//execute stage
		.memtoregE(memtoregE),
		.alusrcE(alusrcE),
		.regdstE(regdstE),
		.regwriteE(regwriteE),
		.alucontrolE(alucontrolE),
		.flushE(flushE),
		.stallE(stallE),
		.jumpE(jumpE),
		.jalE(jalE),
		.jrE(jrE),
		.balE(balE),
		.memenE(memenE),
		.hiloE(hiloE),
		//mem stage
		.memtoregM(memtoregM),
		.regwriteM(regwriteM),
		.cp0weM(cp0weM),
		.cp0selM(cp0selM),
		.aluout2M(aluoutM),
		.writedata2M(writedataM),
		.readdataM(readdataM),
		.memwriteM(memwriteM),
		.flushM(flushM),
		//writeback stage
		.memtoregW(memtoregW),
		.regwriteW(regwriteW),
		.flushW(flushW),
		.pcW(pcW),
		.writeregW(writereg2W),
		.resultW(result2W)
	    );
	
endmodule
