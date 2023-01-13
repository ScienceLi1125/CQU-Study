`timescale 1ns / 1ps
/* Controller：输入IR[31:26]、IR[5:0]，输出
    memtoreg：写回register的数据来自 （R型）ALU计算结果 or （lw）存储器读取的数据
    memwrite：是否需要写（sw）数据寄存器
    pcsrc：下一个地址是否为PC+4
    alusrc：传入ALU B端口的值是（addi）32位立即数 or （R/sw/beq）寄存器堆读取的数据
    regdst：写入存储器堆的地址是（lw）rt(0) or （R型）rd(1) （配合regwrite信号）
    regwrite：是否需要写寄存器堆（R型、lw需要写回寄存器堆）
    branch：是否满足branch指令的跳转条件
    jump：是否为jump指令
    alucontrol：ALU控制信号，只要求实现R型指令的add、sub、and、or、slt
    上述信号除了alucontrol由ALU decoder负责译码输出，其余均在Main decoder中输出。中间信号aluop
由Main decoder输出并输入ALU decoder。

原理：32位MIPS指令在不同类型指令中分别有不同结构。但IR[31:26]表示的opcode，IR[5:0] 表示的funct，
为译码阶段明确指令控制信号的主要字段。根据实验要求，实现R、lw、sw、beq、addi、j型指令的译码。
    由于包含Main decoder和ALU decoder，因此分模块编写，Controller顶层调用。Main decoder输入IR[31:26]
作为opcode，输出memtoreg、memwrite、pcsrc、alusrc、regdst、regwrite、branch、jump和aluop，ALU decoder
输入aluop和IR[5:0]作为funct，输出alu control
*/

module controller(
    input wire[5:0] op,
    input wire[5:0] funct,
    output wire[2:0] aluctrl,
    output wire memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump
);
    wire[1:0] aluop;
    maindec gate1(op,aluop,memtoreg,memwrite,alusrc,regdst,regwrite,branch,jump);
    aludec gate2(aluop,funct,aluctrl);
    
endmodule
