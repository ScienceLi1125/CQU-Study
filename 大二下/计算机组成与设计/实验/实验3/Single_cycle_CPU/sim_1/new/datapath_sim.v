`timescale 1ns / 1ps

module datapath_sim();
    reg clk=0,rst=1;
    reg[2:0] aluctrl;
    reg memtoreg,alusrc,regdst,regwrite,pcsrc;
    reg jump;
    reg[31:0] readdata;
    reg[31:0] IR;
    wire[31:0] aluresult,writedata,pc_out;
    wire zero;
    datapath gate(clk,rst,aluctrl,memtoreg,alusrc,regdst,regwrite,pcsrc,jump,readdata,IR,aluresult,writedata,pc_out,zero);
    initial begin    #1 rst=0;jump=0;end
    always #37 clk=~clk;
    always #20 {memtoreg,alusrc,regdst,regwrite,pcsrc}={$random}%32;
    always #20 aluctrl={$random}%8;
    always #20 readdata={$random}%1048576;
    always #20 IR={$random}%1048576;
endmodule
