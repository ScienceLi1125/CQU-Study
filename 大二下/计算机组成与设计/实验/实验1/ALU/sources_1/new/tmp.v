`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/08 23:30:56
// Design Name: 
// Module Name: tmp
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
/*验证Vivado中减法操作符*/

module tmp(
    input [7:0] A,
    input [7:0] B,
    output [7:0] C
    );
    assign C=A-B;
    
endmodule
