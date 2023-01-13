`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CQU
// Engineer: Calvin Ren
// 
// Create Date: 2021/11/28 19:37:59
// Design Name: Single Port RAM
// Module Name: SP_RAM
// Project Name: Single Port RAM
// Target Devices: basys3
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


module SP_RAM
#(parameter DW = 4,AW = 4)   // data_width & address width
(
    input [AW-1:0]addr,         
    input clk,
    input cs,                // chip select
    input oe,                // output enable
    input we,                // write enable
    input mode_cs,           // mode_cs = 1 sync  mode_cs = 0 asynch
    input [DW-1:0]data_in,      // data in
    output [DW-1:0]data_out     // data output
    );

parameter DP = 1 << AW;      // depth 
reg [DW-1:0]mem[0:DP-1];
reg [DW-1:0]temp1;
reg [DW-1:0]temp2;


// initial 
integer i;
initial begin
    for(i = 0; i < DP; i = i + 1) begin
        mem[i] = 4'h00;
    end
end

// write block
always@(posedge clk)
begin
    if (cs && we)
        begin
            mem[addr] <= data_in;
        end
    else
        begin
            mem[addr] <= mem[addr];
        end
end

//  sync-read block 
always@(posedge clk)
begin
    if (cs && !we && oe && mode_cs)           
        begin
            temp1 <= mem[addr];
        end
end

// asynch-read block
always @(*) 
begin
    if (cs && !we && oe && !mode_cs)
        begin
            temp2 <= mem[addr];
        end    
end


assign data_out = (mode_cs)? temp1 : temp2;

endmodule