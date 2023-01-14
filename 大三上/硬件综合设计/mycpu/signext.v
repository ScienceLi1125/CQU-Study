/*signext模块
	立即数扩展,0扩展(instr[29:28]=2'b11)或按符号扩展(其他)
*/
`timescale 1ns / 1ps

module signext (
    input [15:0] a,
    input [1:0] typeM,
    output [31:0] y);
    
    assign y = (typeM == 2'b11)? {{16{1'b0}}, a} : {{16{a[15]}}, a};
endmodule
