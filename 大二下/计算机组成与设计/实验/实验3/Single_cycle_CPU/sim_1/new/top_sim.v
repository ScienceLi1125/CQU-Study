`timescale 1ns / 1ps


module top_sim();
	reg clk=0,rst=0;
	wire[31:0] writedata,dataadr;
	wire memwrite;
	wire[31:0] pc,instr,readdata;
	mips mp(clk,rst,pc,instr,memwrite,dataadr,writedata,readdata);
	Instr_mem imem(.clka(~clk),.addra({26'b0,pc[7:2]}),.douta(instr));
	Data_mem dmem(.clka(clk),.wea({3'b0,memwrite}),.addra(dataadr),.dina(writedata),.douta(readdata)); 
    
    always #10 clk=~clk;
    
endmodule
