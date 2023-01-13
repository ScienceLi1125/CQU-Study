`timescale 1ns / 1ps
/*顶层模块：输入clk、rst信号，执行一条指令并输出需要写进Data memory的数据
    如果 datapath 和指令存储器都用上升沿触发的话，指令寄存器在上升沿收到的输入信号相当于上一个周期的地址。
    因此将指令寄存器改成下降沿触发，即传入~clk
*/

module top(
	input wire clk,rst,
	output wire[31:0] writedata,dataadr,
	output wire memwrite
    );
	wire[31:0] pc,instr,readdata;

	mips mp(clk,rst,instr,pc,memwrite,dataadr,writedata,readdata);
	Instr_mem imem(.clka(~clk),.addra({26'b0,pc[7:2]}),.douta(instr));
	Data_mem dmem(.clka(clk),.wea({3'b0,memwrite}),.addra(dataadr),.dina(writedata),.douta(readdata));
endmodule
