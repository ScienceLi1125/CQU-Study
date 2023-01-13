`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/28 21:23:06
// Design Name: 
// Module Name: SP_RAM_sim
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


module SP_RAM_sim();

// port declaration
reg [3:0]addr;
reg clk, cs, oe, we;
reg [3:0]data_in;
reg mode_cs;
wire [3:0]data_out;
integer i;



initial
begin
    clk = 1'b0;
    forever #4 clk = ~clk; 
end

// initilize 
initial
begin
    cs = 1'b0;
    oe = 1'b1;
    mode_cs = 1'b1;    // mode_cs : sync-read
    we = 1'b0;
    addr = 4'd0;
    data_in = 4'h00;
    #20 
    @(negedge clk) // read
    cs = 1'b1;

    for (i = 0; i < 16; i = i + 1) begin
        @(negedge clk)
            addr = i;
    end

    // write the data
    @(negedge clk) 
        we = 1'b1;
    for (i = 0; i < 16; i = i + 1) begin
        @(negedge clk) begin
            addr = i;
            data_in = data_in + 1'b1;
        end
    end

    // read the data
    @(negedge clk)  
        we = 1'b0;
    for (i = 0; i < 16; i = i + 1) begin
        @(posedge clk)
            addr = i;
    end
    #5
    mode_cs = 0;    // mode change: asynch-read
    repeat(15) begin
        #20 addr = addr - 1'b1;
    end
    @(negedge clk) 
        cs = 1'b0;
    

    
    
end
    SP_RAM #(.AW(4), .DW(8)) ux (
      .addr(addr),      // input wire [3 : 0] a
      .data_in(data_in),      // input wire [7 : 0] d
      .clk(clk),  // input wire clk
      .we(we),    // input wire we
      .cs(cs), 
      .oe(oe),
      .mode_cs(mode_cs),
      .data_out(data_out)  
    );
endmodule
