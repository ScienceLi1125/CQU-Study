/*eqcmp模块
    为branch指令提供判断,输出0/1值
*/
`timescale 1ns / 1ps
`include "defines.vh"

module eqcmp(
	input wire [31:0] a,b,
	input wire [7:0] alucontrolD,
	output reg y
    );
	
	always@ (*) begin
		case (alucontrolD)
			`EXE_BEQ_OP: y = (a == b) ? 1:0;
			`EXE_BGTZ_OP: y = ((a[31] == 0) && (a != 32'b0)) ? 1:0;
			`EXE_BLEZ_OP: y = ((a[31] == 1) || (a == 32'b0)) ? 1:0;
			`EXE_BNE_OP: y = (a != b) ? 1:0; 
			`EXE_BLTZ_OP: y = (a[31] == 1) ? 1:0;
			`EXE_BLTZAL_OP: y = (a[31] == 1) ? 1:0;
			`EXE_BGEZ_OP: y = (a[31] == 0) ? 1:0;
			`EXE_BGEZAL_OP: y = (a[31] == 0) ? 1:0;
		default: y = 0;
		endcase
	end
	
endmodule
