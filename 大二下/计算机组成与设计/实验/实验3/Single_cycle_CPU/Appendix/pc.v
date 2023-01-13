`timescale 1ns / 1ps
/*pc模块：对实验二中PC模块加以修改，接受PC'作为输入，并根据clk输出PC。PC+4的功能放入adder中实现
    否则无法实现branch、jump功能
注意：addr不赋初值仿真会出现问题，第一条指令会被吞掉
*/
module pc(
    input clk,rst,
    input[31:0] pc,
    output reg[31:0] pc_new=0
);
    always@(posedge clk)begin
        if(rst)begin
            pc_new=0;
        end
        else begin
           pc_new=pc;
        end
    end
endmodule
