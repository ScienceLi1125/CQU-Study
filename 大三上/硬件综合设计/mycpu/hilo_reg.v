/*hilo_reg模块
    乘除法指令写HILO,数据移动指令读HILO
*/
`timescale 1ns / 1ps
`include "defines.vh"

module hilo_reg(
	input wire clk,rst,flushE,
	input wire hilo_signal,		//是否是hilo指令
	input wire hilo_div,		//是否取除法结果
	input wire [7:0] alucontrol,
	input wire [31:0] hi_in,lo_in,
	input wire [63:0] div_result,
	output reg [31:0] hi_out,lo_out
    );

	always @(negedge clk) begin
		if(rst) begin
			hi_out <= 0;
			lo_out <= 0;
		end 
		else if(~flushE) begin
			if(hilo_div) begin
				hi_out <=div_result[63:32];
				lo_out <=div_result[31:0];
			end
			else if(alucontrol == `EXE_MULT_OP | alucontrol == `EXE_MULTU_OP) begin
				hi_out <=hi_in;
				lo_out <=lo_in;
			end
			else if(hilo_signal & alucontrol == `EXE_MTHI_OP) begin
				hi_out <= hi_in;
			end
			else if(hilo_signal & alucontrol == `EXE_MTLO_OP) begin
				lo_out <= lo_in;
			end
		end
	end
endmodule
