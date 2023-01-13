`timescale 1ns / 1ps

/* ALU模块实现两个32bit数的add、sub、and、or、not、slt功能，
但由于Nexy7输入口限制，将num1简化为8位，在过程中再extend成32位，num2作为内部wire自行赋值，此处赋为5
由于最后的结果在top.v中以七段数码管显示，32位结果不用以led在nexy4显示，因此输出32位结果没有问题*/

module alu(
    input wire [2:0] op,
    input wire [7:0] num1,
    output reg [31:0] result
    );
    wire [31:0] num2;
    wire [31:0] sign_extend_num1;
    assign num2=32'h0000_0001;
    assign sign_extend_num1={24'h0,num1};
    
    always@(*)begin
        case(op)
            3'b000:result=sign_extend_num1+num2;
            3'b001:result=sign_extend_num1-num2;
            3'b010:result=sign_extend_num1&num2;
            3'b011:result=sign_extend_num1|num2;
            3'b100:result=~sign_extend_num1;
            3'b101:begin
                if(sign_extend_num1<num2)   result=32'h0000_0001;
                else                        result=32'h0000_0000;
            end
            default:result=32'hxxxx_xxxx;
        endcase
    end
    
endmodule
