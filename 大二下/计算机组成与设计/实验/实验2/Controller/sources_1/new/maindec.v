`timescale 1ns / 1ps
/* Main decoder：根据输入的opcode判断指令类型，译码得到各元件的控制信号
    aluop[1:0]：alu控制信号
    memtoreg：写回register的数据来自 （R型）ALU计算结果 or （lw）存储器读取的数据
    memwrite：是否需要写（sw）数据寄存器
    //pcsrc：下一个地址是否为PC+4        //不在Controller中实现
    alusrc：传入ALU B端口的值是（addi）32位立即数 or （R/sw/beq）寄存器堆读取的数据
    regdst：写入存储器堆的地址是（lw）rt(0) or （R型）rd(1) （配合regwrite信号）
    regwrite：是否需要写寄存器堆（R型、lw需要写回寄存器堆）
    branch：是否满足branch指令的跳转条件
    jump：是否为jump指令
*/

module maindec(
    input [5:0] op,              //输入opcode
    output reg[1:0] aluop,      //输出alu控制信号
    output reg memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump
);
    always@(*)begin
        case(op)
            6'b000000:begin     //R型
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b1100000;  //顺序按指导书表5
                aluop=2'b10;
            end
            6'b100011:begin     //lw
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b1010010;
                aluop=2'b00;
            end
            6'b101011:begin     //sw
//                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b0z101z0;
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b0010100;
                aluop=2'b00;
            end
            6'b000100:begin     //beq
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b0001000;
                aluop=2'b01;
            end
            6'b001000:begin     //I型(addi)
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b1010000;
                aluop=2'b00;
            end
            6'b000010:begin     //jump
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}=7'b0000001;
                aluop=2'b00;
            end
            default:begin
                {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump}='b0;
                aluop=2'b00;
            end
        endcase
    end
endmodule
