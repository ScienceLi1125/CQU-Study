`timescale 1ns / 1ps
//PCÄ£¿é£¬ÏÂ½µÑØ´¥·¢
module pc(
    input wire clk,rst,en,
    input wire [31:0] din,
    output reg [31:0] q
    );
    always @(negedge clk) begin
        if(rst) q<=32'b0;
        else begin
            if(en != 1) q<=32'b0;
            else q<=din;
        end
    end
endmodule

