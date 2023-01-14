/*alu模块
    包含除除法以外的所有计算指令,并提供除法要用到的信号
*/
`timescale 1ns / 1ps
`include "defines.vh"

module alu(
    input wire [31:0] a,
    input wire [31:0] b,
    input wire [7:0] alucontrol,
    input wire [4:0] sa,        //移位指令的sa
    input wire [15:0] offset,   //分支跳转指令的offset
    output reg [31:0] result,
    input [63:0] hilo_in,       //数据移动指令需要的hilo
    output reg [63:0] hilo_out,
    output reg overflow
    );

    always @(*) begin
        result = 32'h00000000;  //赋初值,否则生成latch
        hilo_out = 0;
        overflow = 0;
        case(alucontrol)
            //logic instr
            `EXE_AND_OP: begin result = a & b;   overflow = 0; end  //and
            `EXE_OR_OP: begin result = a | b;      overflow = 0; end //or
            `EXE_XOR_OP: begin result = a ^ b;     overflow = 0; end //xor
            `EXE_NOR_OP: begin result = ~(a | b);      overflow = 0; end //nor
            `EXE_ANDI_OP: begin result = a & b;        overflow = 0; end //andi
            `EXE_XORI_OP:begin  result = a ^ b;        overflow = 0; end //xori
            `EXE_LUI_OP: begin result ={ b[15:0],16'b0 };     overflow = 0; end //lui
            `EXE_ORI_OP: begin result = a | b;         overflow = 0; end //ori

            //shift instr
            `EXE_SLL_OP: begin result = b << sa;     overflow = 0; end  //sll
            `EXE_SRL_OP: begin result = b >> sa;      overflow = 0; end //srl
            `EXE_SRA_OP: begin result = ({32{b[31]}} << (6'd32 -{1'b0,sa})) | b >> sa;      overflow = 0; end  //sra
            `EXE_SLLV_OP: begin result = b << a[4:0];      overflow = 0; end //sllv
            `EXE_SRLV_OP:begin  result = b >> a[4:0];      overflow = 0; end //srlv
            `EXE_SRAV_OP: begin result = ({32{b[31]}} << (6'd32 -{1'b0,a[4:0]})) | b >> a[4:0];       overflow = 0; end //srav

            //move instr
            `EXE_MTHI_OP: begin hilo_out = {a,hilo_in[31:0]};       overflow = 0; end //mthi
            `EXE_MTLO_OP: begin hilo_out = {hilo_in[31:0],a};      overflow = 0; end //mtlo
            `EXE_MFHI_OP: begin result = hilo_in[63:32];             overflow = 0; end //mfhi
            `EXE_MFLO_OP: begin result = hilo_in[31:0];              overflow = 0; end //mflo

            //ath instr
            `EXE_ADD_OP: begin result = a + b; overflow = (~result[31] & a[31] & b[31]) | (result[31] & ~a[31] & ~b[31]); end //add
            `EXE_ADDU_OP: result = a + b;  //addu
            `EXE_SUB_OP: begin result = a - b; overflow = (~result[31] & a[31] & ~b[31]) | (result[31] & ~a[31] & b[31]); end //sub
            `EXE_SUBU_OP:  result = a - b;  //subu
            `EXE_SLT_OP: begin result = ($signed(a) < $signed(b))?1:0; overflow = 0; end //slt
            `EXE_SLTU_OP: begin result = a<b? 32'b1:32'b0; overflow = 0; end //stlu
            `EXE_MULT_OP: begin hilo_out = $signed(a)*$signed(b); overflow = 0; end //mult
            // `EXE_MULTU_OP: begin hilo_out = $unsigned(a)*$unsigned(b); overflow = 0; end //multu
            `EXE_MULTU_OP: begin hilo_out = {32'b0,a}*{32'b0,b}; overflow = 0; end //multu
            
            `EXE_ADDI_OP:begin result = a + b; overflow = (~result[31] & a[31] & b[31]) | (result[31] & ~a[31] & ~b[31]); end //addi
            `EXE_ADDIU_OP: begin result = a + b; overflow = 0; end //addiu
            `EXE_SLTI_OP: begin result = ($signed(a) < $signed(b))?1:0; overflow = 0; end //slti
            `EXE_SLTIU_OP: begin result = a < b? 32'b1:32'b0; overflow = 0; end //sltiu

            //memory instr
            `EXE_LB_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //lb
            `EXE_LBU_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //lbu
            `EXE_LH_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //lh
            `EXE_LHU_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //lhu
            `EXE_LW_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //lw
            `EXE_SB_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //sb
            `EXE_SH_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //sh
            `EXE_SW_OP: begin result = a + {{16{offset[15]}}, offset };  overflow = 0; end //sw
            
            default: begin result = 32'h00000000; overflow = 0; hilo_out = 0;end 
        endcase
    end
endmodule