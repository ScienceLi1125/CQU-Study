`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/20 09:54:50
// Design Name: 
// Module Name: stallable_pipeline_sim
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


module stallable_pipeline_sim();
    reg clk;
    reg rst;
    reg validin;
    reg [7:0] datain;
    reg out_allow;
    wire validout;
    wire [7:0] dataout;
    
    stallable_pipeline#(8) gate(clk,rst,validin,datain,out_allow,validout,dataout);
    initial begin
        clk=0;
        rst=0;
        validin=1;
        datain=0;
        out_allow=1;
        #50 rst=~rst;
        #50 rst=~rst;
        #200 rst=~rst;
        #50 rst=~rst;
    end
    always #50 clk=~clk;
    always #21 datain={$random}%256;

endmodule
