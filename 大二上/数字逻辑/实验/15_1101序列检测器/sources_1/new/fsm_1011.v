`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/30 15:23:37
// Design Name: 
// Module Name: fsm_1011
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
/*1101序列检测器：事先输入一个8位01串，每次手动读入一位，当读到1101序列时检测成功
消抖模块：按钮输入会有抖动，因此采用延迟30ms的方法检测有效输入
并转串模块：将输入的8位串最高位输出，然后整体左移。循环该操作即可
检测模块：5个状态转移，检测1101
*/

module fsm_1011(
    input clk,          //系统时钟信号
    input bot_clk,      //消抖前的按钮输入信号，表示读入一位
    input set,          //读入的使能信号
    input [7:0] data,   //事先输入的8位数据
    input rst,          //复位信号
    output z,           //当前结果（即序列中有无1101）
    output now          //当前读到的信号
    );
wire temp_clk;          //消抖后的按钮信号
wire x;                 //有限状态机模块中用到的输入X

debkey ux(.clk(clk), .reset(rst), .key(bot_clk), .debkey(temp_clk));

par2ser uxx(.data(data), .clk(temp_clk), .rst(rst), .set(set), .out(x), .now(now));

fsm uxxx(.x(x), .clk(temp_clk), .rst(rst), .data_out(z));

endmodule


// par to ser
module par2ser(data,clk,rst,set,out,now);
    input [7:0]data;        //8位并行输入信号
    input clk,set,rst;      //此clk非系统时钟，而是消抖后的按钮输入信号
    output reg out;
    output now;             //并转串的1位信号
    reg [7:0] load;         //临时寄存器，存储data，防止左移时data被改变
    always@(posedge clk or posedge rst) begin
        if (set) load <= data;              //set是设定data的使能信号
        else if (rst) load <= 0;
        else load <= {load[6:0],1'b0};      //也可以写成load <= load<<1;
    end

    always@(*) begin
        out <= load[7];
    end
    
    assign now = out;
endmodule

// main fsm block(有限状态机)
module fsm(x, clk, rst, data_out);
    input clk, rst;              //此处clk为消抖后的按键信号
    input x;                     //输入X
    output reg data_out;

parameter   s0 = 5'b00001,      //5种状态
             s1 = 5'b00010,
             s2 = 5'b00100, 
             s3 = 5'b01000, 
             s4 = 5'b10000;

// reg delare
reg [4:0] current_state, next_state;    //现态与次态

always @(negedge clk or posedge rst) begin  //negedge clk表示松开按钮后触发
    if (rst) current_state <= s0;
    else current_state <= next_state;
end

always @(*) begin
    case (current_state)
        s0 : begin
            if (x) next_state <= s1;
            else next_state <= s0;
        end
        s1 : begin
            if (x) next_state <= s2;
            else next_state <= s0;
        end
        s2 : begin
            if (x) next_state <= s2;
            else next_state <= s3;
        end
        s3 : begin
            if (x) next_state <= s4;
            else next_state <= s0;
        end
        s4 : begin
            if (x) next_state <= s2;
            else next_state <= s0;
        end
        default: next_state <= s0;
    endcase
end

always @(*) begin
    if (current_state == s4) data_out <= 1;
    else data_out <= 0;
end
endmodule


// 消抖模块
module debkey(clk,reset,key,debkey);
parameter width = 1;
parameter T100Hz = 499999;

	input clk;
	input reset;
	input [width-1:0]key;
	output [width-1:0]debkey;

    reg [width-1:0]key_rrr,key_rr,key_r;

	integer cnt_100Hz;
	reg clk_100Hz;
	always @(posedge clk or posedge reset)
		if(reset)
			cnt_100Hz <= 32'b0;
		else
			begin
				cnt_100Hz <= cnt_100Hz + 1'b1;
				if(cnt_100Hz == T100Hz)
					begin
						cnt_100Hz <= 32'b0;
						clk_100Hz <= ~clk_100Hz;
					end
			end

	always @(posedge clk_100Hz or posedge reset)
		if(reset)
			begin
				key_rrr <= 1'b1;
				key_rr <= 1'b1;
				key_r <= 1'b1;
			end
		else
			begin
				key_rrr <= key_rr;
				key_rr <= key_r;
				key_r <= key;
			end

	assign debkey = key_rrr & key_rr & key_r;
	
endmodule