`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/17 10:56:25
// Design Name: 
// Module Name: x7seg_sim
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


module x7seg_sim();
    reg [3:0]x;
    wire [6:0]a_to_g;
    wire [3:0]an;
    x7seg gate(x,a_to_g,an);
    initial
    begin
        x=0;
    end
    always #50 x=x+1;
    

endmodule
