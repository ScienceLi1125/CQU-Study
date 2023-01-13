`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/18 09:45:00
// Design Name: 
// Module Name: digit_clock
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
/*  数字钟用数码管[1:0]显示秒，[3:2]显示分，LED[4:0]显示小时
    将100MHz系统时钟仍分频成400Hz实现分时复用，并且秒数每秒加一。又2**18=262144，2**27=134217728，因此
clk_cnt[17:0]==250000时显像位变化一次，clk_cnt[26:0]==100_00_0000时秒数加一。
    外加一个rst复位键可以将时钟清零
*/

module digit_clock(clk,rst,a_to_g,an,dp,led);
    input clk;              //clk接系统默认时钟信号，频率为100MHz
    input  rst;             //复位键
    output reg [6:0]a_to_g; //段
    output reg [3:0]an;     //位
    output reg dp;          //小数点
    output [4:0]led;        //led灯，显示小时(0~15)
    
    wire [1:0] s;           //临时变量，表示400Hz频率扫描的分与秒，4种值的情况对应an的4种选择
    reg [3:0] digit;        //临时变量，记录段
    reg [26:0] clk_cnt=0;   //计数变量，记录clk变化次数
    reg [6:0] second;       //秒，[6:4]记录秒的十位，[3:0]记录秒的个位
    reg [6:0] minute;       //分
    reg [4:0] hour=0;       //时
    assign s=clk_cnt[19:18];
    assign led=hour;

    always@(*)              //确定位
    case(s)
        2'b00: begin digit=second[3:0];  dp=1;   end  //秒的个位
        2'b01: begin digit=second[6:4];  dp=1;   end  //秒的十位
        2'b10: begin digit=minute[3:0];  dp=0;   end  //分的个位
        2'b11: begin digit=minute[6:4];  dp=1;   end  //分的十位
        default:digit=second[3:0];
    endcase
    always@(*)              //确定段
    case(digit)
        4'h0:a_to_g=7'b0000001;
        4'h1:a_to_g=7'b1001111;
        4'h2:a_to_g=7'b0010010;
        4'h3:a_to_g=7'b0000110;
        4'h4:a_to_g=7'b1001100;
        4'h5:a_to_g=7'b0100100;
        4'h6:a_to_g=7'b0100000;
        4'h7:a_to_g=7'b0001111;
        4'h8:a_to_g=7'b0000000;
        4'h9:a_to_g=7'b0000100;
        default:a_to_g=7'b0000001;
    endcase
    
    always@(*)              //改变位
    begin
        an=4'b1111;
        an[s]=0;
    end
    
//    always@(rst)begin         //此条always语句中和下一条always语句冲突，多个信号触发clk_cnt=0、second、minute、hour
//        if(rst==1)begin
//            clk_cnt=0;
//            second=0;
//            minute=0;
//            hour=0;
//        end
//        else;               //必须加else，否则生成锁存器！
//    end
    
    always@(posedge clk or posedge rst)
    begin
        if(rst==1)begin
            clk_cnt=0;
            second=0;
            minute=0;
            hour=0;
        end
        else if(clk_cnt==10000_0000)begin
            if(second[3:0]==9)begin
                if(second[6:4]==5)begin
                    if(minute[3:0]==9)begin
                        if(minute[6:4]==5)begin
                            hour=hour+1;
                            minute[6:4]=0;
                        end
                        else    minute[6:4]=minute[6:4]+1;
                        minute[3:0]=0;
                    end
                    else   minute[3:0]=minute[3:0]+1; 
                    second[6:4]=0;
                end
                else    second[6:4]=second[6:4]+1;
                second[3:0]=0;
            end
            else    second[3:0]=second[3:0]+1;
            clk_cnt=0;
        end
        else    clk_cnt=clk_cnt+1;
    end

endmodule
