`timescale 1ns / 1ps
//pc模块：根据时钟信号计数，输出当前指令地址
//addr不赋初值仿真会出现问题，第一条指令会被吞掉
module pc(
    input clk,rst,
    output reg[31:0] addr=0,    //连接指令寄存器的输入地址端口
    output wire ena             //连接指令寄存器的使能端口
);
    reg [31:0] cnt=0;           //地址计数，不断+4
    assign ena=(addr<1024)?1:0; //ROM设置的端口Depth为1024，因此>1024的地址为无效地址
//    assign ena =1;
    always@(posedge clk)begin
        if(rst)begin
            cnt=0;
            addr=cnt;
        end
        else begin
           cnt=cnt+4;
           addr=cnt;
        end
    end
endmodule
