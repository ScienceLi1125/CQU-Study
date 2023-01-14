/*datapath模块
    根据Controller的解码信号在流水线寄存器传递信号，串起CPU的整个运行过程
*/
`timescale 1ns / 1ps
`include "defines.vh"

module datapath(
	input wire clk,rst,
	// F 阶段
	input wire[31:0] instrF,
	output wire[31:0] pcF,
	// D 阶段
	input wire pcsrcD,branchD,
	input wire jumpD,jalD,jrD,balD,memenD,
	input wire breakD,syscallD,reserveD,eretD,
	input wire[7:0] alucontrolD,
	output wire equalD,
	output wire[5:0] opD,functD,
	output wire[4:0] rtD,
	output wire [31:0] instrD,
	output wire stallD,
	// E 阶段
	input wire memtoregE,
	input wire alusrcE,regdstE,
	input wire regwriteE,
	input wire[7:0] alucontrolE,
	input wire jumpE,jalE,jrE,balE,memenE,hiloE,
	output wire flushE,stallE,
	// M 阶段
	input wire memtoregM,
	input wire regwriteM,
	input wire cp0weM,cp0selM,
	input wire [31:0] readdataM,
	output wire [31:0] aluout2M,writedata2M,
	output wire [3:0] memwriteM,
	output wire flushM,
	// W 阶段
	input wire memtoregW,
	input wire regwriteW,
	output wire flushW,
	output wire [31:0] pcW,
	output wire [4:0] writeregW,
	output wire [31:0] resultW
    );
	
	// F 阶段
	wire stallF,flushF;
	wire branchjumpF;
	wire [31:0] newPC;
	wire [31:0] pcnextFD,pcnextbrFD,pcplus4F,pcplus8F;
	// D 阶段
	wire [31:0] pcbranchD,pcD,pcplus8D,pcnext_tmp;
	wire [31:0] pcplus4D;
	wire forwardaD,forwardbD,jrforwardaD;
	wire branchjumpD,jrb_l_astall,jrb_l_bstall;
	wire [6:0] exceptD;
	wire [4:0] rsD,rdD;
	wire [4:0] saD;
	wire flushD; 
	wire [31:0] signimmD,signimmshD;
	wire [31:0] srcaD,srca2D,srcbD,srcb2D,srca2jD,srca3D,srcb3D;
	wire [15:0] offsetD;
	// E 阶段
	wire [1:0] forwardaE,forwardbE;
	wire [4:0] rsE,rtE,rdE;
	wire [4:0] saE;
	wire [4:0] writeregE,writereg_jalrE,writereg2E;
	wire [31:0] signimmE;
	wire [31:0] srcaE,srca2E,srcbE,srcb2E,srcb3E;
	wire [31:0] aluoutE,aluout2E;
	wire [31:0] pcE,pcplus4E,pcplus8E;
	wire [31:0] instrE;
	wire [15:0] offsetE;
	wire overflowE,branchjumpE;
	wire [63:0] div_result;
	wire [6:0] exceptE;
	// M 阶段
	wire [4:0] writeregM,rdM;
	wire [7:0] alucontrolM;
	wire overflowM,branchjumpM,adelM,adesM;
	wire [31:0] writedataM,aluoutM,pcM,aluout1M,srcbM;
	wire [31:0] cp0out_data;
	wire [6:0] exceptM;
	wire [31:0] status_o;
	wire [31:0] cause_o;
	wire [31:0] excepttype_i;
	wire [31:0] bad_addr_i;
	wire [31:0] count_o;
	wire [31:0] compare_o;
	wire [31:0] epc_o;
	wire [31:0] config_o;
	wire [31:0] prid_o;
	wire [31:0] badvaddr;
	wire timer_int_o;
	// W 阶段
	wire adelW;
	wire [31:0] readdataW,lwresultW,aluoutW;
	wire [7:0] alucontrolW;


	/* ---------------------------- F 阶段 ---------------------------- */

	//PC寄存器，pcF = pcnextFD(按instr_ram取指) or newPC(flush流水线)
	pc #(32) pc_regF(
		.clk(clk),
		.reset(rst),
		.enable(~stallF),
		.clear(flushF),
		.d(pcnextFD),
		.newPC(newPC),
		.q(pcF)
		);
	//计算顺序读取需要的PC值,PCnext = PC+4
	adder pcadd1(pcF,32'b100,pcplus4F);
	//计算JAL/JALR指令需要的PC值,GPR[31] = PC+8
	adder pcadd2(pcF,32'b1000,pcplus8F);

	//-------------------- 确定下一条PC --------------------
	//PCnext = PC+4 or branch
	mux2 #(32) pcbrmux(pcplus4F,pcbranchD,pcsrcD,pcnextbrFD);
	//PCnext = PCnext or j/jal
	mux2 #(32) pcjumpmux(pcnextbrFD,{pcplus4D[31:28],instrD[25:0],2'b00},jumpD | jalD,pcnext_tmp);
	//PCnext = PCnext or jr
	mux2 #(32) pcjrmux(pcnext_tmp,srca2D,jrD,pcnextFD);

	//是否是跳转指令
	assign branchjumpF =branchD | jumpD | jalD | jrD;

	/* ---------------------------- FD流水线寄存器 ---------------------------- */
	flopenrc #(32) r1D(clk,rst,~stallD,flushD,pcplus4F,pcplus4D);
	flopenrc #(32) r2D(clk,rst,~stallD,flushD,instrF,instrD);
	flopenrc #(32) r3D(clk,rst,~stallD,flushD,pcF,pcD);
	flopenrc #(32) r4D(clk,rst,~stallD,flushD,pcplus8F,pcplus8D);
	flopenrc #(1) r5D(clk,rst,~stallD,flushD,branchjumpF,branchjumpD);

	/* ---------------------------- D 阶段 ---------------------------- */

	//instrD[15:0]扩展
	signext se(instrD[15:0],instrD[29:28],signimmD);
	//扩展后左移
	sl2 immsh(signimmD,signimmshD);
	//计算branch指令的跳转地址:PC+Sign_extend({offset,00})
	adder pcadd3(pcplus4D,signimmshD,pcbranchD);
	
	// --------------------- 解决控制冒险与数据冒险 ---------------------
	//branch带来的数据前推选择当前输入ALU的操作数srcD=srcD(不前推) or aluoutM(上一条是R/上两条是load带来的数据冒险)
	mux2 #(32) forwardamux(srcaD,aluoutM,forwardaD,srca2D);
	mux2 #(32) forwardbmux(srcbD,aluoutM,forwardbD,srcb2D);
	//提前判断branch指令可能需要数据前推
	mux2 #(32) forwardbjrb_lamux(srca2D,readdataM,jrb_l_astall,srca3D);
	mux2 #(32) forwardbjrb_lbmux(srcb2D,readdataM,jrb_l_bstall,srcb3D);
	//提前判断branch指令的跳转情况以避免控制冒险
	eqcmp comp(srca3D,srcb3D,alucontrolD,equalD);

	//指令字段
	assign opD = instrD[31:26];
	assign functD = instrD[5:0];
	assign rsD = instrD[25:21];
	assign rtD = instrD[20:16];
	assign rdD = instrD[15:11];
	assign saD = instrD[10:6];
	assign offsetD = instrD[15:0];

	//异常采集
	assign exceptD[3:0] = {reserveD,breakD,syscallD,eretD};

	/* ---------------------------- DE流水线寄存器 ---------------------------- */
	flopenrc #(32) 	r1E(clk,rst,~stallE,flushE,pcD,pcE);
	flopenrc #(32) 	r2E(clk,rst,~stallE,flushE,instrD,instrE);
	flopenrc #(32) 	r3E(clk,rst,~stallE,flushE,pcplus4D,pcplus4E);
	flopenrc #(32) 	r4E(clk,rst,~stallE,flushE,pcplus8D,pcplus8E);
	flopenrc #(1) 	r5E(clk,rst,~stallE,flushE,branchjumpD,branchjumpE);
	flopenrc #(4) 	r6E(clk,rst,~stallE,flushE,exceptD[3:0],exceptE[3:0]);
	flopenrc #(32) r7E(clk,rst,~stallE,flushE,srcaD,srcaE);
	flopenrc #(32) r8E(clk,rst,~stallE,flushE,srcbD,srcbE);
	flopenrc #(32) r9E(clk,rst,~stallE,flushE,signimmD,signimmE);
	flopenrc #(5) r10E(clk,rst,~stallE,flushE,rsD,rsE);
	flopenrc #(5) r11E(clk,rst,~stallE,flushE,rtD,rtE);
	flopenrc #(5) r12E(clk,rst,~stallE,flushE,rdD,rdE);
	flopenrc #(5) r13E(clk,rst,~stallE,flushE,saD,saE);
	flopenr #(16) r14E(clk,rst,~stallE,offsetD,offsetE);

	/* ---------------------------- E 阶段 ---------------------------- */

	//数据前推选择当前输入ALU的操作数srcE=srcE(不前推) or resultW(上两条要写寄存器堆) or aluoutM(上一条是R)
	mux3 #(32) forwardaemux(srcaE,resultW,aluoutM,forwardaE,srca2E);
	mux3 #(32) forwardbemux(srcbE,resultW,aluoutM,forwardbE,srcb2E);

	//选择当前输入ALU的srcB的操作数=srcb2E or imm(立即数)
	mux2 #(32) srcbmux(srcb2E,signimmE,alusrcE,srcb3E);

	//除法运算
	wire [63:0] hilo_in,hilo_out;
	wire div_start,div_signed,div_ready;
	assign div_signed = (alucontrolE == `EXE_DIV_OP)? 1'b1: 1'b0;
	assign div_start = (alucontrolE == `EXE_DIV_OP | alucontrolE == `EXE_DIVU_OP & ~div_ready)? 1'b1: 1'b0;
	div div(
		.clk(clk),
		.rst(rst),
		.signed_div_i(div_signed),
		.opdata1_i(srca2E),
		.opdata2_i(srcb3E),
		.start_i(div_start),
		.annul_i(1'b0),
		.result_o(div_result),
		.ready_o(div_ready)
		);

	//ALU运算
	alu alu(
		.a(srca2E),
		.b(srcb3E),
		.alucontrol(alucontrolE),
		.sa(saE),
		.offset(offsetE),
		.hilo_in(hilo_in),
		.result(aluoutE),
		.hilo_out(hilo_out),
		.overflow(overflowE)
		);
	
	//HILO寄存器
	hilo_reg hilo(
		.clk(clk),
		.rst(rst),
		.flushE(flushE),
		.hilo_signal(hiloE),
		.hilo_div(div_ready),
		.alucontrol(alucontrolE),
		.hi_in(hilo_out[63:32]),
		.lo_in(hilo_out[31:0]),
		.div_result(div_result),
		.hi_out(hilo_in[63:32]),
		.lo_out(hilo_in[31:0])
		);

	//异常采集
	assign exceptE[4]=overflowE;

	//选择写寄存器：rt(I型) or rd(R型)
	assign writeregE = (regwriteE & regdstE)?  rdE:
					   (regwriteE & ~regdstE)? rtE: 
					   5'b00000;

	//JALR指令选择写寄存器，没有指定时默认为31
	assign writereg_jalrE = (alucontrolE == `EXE_JALR_OP & writeregE == 0)? 5'b11111 : writeregE;
	//选择Link类指令的写寄存器
	mux2 #(5) wrmux2(writereg_jalrE,5'b11111,jalE | balE,writereg2E);
	//选择写寄存器堆的数据，ALU计算结果 or Link指令的跳转地址
	mux2 #(32) wrmux23(aluoutE,pcplus8E,jalE|jrE|balE,aluout2E);
	

	/* ---------------------------- EM流水线寄存器 ---------------------------- */
	floprc #(32) r1M(clk,rst,flushM,srcb2E,writedataM);
	floprc #(32) r2M(clk,rst,flushM,aluout2E,aluout2M);
	floprc #(5) r3M(clk,rst,flushM,writereg2E,writeregM);
	floprc #(1) r4M(clk,rst,flushM,overflowE,overflowM);
	floprc #(8) r5M(clk,rst,flushM,alucontrolE,alucontrolM);
	floprc #(5) r6M(clk,rst,flushM,rdE,rdM);
	floprc #(32) r7M(clk,rst,flushM,srcb3E,srcbM);
	floprc #(32) r8M(clk,rst,flushM,pcE,pcM);
	floprc #(1) r9M(clk,rst,flushM,branchjumpE,branchjumpM);
	floprc #(5) r10M(clk,rst,flushM,exceptE[4:0],exceptM[4:0]);

	/* ---------------------------- M 阶段 ---------------------------- */

	//选择写入dataram的数据来自ALU or CP0
	mux2 #(32) cp0selmux(aluout2M,cp0out_data,cp0selM,aluoutM);
	//为不同的写内存指令(sb、sh、sw)解码写地址类型,即字节、半字、整字的位置
	sw_select swsel(
		.adesM(adesM),
		.addressM(aluout2M),
		.alucontrolM(alucontrolM),
		.memwriteM(memwriteM)
		);

	//地址例外
	addr_except addrexcept(
		.addrs(aluoutM),
		.alucontrolM(alucontrolM),
		.adelM(adelM),
		.adesM(adesM)
		); 

	//异常采集
	assign exceptM[6:5]={adesM,adelM};

	//将需要写的字节/半字扩展至整字宽
	assign writedata2M = (alucontrolM == `EXE_SB_OP)? {{writedataM[7:0]},{writedataM[7:0]},{writedataM[7:0]},{writedataM[7:0]}}:
						(alucontrolM == `EXE_SH_OP)? {{writedataM[15:0]},{writedataM[15:0]}}:
						(alucontrolM == `EXE_SW_OP)? {{writedataM[31:0]}}:
						writedataM;

	
	/* ---------------------------- MW流水线寄存器 ---------------------------- */
	floprc #(32) r1W(clk,rst,flushW,readdataM,readdataW);
	floprc #(5) r2W(clk,rst,flushW,writeregM,writeregW);
	floprc #(8) r3W(clk,rst,flushW,alucontrolM,alucontrolW);
	floprc #(32) r4W(clk,rst,flushW,aluoutM,aluoutW);
	floprc #(32) r5W(clk,rst,flushW,pcM,pcW);
	floprc #(1) r6W(clk,rst,flushW,adelM,adelW);

	/* ---------------------------- W 阶段 ---------------------------- */

	//选择写回寄存器堆的数据来自ALU or dataram
	mux2 #(32) resmux(aluoutW,readdataW,memtoregW,lwresultW);

	//根据访存指令类型将从内存中读取的整字结果截取并扩展
	lw_select lwsel(
		.adelW(adelW),
		.aluoutW(aluoutW),
		.alucontrolW(alucontrolW),
		.lwresultW(lwresultW),
		.resultW(resultW)
		);

	//寄存器堆
	regfile rf(
		.clk(clk),
		.we3(regwriteW),
		.ra1(rsD),
		.ra2(rtD),
		.wa3(writeregW),
		.wd3(resultW),
		.rd1(srcaD),
		.rd2(srcbD)
	);

	//例外
	exception exception_type(
		.rst(rst),
		.pcM(pcM),
		.exceptM(exceptM),
		.cp0_status(status_o),
		.cp0_cause(cause_o),
		.aluoutM(aluoutM),
		.excepttype(excepttype_i),
		.bad_addr(bad_addr_i)
		);

	//冒险
	hazard h(
		// F 阶段
		.stallF(stallF),
		.newPC(newPC),
		.flushF(flushF),
		// D 阶段
		.rsD(rsD),
		.rtD(rtD),
		.branchD(branchD),
		.jumpD(jumpD),
		.jrD(jrD),
		.alucontrolD(alucontrolD),
		.forwardaD(forwardaD),
		.forwardbD(forwardbD),
		.jrforwardaD(jrforwardaD),
		.stallD(stallD),
		.jrb_l_astall(jrb_l_astall),
		.jrb_l_bstall(jrb_l_bstall),
		.flushD(flushD),
		// E 阶段
		.rsE(rsE),
		.rtE(rtE),
		.writeregE(writeregE),
		.regwriteE(regwriteE),
		.memtoregE(memtoregE),
		.hilo_signal(hiloE),
		.alucontrolE(alucontrolE),
		.div_ready(div_ready),
		.forwardaE(forwardaE),
		.forwardbE(forwardbE),
		.flushE(flushE),
		.stallE(stallE),
		// M 阶段
		.writeregM(writeregM),
		.regwriteM(regwriteM),
		.memtoregM(memtoregM),
		.exception_type(excepttype_i),
		.overflowM(overflowM), 
		.flushM(flushM),
		.epc(epc_o),
		// W 阶段
		.writeregW(writeregW), // writereg addr
		.regwriteW(regwriteW), // wtitereg enable
		.flushW(flushW)
		);

	//CP0寄存器
	cp0_reg cp0reg(
		.clk(clk),  
		.rst(rst),
		.we_i(cp0weM),
		.waddr_i(rdM),
		.raddr_i(rdM),
		.data_i(srcbM),
		.int_i(0),
		.excepttype_i(excepttype_i),
		.current_inst_addr_i(pcM),
		.is_in_delayslot_i(branchjumpM),
		.bad_addr_i(bad_addr_i),
		.data_o(cp0out_data),
		.count_o(count_o),
		.compare_o(compare_o),
		.status_o(status_o),
		.cause_o(cause_o),
		.epc_o(epc_o),
		.config_o(config_o),
		.prid_o(prid_o),
		.badvaddr(badvaddr),
		.timer_int_o(timer_int_o)
		);
endmodule
