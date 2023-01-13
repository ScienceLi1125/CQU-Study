`timescale 1ns / 1ps
/*Main Decoder模块：将jump,branch,alusrc,memwrite,memetoreg,regwrite,regdst,data_ram_ena合并为sigs，方便输入输出
*/
module main_dec(
    input wire [5:0] op,
    output reg [7:0]sigs,       //合并jump,branch,alusrc,memwrite,memetoreg,regwrite,regdst,data_ram_ena
    // output wire jump,branch,alusrc,memwrite,memetoreg,regwrite,regdst,data_ram_ena,
    output wire [1:0] aluop
);
    reg [1:0] aluop_reg;
    assign aluop = aluop_reg;
    always@(*)  begin 
        case(op)
            6'b000000:begin     //R
                sigs <= 8'b01100000;
                aluop_reg <= 2'b10;
            end
            6'b100011:begin     //lw
                sigs <= 8'b01010011;
                aluop_reg <= 2'b00;
            end
            6'b101011:begin     //sw
                sigs <= 8'b00010101;
                aluop_reg <= 2'b00;
            end
            6'b000100:begin     //beq
                sigs <= 8'b00001000;
                aluop_reg <= 2'b01;
            end
            6'b001000:begin     //addi
                sigs <= 8'b01010000;
                aluop_reg <= 2'b00;
            end
            6'b 000010:begin    //j
                sigs <= 8'b10000000;
                aluop_reg <= 2'b00;
            end
        endcase
    end
endmodule

