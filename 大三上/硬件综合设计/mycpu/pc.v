/*pcflopenrc模块
    包含en信号、rst信号、clear信号的PC寄存器
*/
`timescale 1ns / 1ps

module pc #(parameter WIDTH = 8)(
	input clk, reset, enable,clear,
	input [WIDTH-1:0] d,
	input [WIDTH-1:0] newPC,
	output reg [WIDTH-1:0] q
	);

	always @(posedge clk, posedge reset) begin
		if(reset)			q <= 32'hbfc00000;
		else if(clear) 		q <= newPC;
		else if(enable) 	q <= d;
	end
endmodule
