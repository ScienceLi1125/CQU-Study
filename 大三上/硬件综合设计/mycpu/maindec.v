/*maindec模块
    根据指令instrD解码控制信号
*/
`timescale 1ns / 1ps
`include "defines.vh"

module maindec(
    input wire [31:0] instrD,
    input wire [5:0] op,
    input wire [5:0] funct,
    input wire [4:0] rt,
    output memtoreg, 
    output branch, alusrc,
    output regdst, regwrite,
    output jump,jal,jr,bal,memen,hilo,
    output  breakM,syscall,reserve,eret,
    output  cp0we,cp0sel
    );

    reg [16:0] controls;
    assign {regwrite, regdst, alusrc,branch,memtoreg,jump,jal,jr,bal,memen,hilo,breakM,syscall,reserve,eret,cp0we,cp0sel} = controls;
    // regwrite 是否需要写入寄存器 1是 0否
    // regdst 写入寄存器rd还是rt 1rd 0rt
    // alusrc alu的第二个操作数是否来自立即数 1是 0否
    // branch 是否是分支指令 1是 0否

    // memtoreg WB阶段写回寄存器堆的是否来自内存 1是 0否
    // jump j跳转指令 1是 0否
    // jal jal跳转指令 1是 0否
    // jr jr跳转指令 1是 0否
    // bal bal跳转指令（包括bltzal和bgezal） 1是 0否
    // memen data ram使能信号 1是 0否
    // hilo 是否需要写入hilo寄存器 1是 0否

    // break 是否为break信号 1是 0否
    // syscall 是否为syscall信号 1是 0否
    // reserve 是否为reserve信号 1是 0否
    // eret 是否为eret信号 1是 0否
    // cp0we cp0写使能信号 1是 0否
    // cp0sel 是否要读cp0 1是 0否
    always @ (*) begin
        case(op)
            //I-type instr in logic instr
            `EXE_ANDI: controls = 17'b1010_0000000_000000; //andi
            `EXE_XORI: controls = 17'b1010_0000000_000000; //xori
            `EXE_LUI: controls = 17'b1010_0000000_000000; //lui
            `EXE_ORI: controls = 17'b1010_0000000_000000; //ori
            
            //Arithmatic_Instr
            `EXE_ADDI: controls = 17'b1010_0000000_000000; //ADDI
            `EXE_ADDIU: controls = 17'b1010_0000000_000000; //ADDIU
            `EXE_SLTI: controls = 17'b1010_0000000_000000; //SLTI
            `EXE_SLTIU: controls = 17'b1010_0000000_000000; //SLTIU

            //j,jal
            `EXE_J: controls = 17'b0000_0100000_000000; //j
            `EXE_JAL: controls = 17'b1000_0010000_000000; //jal

            //b-type
            `EXE_BEQ: controls = 17'b0001_0000000_000000; //beq
            `EXE_BGTZ: controls = 17'b0001_0000000_000000; //bgtz
            `EXE_BLEZ: controls = 17'b0001_0000000_000000; //blez
            `EXE_BNE: controls = 17'b0001_0000000_000000; //bne
            `EXE_REGIMM_INST:case(rt) 
                `EXE_BLTZ: controls = 17'b0001_0000000_000000; //bltz
                `EXE_BLTZAL: controls = 17'b1001_0000100_000000; //bltzal
                `EXE_BGEZ: controls = 17'b0001_0000000_000000; //bgez
                `EXE_BGEZAL: controls = 17'b1001_0000100_000000; //bgezal
                default: controls = 17'b0;
            endcase
            
            //memory instr
            `EXE_LB: controls = 17'b1010_1000010_000000; //lb
            `EXE_LBU: controls = 17'b1010_1000010_000000; //lbu
            `EXE_LH: controls = 17'b1010_1000010_000000; //lh
            `EXE_LHU: controls = 17'b1010_1000010_000000; //lhu
            `EXE_LW: controls = 17'b1010_1000010_000000; //lw
            `EXE_SB: controls = 17'b0010_0000010_000000; //sb
            `EXE_SH: controls = 17'b0010_0000010_000000; //sh
            `EXE_SW: controls = 17'b0010_0000010_000000; //sw

            //op为000000
            `EXE_NOP:case(funct)
                //move instr
                `EXE_MTHI: controls = 17'b0000_0000001_000000;    //mthi
                `EXE_MTLO: controls = 17'b0000_0000001_000000;    //mtlo
                `EXE_MFHI: controls = 17'b1100_0000001_000000;    //mfhi
                `EXE_MFLO: controls = 17'b1100_0000001_000000;    //mflo

                //mult instr
                `EXE_MULT: controls = 17'b0000_0000001_000000;    //mult
                `EXE_MULTU: controls = 17'b0000_0000001_000000;   //multu
                //div instr
                `EXE_DIV: controls = 17'b0000_0000001_000000;     //div
                `EXE_DIVU: controls = 17'b0000_0000001_000000;     //divu
                //jr,jalr
                `EXE_JR: controls = 17'b0000_0001000_000000;      //jr
                `EXE_JALR: controls = 17'b1100_0001000_000000;    //jalr
                //break,syscall
                `EXE_BREAK: controls = 17'b0000_0000000_100000;  //break
                `EXE_SYSCALL: controls = 17'b0000_0000000_010000;    //syscall
                
                default: controls = 17'b1100_0000000_000000;       //r-type
            endcase

            //special instr
            6'b010000: begin
                if (instrD == `EXE_ERET)
                    controls = 17'b0000_0000000_000100;      //eret
                else if (instrD[25:21]==5'b00100 && instrD[10:3]==0)
                    controls = 17'b0000_0000000_000010;      //mtc0
                else if (instrD[25:21]==5'b00000 && instrD[10:3]==0)
                    controls = 17'b1000_0000000_000001;      //mfc0
                else
                    controls = 17'b0000_0000000_001000;
            end

            default: controls = 17'b0000_0000000_001000;     

        endcase
    end
endmodule

