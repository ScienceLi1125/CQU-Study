`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/18 13:33:06
// Design Name: 
// Module Name: digit_clock_sim
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


module digit_clock_sim();
    reg clk;
    reg rst;
    wire [6:0] a_to_g;
    wire [3:0] an;
    wire dp;
    wire [4:0] led;
    digit_clock gate(clk,rst,a_to_g,an,dp,led); 
    initial
    begin
        clk=0;
        rst=0;
    end
    always #0.001 clk=~clk;

endmodule
