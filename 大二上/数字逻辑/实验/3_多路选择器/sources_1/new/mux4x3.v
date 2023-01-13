`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/23 14:44:48
// Design Name: 
// Module Name: mux4x3
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


module mux4x3(w0,w1,w2,w3,s0,s1,f);
    input [2:0] w0;
    input [2:0] w1;
    input [2:0] w2;
    input [2:0] w3;
    input s0,s1;
    output reg[2:0] f;
    always@(w0,w1,w2,w3,s0,s1)
    begin
        case({s1,s0})
        2'b00:f=w0;
        2'b01:f=w1;
        2'b10:f=w2;
        2'b11:f=w3;
        endcase
    end
endmodule
