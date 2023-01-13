`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/20 09:04:16
// Design Name: 
// Module Name: non_stall_pipeline_sim
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


module non_stall_pipeline_sim();
    reg clk;
    reg[7:0] datain;
    wire[7:0] dataout;
    non_stall_pipeline#(8) gate(clk,datain,dataout);
    
    initial begin
        clk=0;
        datain=0;
    end
    always #50 clk=~clk;
    always #49 datain={$random}%256;

endmodule
