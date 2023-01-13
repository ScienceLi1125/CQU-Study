`timescale 1ns / 1ps
/*符号扩展模块：将输入16位二进制数扩展为32位*/

module signext(
    input [15:0] a,
    output [31:0] y
    );
    assign y={{16{a[15]}},a};   //有符号数扩展
endmodule
