`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/12/08 23:57:11
// Design Name: 
// Module Name: vga_driver
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module vga_driver
(
    input                   I_clk   , // 系统50MHz时钟
    input                   I_rst_n , // 系统复位
    output   reg   [3:0]    O_red   , // VGA红色分量
    output   reg   [3:0]    O_green , // VGA绿色分量
    output   reg   [3:0]    O_blue  , // VGA蓝色分量
    output                  O_hs    , // VGA行同步信号
    output                  O_vs      // VGA场同步信号
);

// 分辨率为640*480时行时序各个参数定义
parameter       C_H_SYNC_PULSE      =   96      , 
                C_H_BACK_PORCH      =   48      ,
                C_H_ACTIVE_TIME     =   640     ,
                C_H_FRONT_PORCH     =   16      ,
                C_H_LINE_PERIOD     =   800     ;
                                                
// 分辨率为640*480时场时序各个参数定义                   
parameter       C_V_SYNC_PULSE      =   2       , 
                C_V_BACK_PORCH      =   33      ,
                C_V_ACTIVE_TIME     =   480     ,
                C_V_FRONT_PORCH     =   10      ,
                C_V_FRAME_PERIOD    =   525     ;
                                                
parameter       C_IMAGE_WIDTH       =   128     ,
                C_IMAGE_HEIGHT      =   128     ,
                C_IMAGE_PIX_NUM     =   16384   ;
                

reg     [11:0]      R_h_cnt         ; // 行时序计数器
reg     [11:0]      R_v_cnt         ; // 列时序计数器
reg                 R_clk_25M       ;
reg     [13:0]      R_rom_addr      ; // ROM的地址
wire    [11:0]      W_rom_data      ; // ROM中存储的数据

reg     [11:0]      R_h_pos         ; // 图片在屏幕上显示的水平位置，当它为0时，图片贴紧屏幕的左边沿
reg     [11:0]      R_v_pos         ; // 图片在屏幕上显示的垂直位置，当它为0时，图片贴紧屏幕的上边沿

reg                 R_vs_reg1       ;
reg                 R_vs_reg2       ;
wire                W_vs_neg        ; // 场脉冲下降沿标志
reg     [1:0]       R_state         ;

wire                W_active_flag   ; // 激活标志，当这个信号为1时RGB的数据可以显示在屏幕上

//功能： 产生25MHz的像素时钟
always @(posedge I_clk or negedge I_rst_n)
begin
    if(!I_rst_n)
        R_clk_25M   <=  1'b0        ;
    else
        R_clk_25M   <=  ~R_clk_25M  ;     
end

// 功能：产生行时序
always @(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n)
        R_h_cnt <=  12'd0   ;
    else if(R_h_cnt == C_H_LINE_PERIOD - 1'b1)
        R_h_cnt <=  12'd0   ;
    else
        R_h_cnt <=  R_h_cnt + 1'b1  ;                
end                

assign O_hs =   (R_h_cnt < C_H_SYNC_PULSE) ? 1'b0 : 1'b1    ; 

// 功能：产生场时序
always @(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n)
        R_v_cnt <=  12'd0   ;
    else if(R_v_cnt == C_V_FRAME_PERIOD - 1'b1)
        R_v_cnt <=  12'd0   ;
    else if(R_h_cnt == C_H_LINE_PERIOD - 1'b1)
        R_v_cnt <=  R_v_cnt + 1'b1  ;
    else
        R_v_cnt <=  R_v_cnt ;                        
end                

assign O_vs =   (R_v_cnt < C_V_SYNC_PULSE) ? 1'b0 : 1'b1    ; 
assign W_active_flag =  (R_h_cnt >= (C_H_SYNC_PULSE + C_H_BACK_PORCH                      ))  &&
                        (R_h_cnt <= (C_H_SYNC_PULSE + C_H_BACK_PORCH + C_H_ACTIVE_TIME     ))  && 
                        (R_v_cnt >= (C_V_SYNC_PULSE + C_V_BACK_PORCH                      ))  &&
                        (R_v_cnt <= (C_V_SYNC_PULSE + C_V_BACK_PORCH + C_V_ACTIVE_TIME     ))  ;   

// load the data from rom
always @(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n) 
        R_rom_addr  <=  14'd0 ;
    else if(W_active_flag)     
        begin
            if(R_h_cnt >= (C_H_SYNC_PULSE + C_H_BACK_PORCH + R_h_pos                        )  && 
               R_h_cnt <= (C_H_SYNC_PULSE + C_H_BACK_PORCH + R_h_pos + C_IMAGE_WIDTH  - 1'b1)  &&
               R_v_cnt >= (C_V_SYNC_PULSE + C_V_BACK_PORCH + R_v_pos                        )  && 
               R_v_cnt <= (C_V_SYNC_PULSE + C_V_BACK_PORCH + R_v_pos + C_IMAGE_HEIGHT - 1'b1)  )
                begin
                    O_red       <= W_rom_data[11:8]    ;
                    O_green     <= W_rom_data[7:4]     ;
                    O_blue      <= W_rom_data[3:0]      ;
                    if(R_rom_addr == C_IMAGE_PIX_NUM - 1'b1)
                        R_rom_addr  <=  14'd0 ;
                    else
                        R_rom_addr  <=  R_rom_addr  +  1'b1 ;         
                end
            else
                begin
                    O_red       <=  3'd0        ;
                    O_green     <=  3'd0        ;
                    O_blue      <=  3'd0        ;
                    R_rom_addr  <=  R_rom_addr  ;
                end                          
        end
    else
        begin
            O_red       <=  3'd0        ;
            O_green     <=  3'd0        ;
            O_blue      <=  3'd0        ;
            R_rom_addr  <=  R_rom_addr  ;
        end          
end

// move the img
always @(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n)
        begin
            R_vs_reg1   <=  1'b0        ;
            R_vs_reg2   <=  1'b0        ;
        end
    else
        begin
            R_vs_reg1   <=  O_vs        ;
            R_vs_reg2   <=  R_vs_reg1   ;
        end         
end

assign W_vs_neg = ~R_vs_reg1 & R_vs_reg2 ;

// bounce block
always@(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n)
        begin
            R_h_pos <=  12'd0   ;
            R_v_pos <=  12'd0   ; 
            R_state <=  2'b00   ;
        end
    else if(W_vs_neg)    
        begin 
            case(R_state)
                2'b00: // 图片往右下方移动
                    begin 
                        R_h_pos     <=  R_h_pos + 1 ;
                        R_v_pos     <=  R_v_pos + 1 ;
                        if(R_h_pos + C_IMAGE_WIDTH == C_H_ACTIVE_TIME) // 如果碰到右边框
                            R_state <=  2'b10       ;
                        else if((R_v_pos + C_IMAGE_HEIGHT) == C_V_ACTIVE_TIME) // 如果碰到下边框
                            R_state <=  2'b01       ;                            
                    end
                2'b01: // 图片往右上方移动
                    begin 
                        R_h_pos     <=  R_h_pos + 1 ;
                        R_v_pos     <=  R_v_pos - 1 ;
                        if(R_h_pos + C_IMAGE_WIDTH == C_H_ACTIVE_TIME) // 如果碰到右边框
                            R_state <=  2'b11       ;
                        else if(R_v_pos == 1)     // 如果碰到上边框
                            R_state <=  2'b00       ;
                    end
                2'b10: // 图片往左下方移动
                    begin 
                        R_h_pos     <=  R_h_pos - 1 ;
                        R_v_pos     <=  R_v_pos + 1 ;
                        if(R_h_pos == 1)    // 如果碰到左边框
                            R_state <=  2'b00       ;
                        else if(R_v_pos + C_IMAGE_HEIGHT == C_V_ACTIVE_TIME) // 如果碰到下边框
                            R_state <=  2'b11       ;
                    end
                2'b11: // 图片往左上方移动
                    begin 
                        R_h_pos     <=  R_h_pos - 1 ;
                        R_v_pos     <=  R_v_pos - 1 ;
                        if(R_h_pos == 1)    // 如果碰到上边框
                            R_state <=  2'b01       ;
                        else if(R_v_pos == 1) // 如果碰到左边框
                            R_state <=  2'b10       ;
                    end
                default:R_state <=  2'b00           ;            
            endcase       
        end
end      

rom_img_12 U_rom_image (
  .clka(R_clk_25M), // input clka
  .addra(R_rom_addr), // input [13 : 0] addra
  .douta(W_rom_data) // output [11 : 0] douta
);

endmodule