/*regfile模块
	ID阶段读寄存器堆,WB阶段写寄存器堆
*/
`timescale 1ns / 1ps

module regfile(
	input wire clk,
	input wire we3,				//写使能信号
	input wire[4:0] ra1,ra2,	//读端口
	input wire[4:0] wa3,		//写端口
	input wire[31:0] wd3,		//写数据
	output wire[31:0] rd1,rd2	//读数据
    );

	reg [31:0] rf[31:0];

	always @(negedge clk) begin	//将组合逻辑改为时序逻辑以避免综合时生成latch
		if(we3) begin
			rf[wa3] <= wd3;
		end
	end

	assign rd1 = (ra1 != 0) ? rf[ra1] : 0;
	assign rd2 = (ra2 != 0) ? rf[ra2] : 0;
endmodule

