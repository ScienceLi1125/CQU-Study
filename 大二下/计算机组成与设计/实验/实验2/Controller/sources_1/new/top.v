`timescale 1ns / 1ps
/*顶层模块：将pc、clk_div、addr、controller、display模块相连
*/
module top(
    input wire clk,rst,
    output wire[2:0] aluctrl,
    output wire memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump,
    output wire[6:0] seg,
    output wire[7:0] ans
);
    wire clk_division;
    clk_div gate1(clk,clk_division);
    
    wire ena;
    wire[31:0] addr;                    //32bits指令的地址（0~1023）
    pc gate2(clk_division,rst,addr,ena);
    
    wire[31:0] IR;                      //32bits指令
    DisM gate3(addr>>2,clk_division,ena,rst,IR);  //传入ROM的是字节地址，因此要右移2位
    
    controller gate4(IR[31:26],IR[5:0],aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
    
    display gate5(clk,rst,IR,seg,ans);  //display中已经分频

endmodule
