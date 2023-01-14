/*div模块,支持有符号和无符号运算,参考https://blog.csdn.net/leishangwen/article/details/39155487
    时序逻辑,需要32个周期,主要部分是一个状态机:
    DivFree:除法模块空闲
    DivByZero:除数是0
    DivOn:除法运算进行中
    DivEnd:除法运算结束
复位时DIV模块处于DivFree状态，当start_i为DivStart(1)且annul_i为0时，除法操作开始：
    如果除数opdata2_i为0，进入DivByZero状态，除法结果为0。然后进入DivEnd状态，通知EX模块除法运算结果得到，后者设置start_i为DivStop(0)，除法运算结束。
    否则进入DivOn状态，经过32个时钟周期得出除法结果。然后进入DivEnd状态，通知EX模块除法运算结果得到，后者会设置start_i为DivStop(0)，除法运算结束。
DivOn时试商法过程:
    因为除法指令的时钟周期数必须固定，所以不可能从可以除尽的位灵活开始，因此选择将被除数一位一位向左移供除数去减;
    dividend低32位初始化为被除数，每执行一次试商就整体左移一位，并将当前位的商写在最低位;
    第k次迭代后dividend[k-1:0]保存得到的中间结果，dividend[31:k]保存的就是被除数中还没有参与运算的部分，即作差后剩余的数;
    dividend[63:32]是被减数，除数是减数，此处作差，结果保存在div_temp中。
*/
`timescale 1ns / 1ps

`include "defines.vh"

module div(
	input wire					clk,
	input wire					rst,
	input wire                  signed_div_i,	//是否是有符号除法
	input wire[31:0]            opdata1_i,		//被除数
	input wire[31:0]		   	opdata2_i,		//除数
	input wire                  start_i,		//是否开始除法运算
	input wire                  annul_i,		//是否取消除法运算
	output reg[63:0]            result_o,		//除法运算结果
	output reg			        ready_o			//是否结束
);

	wire[32:0] div_temp;		//存储dividend[63:32]与除数的差,做有符号减法,最高位为符号位
	reg[5:0] cnt;				//记录试商法进行轮数,达到32时结束
	reg[64:0] dividend;			//{被除数,商}
	reg[1:0] state;				//状态机的状态
	reg[31:0] divisor;	 		//除数原码用来运算
	reg[31:0] temp_op1;			//被除数原码
	reg[31:0] temp_op2;			//除数原码
	reg[31:0] reg_op1;
	reg[31:0] reg_op2;
	
	assign div_temp = {1'b0,dividend[63:32]} - {1'b0,divisor};

	always @ (posedge clk) begin
		if (rst) begin
			state <= `DivFree;
			ready_o <= `DivResultNotReady;
			result_o <= {`ZeroWord,`ZeroWord};
		end else begin
		  case (state)			//状态机
		  	/* --------------------除法模块空闲，可以执行除法-------------------- */
		  	`DivFree:	begin
				/* ---------------准备好除法运算，规范被除数、除数--------------- */
		  		if(start_i == `DivStart && annul_i == 1'b0) begin
		  			if(opdata2_i == `ZeroWord) begin    //除数为0
		  				state <= `DivByZero;
		  			end else begin
		  				state <= `DivOn;				//状态切换为除法运算进行中
		  				cnt <= 6'b000000;				//开始计数
		  				/* ----------被除数、除数补码还原原码---------- */
						if(signed_div_i == 1'b1 && opdata1_i[31] == 1'b1 ) begin	//被除数为负
		  					temp_op1 = ~opdata1_i + 1;	//补码还原原码
		  				end else begin
		  					temp_op1 = opdata1_i;		//正数原码=补码
		  				end
		  				if(signed_div_i == 1'b1 && opdata2_i[31] == 1'b1 ) begin	//除数为负
		  					temp_op2 = ~opdata2_i + 1;
		  				end else begin
		  					temp_op2 = opdata2_i;
		  				end
						/* ----------被除数、除数赋初值并执行第一次运算---------- */
		  				dividend <= {`ZeroWord,`ZeroWord};
              		dividend[32:1] <= temp_op1;
              		divisor <= temp_op2;
			  		reg_op1 <= opdata1_i;
			  		reg_op2 <= opdata2_i;
             		end
				/* ---------------还未准备好除法运算--------------- */
				end else begin
					ready_o <= `DivResultNotReady;
					result_o <= {`ZeroWord,`ZeroWord};
				end          	
		  	end
			/* --------------------上一步除数是0，此时取值并修改状态-------------------- */
		  	`DivByZero:	begin
				dividend <= {`ZeroWord,`ZeroWord};
				state <= `DivEnd;		 		
		  	end
			/* --------------------除法运算正在进行中-------------------- */
		  	`DivOn:	begin
				/* ---------------除法运算没被取消--------------- */
		  		if(annul_i == 1'b0) begin
					/* ----------除法运算还没完成---------- */
		  			if(cnt != 6'b100000) begin
						if(div_temp[32] == 1'b1) begin				//差值为负,不够除
							dividend <= {dividend[63:0] , 1'b0};	//被除数不变,左移补0
						end else begin								//差值为正,够除
							dividend <= {div_temp[31:0] , dividend[31:0] , 1'b1};	//被除数变为div_temp
						end
               			cnt <= cnt + 1;
					/* ----------除法运算完成---------- */
             		end else begin
						/* -----有符号除法且被除数与除数异号----- */
						if((signed_div_i == 1'b1) && ((reg_op1[31] ^ reg_op2[31]) == 1'b1)) begin
							dividend[31:0] <= (~dividend[31:0] + 1);
						end
						/* -----有符号除法且被除数与除数同号----- */
						if((signed_div_i == 1'b1) && ((reg_op1[31] ^ dividend[64]) == 1'b1)) begin              
							dividend[64:33] <= (~dividend[64:33] + 1);
						end
						state <= `DivEnd;
						cnt <= 6'b000000;
             		end
				/* ---------------取消除法运算--------------- */
		  		end else begin
		  			state <= `DivFree;
		  		end	
		  	end
			/* --------------------除法运算结束-------------------- */
		  	`DivEnd:	begin
				result_o <= {dividend[64:33], dividend[31:0]};  
				ready_o <= `DivResultReady;
				if(start_i == `DivStop) begin
					state <= `DivFree;
					ready_o <= `DivResultNotReady;
					result_o <= {`ZeroWord,`ZeroWord};       	
				end		  	
		  	end
		  endcase
		end
	end

endmodule