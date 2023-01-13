`timescale 1ns / 1ps
/*移位模块sl2：将输入的32位data左移两位*/

module sl2(
    input [31:0] a,
    output [31:0] y
    );
    assign y={a[29:0],2'b00};
    
endmodule
