`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/16 23:48:46
// Design Name: 
// Module Name: x7seg
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


module x7seg(x,a_to_g,an);
    input [3:0] x;          //x为输入的待显示的十六进制数字
    output reg [6:0]a_to_g; //a_to_g表示输出数码管的数字
    output [3:0]an;         //an是使能信号，表示4个数码管输出在哪一个
    
    assign an=4'b1110;      //一位七段数码管默认在最低位输出
    
    always@(x)
    case(x)
        4'h0:a_to_g=7'b0000001;     //4指的是二进制位数！！！
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
    
endmodule
