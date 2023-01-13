`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/23 14:46:47
// Design Name: 
// Module Name: mux4x3_sim
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


module mux4x3_sim();
    reg [2:0]w0=0;
    reg [2:0]w1=0;
    reg [2:0]w2=0;
    reg [2:0]w3=0;
    reg s0=0;
    reg s1=0;
    wire [2:0] f;
    mux4x3 utt(w0,w1,w2,w3,s0,s1,f);    //记得实例化模块
    always #5 w0=w0+1;
    always #10 w1=w1+1;
    always #15 w2=w2+1;
    always #20 w3=w3+1;
    always #25 s0=s0+1;
    always #30 s1=s1+1;

endmodule
