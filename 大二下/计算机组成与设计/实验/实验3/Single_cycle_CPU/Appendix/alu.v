`timescale 1ns / 1ps

/* ALU模块实现两个32bit数的add、sub、and、or、not、slt功能
    为缓解较大线路中信号延迟，将alwa语句改为assign
*/

module alu(
    input wire [2:0] op,
    input wire [31:0] num1,
    input wire [31:0] num2,
    output [31:0] result,
    output zero
    );
    assign zero=(result==32'b0) ? 1:0;
    
//    always@(*)begin
//        case(op)
//            3'b000:result=num1+num2;
//            3'b001:result=num1-num2;
//            3'b010:result=num1&num2;
//            3'b011:result=num1|num2;
//            3'b100:result=~num1;
//            3'b101:begin
//                if(num1<num2)   result=32'h0000_0001;
//                else            result=32'h0000_0000;
//            end
//            default:result=32'hxxxx_xxxx;
//        endcase
//    end
    
    assign result = (op==3'b000) ? (num1+num2):
                    (op==3'b001) ? (num1-num2):
                    (op==3'b010) ? (num1&num2):
                    (op==3'b011) ? (num1|num2):
                    (op==3'b100) ? ~num1:
                    (op==3'b101 && num1<num2) ? 32'h0000_0001:
                    (op==3'b101 && num1>=num2) ? 32'h0000_0000:
                    32'h0000_0000;
    
endmodule
