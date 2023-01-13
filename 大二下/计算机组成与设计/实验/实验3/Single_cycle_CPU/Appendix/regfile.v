`timescale 1ns / 1ps
/*寄存器堆(32*32bits)模块：用于读写ALU运算时用到的数据，其中读取为组合逻辑，写入为时序逻辑*/

module regfile(
	input wire clk,
	input wire we3,                //写使能信号
	input wire[4:0] ra1,ra2,wa3,   //读端口1,2，写端口3
	input wire[31:0] wd3,          //写数据
	output wire[31:0] rd1,rd2      //读数据
    );

	reg [31:0] rf[31:0];           //寄存器堆

	always @(posedge clk) begin
		if(we3) begin
			 rf[wa3] <= wd3;
		end
	end

	assign rd1 = (ra1 != 0) ? rf[ra1] : 0;     //约定0号寄存器只存储0
	assign rd2 = (ra2 != 0) ? rf[ra2] : 0;
endmodule
