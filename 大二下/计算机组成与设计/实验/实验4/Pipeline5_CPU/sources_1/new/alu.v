`timescale 1ns / 1ps
//ALU模块
module alu(
    input [31:0] a, //A端口
    input [31:0] b, //B端口
    input [2:0] op, //运算符控制码
    output wire [31:0] result,  //结果
    output wire zero
    );
    assign result = (op == 3'b010)? a + b:
                    (op == 3'b110)? a - b:
                    (op == 3'b000)? a & b:
                    (op == 3'b001)? a | b:
                    (op == 3'b100)? ~a: 
                    (op == 3'b111)? (a<b):32'h00000000;
    assign zero = (result == 32'b0);
endmodule
