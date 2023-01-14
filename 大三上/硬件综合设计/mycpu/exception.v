/*exception模块
    IF,ID,EXE,MEM检测到的例外都放在MEM阶段进行处理
*/
`timescale 1ns / 1ps

module exception(
	input rst,
	input [31:0] pcM,
	input [6:0] exceptM,
	input wire[31:0] cp0_status,cp0_cause,aluoutM,
	output wire [31:0] excepttype,bad_addr
    );
	/*	exception input:
	{0: eret, 1: syscall, 2: break, 3: reserve, 4: overflow, 5: adelM, 6: adesM}

	ExcCode:
	0x00 Int
	0x04 AdEL
	0x05 AdES
	0x08 Sys
	0x09 Bp
	0x0A RI
	0x0C Ov
	*/
	// exception type
	assign excepttype = (rst)? 32'h0000_0000:
	                      ((cp0_cause[15:8] & cp0_status[15:8]) != 8'h00 && cp0_status[1] == 1'b0 && cp0_status[0] == 1'b1)? 32'h0000_0001: // interrupt
						  (pcM[1:0]!=2'b00)? 32'h0000_0004: // AdEL
						  (exceptM[0])? 32'h0000_000e: // eret
						  (exceptM[1])? 32'h0000_0008: // syscall
						  (exceptM[2])? 32'h0000_0009: // break
						  (exceptM[3])? 32'h0000_000a: // reserve
						  (exceptM[4])? 32'h0000_000c: // overflow
						  (exceptM[5])? 32'h0000_0004: // adelM
						  (exceptM[6])? 32'h0000_0005: // adesM
						  32'h0;
	// bad address
	assign bad_addr = (rst)? 32'h0:
					  ((cp0_cause[15:8] & cp0_status[15:8]) != 8'h00 && cp0_status[1] == 1'b0 && cp0_status[0] == 1'b1)? 32'h0:
					  (pcM[1:0]!=2'b00)? pcM:
					  (exceptM[0])? 32'h0:
					  (exceptM[1])? 32'h0:
					  (exceptM[2])? 32'h0:
					  (exceptM[3])? 32'h0:
					  (exceptM[4])? 32'h0:
					  (exceptM[5])? aluoutM:
					  (exceptM[6])? aluoutM:
					  32'h0;
endmodule
