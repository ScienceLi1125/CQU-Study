`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/19 19:37:52
// Design Name: 
// Module Name: alu_sim2
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

module alu_sim2();
    reg [2:0] op; 
    reg [7:0] num1;
    wire [31:0] result;
    alu gate(op,num1,result);
    initial begin
        op=3'b000;
        num1=8'b00000010;
        #10 op=3'b001;num1=8'b11111111;
        #10 op=3'b010;num1=8'b11111110;
        #10 op=3'b011;num1=8'b10101010;
        #10 op=3'b100;num1=8'b11110000;
        #10 op=3'b101;num1=8'b10000001;
    end
    

endmodule
