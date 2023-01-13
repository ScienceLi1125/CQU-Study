`timescale 1ns / 1ps

/*实验要求：
  1.实现4级流水线32bit全加器，每一级进行8bit加法运算，需带有流水线暂停和刷新；
  2.模拟流水线暂停，仿真时控制10周期后暂停流水线2周期（第2级），流水线恢复流动；
  3.模拟流水线刷新，仿真时控制15周期时流水线刷新（第3级）。
  流水线的作用在于将大问题分解成小问题，如果有10000组a和b相加，流水线只需要(10000+3)T
而常规加法器需要10000*4T
  实现思路：将32位数据分为4级，第1级计算a[7:0]+b[7:0]，第2级计算a[8:15]+b[8:15]，第3级
计算a[16:23]+b[16:23]，第4级计算a[24:31]+b[24:31]，其中每级之间加入流水线寄存器，存储
进位、还没加的数据以及已经加得的和
  实验还要求实现对各级分别暂停和刷新，原本考虑加入valid记录两级之间是否可以传送数据，后
来被if...else取代
若某一级被暂停，则前面的几级会先执行完当前操作然后暂停，后面几级会执行完毕然后暂停；
若某一级被刷新，则该级的数据全部清零，只影响一次结果
  注意：流水线应该采用非阻塞赋值，体现流水线思想，否则在同一周期计算出结果
*/

module stallable_pipeline_adder(
    input clk,
    input [3:0] refresh,    //流水线刷新
    input [3:0] halt,       //流水线暂停
    input [31:0] cin_a,     //加数a
    input [31:0] cin_b,     //被加数b
    input c_in,             //前一级对当前级的进位
    output reg c_out,       //当前一级对后一级的进位
    output reg[31:0] sum_out    //和
    );
    reg c_out_12,c_out_23,c_out_34;    //流水线寄存器，存储进位
    //reg [7:0] sum1,sum2,sum3;         //因为流水线寄存器每一次clk进来都会被覆盖，所以不能每一级8位等到最后合并
    reg [7:0] sum1;                     //流水线寄存器，存储当前和
    reg [15:0] sum2;
    reg [23:0] sum3;
    reg [23:0] tmpa1,tmpb1;             //存储还没计算的23位a、b
    reg [15:0] tmpa2,tmpb2;
    reg [7:0] tmpa3,tmpb3;
    //assign tmpa1=cin_a[31:8];         //不能用assign连续赋值，否则下一周期传入新的a上一周期的a会被覆盖

//    reg go1,go2,go3;                    //表示某一级允许向下一级传数据
//    reg come2,come3,come4;              //表示某一级允许接受上一级数据
//    wire valid_12,valid_23,valid_34;    //表示某两级之间允许传递数据
//    assign valid_12=go1&come2;          //前后两级同时满足才可以传递数据
//    assign valid_23=go2&come3;
//    assign valid_34=go3&come4;

    // pipeline 1
    always@(posedge clk)begin
        if(halt[0])begin
        //1级流水线暂停会使得后续流水线完成手头工作后都停下，因此向2级传Z
            {c_out_12,sum1}<='bz;
            tmpa1<='bz;
            tmpb1<='bz;
        end
        else if(refresh[0])begin
            {c_out_12,sum1}<=9'b0;
            tmpa1<=24'b0;
            tmpb1<=24'b0;
        end
        else begin                      //pipeline 1不用考虑被前一级暂停
            {c_out_12,sum1}<=cin_a[7:0]+cin_b[7:0];
            tmpa1<=cin_a[31:8];
            tmpb1<=cin_b[31:8];
//            go1<=1;
        end
    end
    // pipeline 2
    always@(posedge clk)begin
        if(halt[1])begin
        //2级流水线暂停对1级没有影响，2级可以不使用1级传入的数据
            {c_out_23,sum2}<='bz;
            tmpa2<='bz;
            tmpb2<='bz;
        end
        else if(refresh[1])begin
            {c_out_23,sum2}<=17'b0;
            tmpa2<=16'b0;
            tmpb2<=16'b0;
        end
        else begin
            if(c_out_12===1'bz)begin    //前一级暂停
                sum2[7:0]<='bz;
                {c_out_23,sum2[15:8]}<='bz;
                tmpa2<='bz;
                tmpb2<='bz;
            end
            else begin
                sum2[7:0]<=sum1;
                {c_out_23,sum2[15:8]}<=tmpa1[7:0]+tmpb1[7:0]+c_out_12;
                tmpa2<=tmpa1[23:8];
                tmpb2<=tmpb1[23:8];
    //            go2<=1;
    //            come2<=1;
            end
        end
    end
    // pipeline 3
    always@(posedge clk)begin
        if(halt[2])begin
            {c_out_34,sum3}<='bz;
            tmpa3<='bz;
            tmpb3<='bz;
        end
        else if(refresh[2])begin
            {c_out_34,sum3}<=25'b0;
            tmpa3<=8'b0;
            tmpb3<=8'b0;
        end
        else begin
            if(c_out_23===1'bz)begin    //前一级暂停
                sum3[15:0]<='bz;
                {c_out_34,sum3[23:16]}<='bz;
                tmpa3<='bz;
                tmpb3<='bz;
            end
            else begin
                sum3[15:0]<=sum2;
                {c_out_34,sum3[23:16]}<=tmpa2[7:0]+tmpb2[7:0]+c_out_23;
                tmpa3<=tmpa2[15:8];
                tmpb3<=tmpb2[15:8];
    //            go3<=1;
    //            come3<=1;
            end
        end
    end
    // pipeline 4
    always@(posedge clk)begin
        if(halt[3])begin
//            {c_out,sum_out}<=33'bzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz;    //超出32位限制
            c_out<='bz;
            sum_out<='bz;
        end
        else if(refresh[3])begin
            c_out<='b0;
            sum_out<='b0;
        end
        else begin
            if(c_out_34===1'bz)begin
                sum_out[23:0]<='bz;
                {c_out,sum_out[31:24]}<='bz;
            end
            else begin
                sum_out[23:0]<=sum3;
                {c_out,sum_out[31:24]}<=tmpa3[7:0]+tmpb3[7:0]+c_out_34;
    //            come4<=1;
            end
        end
    end

    
endmodule
