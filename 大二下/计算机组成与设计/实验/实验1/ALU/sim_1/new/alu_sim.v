`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/09 00:07:29
// Design Name: 
// Module Name: alu_sim
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


module alu_sim();
    reg [2:0] op; 
    reg [7:0] num1;
    wire [31:0] result;
    alu gate(op,num1,result);
    initial begin
        op=0;
        num1=0;
    end
    always #50 op=op+1;
    always #50 num1={$random}%256;

endmodule
