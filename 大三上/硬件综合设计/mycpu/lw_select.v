/*lwselect模块
	根据访存指令类型将从内存中读取的整字结果截取并扩展
*/
`timescale 1ns / 1ps
`include "defines.vh"

module lw_select(
    input wire adelW,               //LH、LW指令地址错例外
    input wire [31:0] aluoutW,      //ALU计算出的访存指令地址
    input [7:0] alucontrolW,        //访存指令类型
    input [31:0] lwresultW,         //读取内存的整字结果(4字节)
    output reg [31:0] resultW       //读取内存的真实结果(LB1字节/LH2字节)
    );

    always@ (*) begin
        if(~adelW) begin
            case(alucontrolW)
                `EXE_LB_OP: case(aluoutW[1:0])  //LB指令读取1字节并按符号扩展
                    2'b00: resultW = {{24{lwresultW[7]}},lwresultW[7:0]};
                    2'b01: resultW = {{24{lwresultW[15]}},lwresultW[15:8]};
                    2'b10: resultW = {{24{lwresultW[23]}},lwresultW[23:16]};
                    2'b11: resultW = {{24{lwresultW[31]}},lwresultW[31:24]};
                    default: resultW = lwresultW;
                endcase
                `EXE_LBU_OP: case(aluoutW[1:0]) //LBU指令读取1字节并0扩展
                    2'b00: resultW = {{24{1'b0}},lwresultW[7:0]};
                    2'b01: resultW = {{24{1'b0}},lwresultW[15:8]};
                    2'b10: resultW = {{24{1'b0}},lwresultW[23:16]};
                    2'b11: resultW = {{24{1'b0}},lwresultW[31:24]};
                    default: resultW = lwresultW;
                endcase
                `EXE_LH_OP: case(aluoutW[1:0])  //LH指令读取2字节并按符号扩展
                    2'b00: resultW = {{16{lwresultW[15]}},lwresultW[15:0]};
                    2'b10: resultW = {{16{lwresultW[31]}},lwresultW[31:16]};
                    default: resultW = lwresultW;  
                endcase
                `EXE_LHU_OP:case(aluoutW[1:0])  //LHU指令读取2字节并0扩展
                    2'b00: resultW = {{16{1'b0}},lwresultW[15:0]};
                    2'b10: resultW = {{16{1'b0}},lwresultW[31:16]};
                    default: resultW = lwresultW;    
                endcase
                default: resultW = lwresultW;   //LW指令读取4字节
            endcase
        end
        else begin
            resultW = 32'b0;
        end
    end
endmodule
