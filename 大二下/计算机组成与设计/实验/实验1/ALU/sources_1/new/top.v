`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/19 20:02:54
// Design Name: 
// Module Name: top
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


module top(
    input wire [2:0] op,    //手动输入alu
    input wire [7:0] num1,  //手动输入alu
    input wire clk,reset,   //板子上clk、手动rst输入display
    output wire [6:0]seg,   //display输出
    output wire [7:0]ans     //display输出
    );
    wire [31:0] result;      //alu输出进入display
    alu gate1(op,num1,result);
    display gate2(clk,reset,result,seg,ans);
    
endmodule
