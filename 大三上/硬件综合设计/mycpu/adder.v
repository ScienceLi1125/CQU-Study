/*adder模块
    加法器
*/
`timescale 1ns / 1ps

module adder(
	input wire[31:0] a,b,
	output wire[31:0] y
    );

	assign y =  a + b;
endmodule