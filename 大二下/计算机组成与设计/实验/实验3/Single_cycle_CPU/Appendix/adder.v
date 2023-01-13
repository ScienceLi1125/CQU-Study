`timescale 1ns / 1ps
/*¼Ó·¨Æ÷Ä£¿é*/

module adder(
	input wire[31:0] a,b,
	output wire[31:0] y
    );
	assign y = a + b;
	
endmodule
