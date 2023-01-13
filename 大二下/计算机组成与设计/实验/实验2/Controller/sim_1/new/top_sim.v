`timescale 1ns / 1ps
/*仿真时不需要分频，因此不能直接使用top模块
*/

module top_sim();
    reg clk=0,rst=0;
    wire[31:0] IR;
    wire[2:0] aluctrl;
    wire memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump;
    
    wire ena;
    wire[31:0] addr;
    pc gate2(clk,rst,addr,ena);
    DisM gate3(addr>>2,clk,ena,rst,IR);
    controller gate4(IR[31:26],IR[5:0],aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
    
    always #50 begin
        clk<=~clk;
        $display("instruction:%h aluctrl:%b memtoreg:%b memwrite:%b alusrc:%b regdst:%b regwrite:%b branch:%b jump:%b",IR,aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
    end
    
endmodule
