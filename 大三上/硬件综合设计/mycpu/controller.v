/*controller模块
    调用maindec模块解码控制信号->调用aludec模块解码alucontrol,并在流水线寄存器、HILO寄存器之间传递信号
*/
`timescale 1ns / 1ps

module controller(
	input wire clk,rst,
	// D阶段
	input wire [31:0] instrD,
	input wire[5:0] opD,functD,
	input wire [4:0] rt,
	input equalD,
	input wire stallD,
	output wire pcsrcD,
	output wire branchD,
	output jumpD,jalD,jrD,balD,memenD,hiloD,
	output breakD,syscallD,reserveD,eretD,
	output wire[7:0] alucontrolD,
	// E阶段
	input wire flushE,
	output wire memtoregE,alusrcE,
	output wire regdstE,regwriteE,	
	output wire[7:0] alucontrolE,
	output wire jumpE,jalE,jrE,balE,memenE,hiloE,
	// M阶段
	input wire flushM,
	output wire memtoregM,
	output wire	regwriteM,hiloM,memenM,cp0weM,cp0selM,
	// W阶段
	input wire flushW,
	output wire memtoregW,regwriteW,hiloW
    );
	
	wire memtoregD,alusrcD,regdstD,regwriteD;
	wire cp0weD,cp0selD,cp0weE,cp0selE;
	
	// decoder
	maindec md(
		.instrD(instrD),
		.op(opD),
		.funct(functD),
		.rt(rt),
		.memtoreg(memtoregD),
		.branch(branchD),
		.alusrc(alusrcD),
		.regdst(regdstD),
		.regwrite(regwriteD),
		.jump(jumpD),
		.jal(jalD),
		.jr(jrD),
		.bal(balD),
		.memen(memenD),
		.hilo(hiloD),
		.breakM(breakD),
		.syscall(syscallD),
		.reserve(reserveD),
		.eret(eretD),
		.cp0we(cp0weD),
		.cp0sel(cp0selD)
		);

	assign pcsrcD = branchD & equalD;

	aludec ad(opD,rt,functD,alucontrolD); 
	
	// DE
	flopenrc #(19) regDE(
		clk,rst,~stallD,flushE,
		{memtoregD,alusrcD,regdstD,regwriteD,alucontrolD,jumpD,jalD,jrD,balD,memenD,cp0weD,cp0selD},
		{memtoregE,alusrcE,regdstE,regwriteE,alucontrolE,jumpE,jalE,jrE,balE,memenE,cp0weE,cp0selE}
		);
	// hilo DE
	flopr #(1) reghiloDE(
		clk,rst,
		hiloD,
		hiloE
		);
	// EM
	floprc #(6) regEM(
		clk,rst,flushM,
		{memtoregE,regwriteE,hiloE,memenE,cp0weE,cp0selE},
		{memtoregM,regwriteM,hiloM,memenM,cp0weM,cp0selM}
		);
	// MW
	floprc #(3) regMW(
		clk,rst,flushW,
		{memtoregM,regwriteM,hiloM},
		{memtoregW,regwriteW,hiloW}
		);
endmodule
