/*cp0_reg模块
    CP0寄存器，处理中断和异常
*/
`timescale 1ns / 1ps
`include "defines.vh"

module cp0_reg(
	input wire clk,
	input wire rst,
	input wire we_i,						//CP0的写使能
	input[4:0] waddr_i,						//CP0的写地址
	input[4:0] raddr_i,						//CP0的读地址
	input[`RegBus] data_i,					//CP0的写数据
	input wire[5:0] int_i,					//cause[15:10]的写数据，每一位对应一个硬件中断
	input wire[`RegBus] excepttype_i,		//异常类型
	input wire[`RegBus] current_inst_addr_i,//当前指令
	input wire is_in_delayslot_i,			//是否处于延迟槽
	input wire[`RegBus] bad_addr_i,			//发生地址错例外的访存地址

	output reg[`RegBus] data_o,				//CP0的读数据
	output reg[`RegBus] count_o,			//处理器内部计数器，两个时钟计数一次
	output reg[`RegBus] compare_o,			//与count寄存器共同完成定时器中断功能：当Coumt==Compare，产生定时器中断，该中断一直持续到有数据被写入Compare
	output reg[`RegBus] status_o,			//处理器状态与控制寄存器
	output reg[`RegBus] cause_o,			//上一次例外原因
	output reg[`RegBus] epc_o,				//上一次发生例外指令的PC
	output reg[`RegBus] config_o,			//输出CPU的参数，如处理器各种配置和功能信息
	output reg[`RegBus] prid_o,				//输出处理器标志和版本，如制造商信息、处理器类型、处理器版本
	output reg[`RegBus] badvaddr,			//上一次发生地址错例外的访存地址
	output reg timer_int_o					//是否处于时钟中断
    );

	//写数据
	always @(posedge clk) begin
		if (rst == `RstEnable) begin
			count_o <= `ZeroWord;
			compare_o <= `ZeroWord;
			status_o <= 32'b00010000000000000000000000000000;
			cause_o <= `ZeroWord;
			epc_o <= `ZeroWord;
			config_o <= 32'b00000000000000001000000000000000;
			prid_o <= 32'b00000000010011000000000100000010;
			timer_int_o <= `InterruptNotAssert;
		end else begin
			count_o <= count_o + 1;
			cause_o[15:10] <= int_i;
			if(compare_o != `ZeroWord && count_o == compare_o) begin
				//COUNT寄存器和COMPARE寄存器的值相等时，触发时钟中断
				timer_int_o <= `InterruptAssert;
			end
			if(we_i == `WriteEnable) begin
				//写寄存器
				case (waddr_i)
					`CP0_REG_COUNT:begin 
						count_o <= data_i;
					end
					`CP0_REG_COMPARE:begin 
						compare_o <= data_i;
						timer_int_o <= `InterruptNotAssert;
					end
					`CP0_REG_STATUS:begin 
						status_o <= data_i;
					end
					`CP0_REG_CAUSE:begin 
						cause_o[9:8] <= data_i[9:8];
						cause_o[23] <= data_i[23];
						cause_o[22] <= data_i[22];
					end
					`CP0_REG_EPC:begin 
						epc_o <= data_i;
					end
					default : /* default */;
				endcase
			end
			case (excepttype_i)
				32'h00000001:begin 		//中断
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b00000;
				end
				32'h00000004:begin 		//读地址错例外
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b00100;
					badvaddr <= bad_addr_i;
				end
				32'h00000005:begin 		//写地址错例外
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b00101;
					badvaddr <= bad_addr_i;
				end
				32'h00000008:begin 		//系统调用例外
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b01000;
				end
				32'h00000009:begin 		//断点例外
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b01001;
				end
				32'h0000000a:begin 		//保存指令例外
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b01010;
				end
				32'h0000000c:begin 		//算术溢出例外
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b01100;
				end
				32'h0000000d:begin 
					if(is_in_delayslot_i == `InDelaySlot) begin
						/* code */
						epc_o <= current_inst_addr_i - 4;
						cause_o[31] <= 1'b1;
					end else begin 
						epc_o <= current_inst_addr_i;
						cause_o[31] <= 1'b0;
					end
					status_o[1] <= 1'b1;
					cause_o[6:2] <= 5'b01101;
				end
				32'h0000000e:begin 
					status_o[1] <= 1'b0;
				end
				default : /* default */;
			endcase
		end
	end

	//读数据
	always @(*) begin
		if(rst == `RstEnable) begin
			/* code */
			data_o = `ZeroWord;
		end else begin 
			case (raddr_i)
				`CP0_REG_COUNT:begin 
					data_o = count_o;
				end
				`CP0_REG_COMPARE:begin 
					data_o = compare_o;
				end
				`CP0_REG_STATUS:begin 
					data_o = status_o;
				end
				`CP0_REG_CAUSE:begin 
					data_o = cause_o;
				end
				`CP0_REG_EPC:begin 
					data_o = epc_o;
				end
				`CP0_REG_PRID:begin 
					data_o = prid_o;
				end
				`CP0_REG_CONFIG:begin 
					data_o = config_o;
				end
				`CP0_REG_BADVADDR:begin 
					data_o = badvaddr;
				end
				default : begin 
					data_o = `ZeroWord;
				end
			endcase
		end
	end
endmodule
