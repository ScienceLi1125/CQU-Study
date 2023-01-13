`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/12/01 12:45:57
// Design Name: 
// Module Name: FIFO2
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
/*本实验设计的FIFO存储队列可容纳16个8位2进制数
存储原理：因为存储器读出后不便删除元素，因此将存储器reg [7:0]mem[15:0]视为环形队列，读、写指针在队列容量未满时达到15后归零
*/

module FIFO2(clk,data_in,wr_en,rd_en,rst,data_out,empty,full);
    input clk;                  //时钟信号(原本接系统时钟信号，分频出现问题，改为手动输入时钟信号)
    input [7:0]data_in;         //输入数据
    input wr_en;                //写使能
    input rd_en;                //读使能
    input rst;                  //重置信号
    output reg[7:0]data_out;   //输出数据
    output empty;               //空
    output full;                //满
    
    reg [3:0]counter=0;         //计数器，队列中元素个数
    reg [7:0]mem[15:0];         //存储器核心
    reg [3:0]wr_ptr=0;          //读指针（别忘了初值）
    reg [3:0]rd_ptr=0;          //写指针
    
    assign empty=(counter==0)?1:0;  //由计数器判断队列的满与空
    assign full=(counter==15)?1:0;
    
    always @(posedge clk)
    begin
        if(rst)                 //rst=1时重置所有信号
        begin
            counter<=0;
            data_out<=0;
            wr_ptr<=0;
            rd_ptr<=0;
        end
        else
        begin
            case({wr_en,rd_en}) //判断读与写的操作
                2'b00:counter<=counter;                 //不写会生成锁存器
                2'b01:          //读操作
                begin
                    if(!empty)begin
                        data_out<=mem[rd_ptr];
                        counter<=counter-1;                 //计数器-1
                        rd_ptr<=(rd_ptr==15)?0:rd_ptr+1;    //循环使用
                    end
                    else data_out<=8'bz;
                end
                2'b10:          //写操作
                begin
                    if(!full)begin
                        mem[wr_ptr]<=data_in;
                        counter<=counter+1;                 //计数器+1
                        wr_ptr<=(wr_ptr==15)?0:wr_ptr+1;
                    end
                    else data_out<=data_out;
                end
                2'b11:          //同时读写
                begin                                   //读写各自使用自己的指针，不交叉
                    if(!empty)begin
                        data_out<=mem[rd_ptr];
                        rd_ptr<=(rd_ptr==15)?0:rd_ptr+1;
                        mem[wr_ptr]<=data_in;           //刚读过一定!full
                        wr_ptr<=(wr_ptr==15)?0:wr_ptr+1;
                    end
                    else if(!full)begin                 //队列为空，判断是否写
                        mem[wr_ptr]<=data_in;
                        wr_ptr<=(wr_ptr==15)?0:wr_ptr+1;
                        counter<=counter+1;
                    end
                    else    data_out<=8'bz;             //队列为空输出z
                    
//                    if(!full)begin                    //并行语句对同一变量赋值报错
//                        mem[wr_ptr][7:0]<=data_in;
//                        wr_ptr<=(wr_ptr==15)?0:wr_ptr+1;
//                        counter<=counter+1;
//                    end
                end
                default:counter<=counter;
            endcase
        end
    end
endmodule
