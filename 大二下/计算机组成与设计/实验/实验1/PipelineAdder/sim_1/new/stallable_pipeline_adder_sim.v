`timescale 1ns / 1ps
/*仿真要求：
1.模拟流水线暂停，仿真时控制 10 周期后暂停流水线 2 周期（第 2 级），流水线恢复流动；
2.模拟流水线刷新，仿真时控制 15 周期时流水线刷新（第 3 级）。
注意：仿真中应该用非阻塞赋值！
*/

module stallable_pipeline_adder_sim();
    reg clk;
    reg[3:0] refresh;
    reg[3:0] halt;
    reg[31:0] cin_a;
    reg[31:0] cin_b;
    reg c_in;
    wire c_out;
    wire[31:0] sum_out;
    stallable_pipeline_adder gate(clk,refresh,halt,cin_a,cin_b,c_in,c_out,sum_out);
    
    initial begin
        clk=0;refresh=0;halt=0;cin_a=0;cin_b=0;c_in=0;
        #50 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //75ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //125ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //175ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //225ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //275ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //325ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //375ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //425ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //475ns
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //525ns||10周期
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;;halt[1]<=1; //2级流水线暂停
        #25 clk<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;halt[1]<=0;    //流水线恢复
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;  //14周期
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;refresh[2]<=1;
        #25 clk<=0;refresh[2]<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;
        #25 clk<=1;cin_a<={$random}%4096;cin_b<={$random}%4096;c_in<={$random}%2;
        #25 clk<=0;
    
    end
endmodule
