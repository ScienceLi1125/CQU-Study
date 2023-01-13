`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/29 22:52:11
// Design Name: 
// Module Name: DP_RAM
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


module DP_RAM
#(parameter AW = 3, DW = 3)
(
    input cs,  //
    input [AW-1:0]addr_a,
    input [AW-1:0]addr_b,
    input clk,
    input we,
    input [DW-1:0]data_a,
    input [DW-1:0]data_b,
    output [DW-1:0] data_aout,
    output [DW-1:0] data_bout
    );   

parameter DP = 1 << AW;   

reg [DW-1:0] data_aout;
reg [DW-1:0] data_bout;
reg [DW-1:0]mem_a[0:DP-1];
reg [DW-1:0]mem_b[0:DP-1];



// write & sync-read block
always @(posedge clk) begin
    if (we) begin
            if(cs) begin
                mem_a[addr_a] <= data_a;
                data_aout <= 0;
            end
            else begin
                mem_b[addr_b] <= data_b;
                data_bout <= 0;
            end
        end
    else begin
        if (cs)
            data_aout <= mem_a[addr_a];
        else
            data_bout <= mem_b[addr_b];
        end
end

endmodule



