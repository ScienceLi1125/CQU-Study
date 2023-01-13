`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/17 17:17:12
// Design Name: 
// Module Name: x4_7seg
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

/*4位7段数码管显像原理：每次选通1位，显示对应数字，一段时间后选通下一位显示对应数字，时间间隔选择合适时肉眼观察到的显像数字就是连续的。结束后重复进行
选择合适时间即为七段数码管的分频问题，频率太低(点亮4位所需时间超过20ms)数码管会出现闪烁现象，频率太高会出现亮度太低甚至无法看清，因此一般扫描间隔为几ms
综上，整个过程不超过0.02s，即间隔不超过0.02/4=0.005s，则频率最小设置为1/0.005=200Hz
另外，点亮一只数码管后接着点第二只数码前需要关断第一只数码管，否则会出现混乱
此处设置频率为400Hz，则时钟信号的计数变量应取(1/400)s / (1/100M)s = 250000，又2**18=262144，即[17:0]置满1，所以判断clk_cnt[19:18]的4种取值即可。
*/
module x4_7seg(x,clk,a_to_g,an,dp);
    input [15:0] x;         //输入4位十六进制数字，分别在四个数码管上显示
    input clk;              //clk接系统默认时钟信号，频率为100MHz
    output reg [6:0]a_to_g; //a_to_g表示亮的数码管显示的数字
    output reg [3:0]an;     //an是使能信号，表示4个数码管哪一个被点亮
    output dp;              //dp表示小数点
    
    wire [1:0] s;           //临时变量，表示clk_cnt最高两位，4种值的情况对应an的4种选择
    reg [3:0] digit;        //临时变量，表示待显示的1位16进制数
    reg [19:0] clk_cnt=0;   //计数变量，记录clk变化次数
    assign dp=1;
    assign s=clk_cnt[19:18];
    //以下几个always语句为并行执行
    always@(*)              //确定位
    case(s)
        2'b00:digit=x[3:0];
        2'b01:digit=x[7:4];
        2'b10:digit=x[11:8];
        2'b11:digit=x[15:12];
        default:digit=x[3:0];
    endcase
    always@(*)              //确定位
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
        4'hA:a_to_g=7'b0001000;
        4'hB:a_to_g=7'b1100000;
        4'hC:a_to_g=7'b0110001;
        4'hD:a_to_g=7'b1000010;
        4'hE:a_to_g=7'b0110000;
        4'hF:a_to_g=7'b0111000;
        default:a_to_g=7'b0000001;
    endcase
    always@(*)              //改变位
    begin
        an=4'b1111;
        an[s]=0;
    end
    
    always@(posedge clk)
    begin
        clk_cnt=clk_cnt+1;
    end
endmodule
