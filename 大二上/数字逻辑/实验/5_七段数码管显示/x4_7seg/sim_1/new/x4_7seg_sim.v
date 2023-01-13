`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/17 19:39:57
// Design Name: 
// Module Name: x4_7seg_sim
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


module x4_7seg_sim();
    reg clk;
    wire [6:0] a_to_g;
    wire [3:0] an;
    wire dp;
    reg [15:0] x;
    x4_7seg gate(x,clk,a_to_g,an,dp); 
    initial
    begin
        clk=0;
        x='h1234;
    end
    always #0.001 clk=~clk;
    //always #100 x=x+1;
    

endmodule
