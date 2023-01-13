`timescale 1ns / 1ps

module controller_sim();
    reg[5:0] op;
    reg[5:0] funct;
    wire[2:0] aluctrl;
    wire memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump;
    controller gate(op,funct,aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
    
    initial begin
        op=0;funct=0;
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
        #50 op<=op+1;funct<=funct+1;$display("aluctrl:%b memtoreg:%d memwrite:%d alusrc:%d regdst:%d regwrite:%d branch:%d jump:%d",aluctrl,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
    end

endmodule
