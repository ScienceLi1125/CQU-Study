/*mux2模块
	二选一
*/
`timescale 1ns / 1ps

module mux2 #(parameter WIDTH = 8)(
	input wire[WIDTH-1:0] d0,d1,
	input wire s,
	output wire[WIDTH-1:0] y
    );
	
	assign y = s ? d1 : d0;
endmodule