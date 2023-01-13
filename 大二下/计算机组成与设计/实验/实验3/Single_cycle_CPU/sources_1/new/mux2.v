`timescale 1ns / 1ps
/*二选一选择器
    使用always赋值会在线路较多时出现延迟，改用assign赋值消除延迟
*/

module mux2#(parameter WIDTH=32)(
    input [WIDTH-1:0] a,
    input [WIDTH-1:0] b,
    input sel,
    output [WIDTH-1:0] c 
    );
//    always@(*)begin
//        if(!sel)    c=a;
//        else        c=b;
//    end
    assign c = sel ? b:a;
    
endmodule
