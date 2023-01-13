`timescale 1ns / 1ps

module mips_sim();
    reg clk=1,rst=0;
    reg[31:0] IR=0;
    wire[31:0] pc_out;
    wire memwrite;
    wire[31:0] aluout,writedata;
    reg[31:0] readdata=0;
    mips gate(clk,rst,IR,pc_out,memwrite,aluout,writedata,readdata);
    always #10 clk=~clk;
//    always #19 begin IR[15:0]={$random}%65536;IR[31:16]={$random}%65536;end
//    always #19 begin readdata[15:0]={$random}%65536;readdata[31:16]={$random}%65536;end
    initial begin
        #20 IR=32'h20020005;
        #20 IR=32'h2003000c;
        #20 IR=32'h2067fff7;
        #20 IR=32'h00e22025;
        #20 IR=32'h00642824;
        #20 IR=32'h00a42820;
        #20 IR=32'h10a7000a;
    end

endmodule
