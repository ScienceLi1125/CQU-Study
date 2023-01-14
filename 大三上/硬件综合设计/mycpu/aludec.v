/*aludec模块
    根据op和funct码解码alucontrol。此外,bltz、bltzal、bgez、bgezal需要和寄存器比较因而引入rt
*/
`timescale 1ns / 1ps
`include "defines.vh"

module aludec (
    input [5:0] op,
    input [4:0] rt,     //bltz、bltzal、bgez、bgezal需要用到寄存器rt
    input [5:0] funct,
    output reg [7:0] alucontrol
    );

    always @ (*)    begin
        case (op)
            //logic
            `EXE_ANDI: alucontrol= `EXE_ANDI_OP;   //andi
            `EXE_XORI: alucontrol= `EXE_XORI_OP;   //xori
            `EXE_LUI: alucontrol= `EXE_LUI_OP;     //lui
            `EXE_ORI: alucontrol= `EXE_ORI_OP;     //ori

            //ATH INSTR
            `EXE_ADDI: alucontrol = `EXE_ADDI_OP; //ADDI
            `EXE_ADDIU: alucontrol = `EXE_ADDIU_OP; //ADDIU
            `EXE_SLTI: alucontrol = `EXE_SLTI_OP; //SLTI
            `EXE_SLTIU: alucontrol = `EXE_SLTIU_OP; //SLRIU

            //j,jal
            `EXE_J: alucontrol = `EXE_J_OP; //j
            `EXE_JAL: alucontrol = `EXE_JAL_OP; //jal

            //b-type
            `EXE_BEQ: alucontrol = `EXE_BEQ_OP; //beq
            `EXE_BGTZ: alucontrol = `EXE_BGTZ_OP; //bgtz
            `EXE_BLEZ: alucontrol = `EXE_BLEZ_OP; //blez
            `EXE_BNE: alucontrol = `EXE_BNE_OP; //bne
            `EXE_REGIMM_INST:case(rt) 
                `EXE_BLTZ: alucontrol = `EXE_BLTZ_OP; //bltz
                `EXE_BLTZAL: alucontrol = `EXE_BLTZAL_OP; //bltzal
                `EXE_BGEZ: alucontrol = `EXE_BGEZ_OP; //bgez
                `EXE_BGEZAL: alucontrol = `EXE_BGEZAL_OP; //bgezal
                default:  alucontrol=`EXE_NOP_OP; 
            endcase

            //memory instr
            `EXE_LB: alucontrol = `EXE_LB_OP; //lb
            `EXE_LBU: alucontrol = `EXE_LBU_OP; //lbu
            `EXE_LH: alucontrol = `EXE_LH_OP; //lh
            `EXE_LHU: alucontrol = `EXE_LHU_OP; //lhu
            `EXE_LW: alucontrol = `EXE_LW_OP; //lw
            `EXE_SB: alucontrol = `EXE_SB_OP; //sb
            `EXE_SH: alucontrol = `EXE_SH_OP; //sh
            `EXE_SW: alucontrol = `EXE_SW_OP; //sw


            `EXE_NOP: case(funct)
                //logic instr
                `EXE_AND: alucontrol= `EXE_AND_OP;     //and
                `EXE_OR: alucontrol= `EXE_OR_OP;       //or
                `EXE_XOR: alucontrol= `EXE_XOR_OP;     //xor
                `EXE_NOR: alucontrol= `EXE_NOR_OP;     //nor
                
                //shift instr
                `EXE_SLL: alucontrol= `EXE_SLL_OP;     //sll
                `EXE_SRL: alucontrol= `EXE_SRL_OP;     //srl
                `EXE_SRA: alucontrol= `EXE_SRA_OP;     //sra
                `EXE_SLLV: alucontrol= `EXE_SLLV_OP;   //sllv
                `EXE_SRLV: alucontrol= `EXE_SRLV_OP;   //srlv
                `EXE_SRAV: alucontrol= `EXE_SRAV_OP;   //srav

                //move instr
                `EXE_MFHI: alucontrol= `EXE_MFHI_OP;   //mfhi
                `EXE_MFLO: alucontrol= `EXE_MFLO_OP;   //mflo
                `EXE_MTHI: alucontrol= `EXE_MTHI_OP;   //mthi
                `EXE_MTLO: alucontrol= `EXE_MTLO_OP;   //mtlo

                //ATH INSTR
                `EXE_ADD: alucontrol = `EXE_ADD_OP; //ADD
                `EXE_ADDU: alucontrol= `EXE_ADDU_OP; //ADDU
                `EXE_SUB: alucontrol = `EXE_SUB_OP; //SUB
                `EXE_SUBU: alucontrol = `EXE_SUBU_OP; //SUBU
                `EXE_SLT: alucontrol = `EXE_SLT_OP; //SLT
                `EXE_SLTU:alucontrol = `EXE_SLTU_OP; //SLTU
                `EXE_MULT:alucontrol = `EXE_MULT_OP; //MULT
                `EXE_MULTU: alucontrol = `EXE_MULTU_OP; //MULTU
                `EXE_DIV: alucontrol = `EXE_DIV_OP; //div
                `EXE_DIVU: alucontrol = `EXE_DIVU_OP; //divu

                //jr,jalr
                `EXE_JR: alucontrol = `EXE_JR_OP; //jr
                `EXE_JALR: alucontrol = `EXE_JALR_OP; //jalr

                default: alucontrol = `EXE_NOP_OP;
            endcase
                
            default: alucontrol=`EXE_NOP_OP; 
        endcase
    end
endmodule

