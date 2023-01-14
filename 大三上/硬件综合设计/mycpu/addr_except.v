/*lwswexcept模块
	LH指令的访存地址不是2的整数倍或LW指令的访存地址不是4的整数倍会触发地址错例外adelM
    SH指令的访存地址不是2的整数倍或SW指令的访存地址不是4的整数倍会触发地址错例外adesM
    adelM: address exception of load instruction in MEM stage
    adesM: address exception of save instruction in MEM stage
*/
`timescale 1ns / 1ps
`include "defines.vh"

module addr_except(
    input [31:0] addrs,     //访存地址
    input [7:0] alucontrolM,//访存类型
    output reg adelM,       //LH、LW指令地址错例外
    output reg adesM        //LH、LW指令地址错例外
    );
    
    always@(*) begin
        adelM <= 1'b0;      //赋初值,否则生成latch
        adesM <= 1'b0;
        case (alucontrolM)
            `EXE_LH_OP: if (addrs[1:0] != 2'b00 & addrs[1:0] != 2'b10 ) begin
                adelM <= 1'b1;
            end
            `EXE_LHU_OP: if ( addrs[1:0] != 2'b00 & addrs[1:0] != 2'b10 ) begin
                adelM <= 1'b1;
            end
            `EXE_LW_OP: if ( addrs[1:0] != 2'b00 ) begin
                adelM <= 1'b1;
            end
            `EXE_SH_OP: if (addrs[1:0] != 2'b00 & addrs[1:0] != 2'b10 ) begin
                adesM <= 1'b1;
            end
            `EXE_SW_OP: if ( addrs[1:0] != 2'b00 ) begin
                adesM <= 1'b1;
            end
            default: begin
                adelM <= 1'b0;
                adesM <= 1'b0;
            end
        endcase
    end
endmodule
