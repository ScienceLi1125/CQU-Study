`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/29 22:52:36
// Design Name: 
// Module Name: DP_RAM_sim
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


module DP_RAM_sim();
reg clk;
reg we;
reg [2:0]addr_a=0;
reg [2:0]addr_b=0;
reg cs;
wire [2:0]dout_a;
wire [2:0]dout_b;
reg [2:0]data_a;
reg [2:0]data_b;
integer i;

initial begin:Clocking
    clk=0;
    #10 forever 
    #10 clk=!clk;
end

initial begin
    #10
    we = 1'b0; cs = 1'b0;
    #10
    we = 1'b1; cs = 1'b1;
    #10 we = 1'b1; cs = 1'b1;

    for (i = 0; i < 5; i = i + 1) begin
        @(negedge clk) begin
            addr_a = i;
            data_a = i + 1;
        end
    end

    #120
    #10
    we = 1'b1; cs = 1'b0;

    for (i = 0; i < 5; i = i + 1) begin
        @(negedge clk) begin
            addr_b = i;
            data_b = i;
        end
    end

    #120
    #10
    we = 1'b0; cs = 1'b0;

    for(i = 0; i < 5; i = i + 1) begin
        @(negedge clk) begin
            addr_b=i;
        end
    end

    #120
    #10
    we = 1'b0; cs = 1'b1;

    for(i = 0; i < 5; i = i + 1) begin
        @(negedge clk) begin
            addr_a = i;
        end
    end

    disable Clocking;
end
DP_RAM u(.cs(cs), .addr_b(addr_b), .addr_a(addr_a), .clk(clk), .we(we), .data_a(data_a), .data_b(data_b), .data_aout(dout_a), .data_bout(dout_b));

endmodule
