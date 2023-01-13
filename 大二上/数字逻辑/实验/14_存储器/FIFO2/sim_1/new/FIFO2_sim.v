`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/12/01 12:49:00
// Design Name: 
// Module Name: FIFO2_sim
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


module FIFO2_sim();
    reg [7:0]data_in;
    reg wr_en=1'b0;
    reg rd_en=1'b0;
    reg clk;
    reg rst;
    //wire [7:0]data_out=8'b0;      //wire²»ÄÜ¸³³õÖµ
    wire [7:0]data_out;
    wire empty;
    wire full;

    FIFO2 gate(clk,data_in,wr_en,rd_en,rst,data_out,empty,full);

    initial
    begin
        clk=0;
        rst=1;
        #1 clk=1;
        #1 rst=0;
        wr_en=1'b1;rd_en=1'b0;
        data_in=0;
        #50 wr_en=1'b1;rd_en=1'b1;
        #50 wr_en=1'b1;rd_en=1'b0;
        #50 wr_en=1'b0;rd_en=1'b1;
        #50 wr_en=1'b1;rd_en=1'b0;
        #50 wr_en=1'b1;rd_en=1'b0;
        #50 wr_en=1'b1;rd_en=1'b0;
        #50 wr_en=1'b0;rd_en=1'b1;
        #50 wr_en=1'b1;rd_en=1'b0;
        #50 wr_en=1'b0;rd_en=1'b1;
        #50 wr_en=1'b1;rd_en=1'b0;
        #50 rst=1;
        #10 rst=0;
    end
        always@(posedge clk)
        begin
            data_in={$random}%256;
        end
        always #50 clk=~clk;

endmodule
