`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/20 09:16:31
// Design Name: 
// Module Name: stallable_pipeline
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
//有阻塞3级流水线

module stallable_pipeline #(parameter WIDTH = 100)(
    input clk ,
    input rst ,
    input validin ,
    input [WIDTH-1:0] datain ,
    input out_allow,
    output validout,
    output [WIDTH-1:0] dataout
);
    reg pipe1_valid ;               //第X级上存有有效数据，清空流水线时将pipeX_valid置0即可
    reg [WIDTH -1:0] pipe1_data ;
    reg pipe2_valid ;
    reg [WIDTH -1:0] pipe2_data ;
    reg pipe3_valid ;
    reg [WIDTH -1:0] pipe3_data ;
    
    wire pipe1_allowin ;            //第1级可以接收前一级流水送来数据
    wire pipe1_ready_go ;           //第1级可以向后一级流水送去数据
    wire pipe1_to_pipe2_valid ;     //第1级可以送去数据，第2级可以接受数据
    wire pipe2_allowin ;
    wire pipe2_ready_go ;
    wire pipe2_to_pipe3_valid ;        
    wire pipe3_allowin ;
    wire pipe3_ready_go ;
        
// pipeline stage1
    assign pipe1_ready_go =1;
    assign pipe1_allowin = !pipe1_valid || pipe1_ready_go&&pipe2_allowin;   //可接收数据的条件：当前流水线无数据或可以向后一级传送
    assign pipe1_to_pipe2_valid = pipe1_valid && pipe1_ready_go ;           //可传送数据的条件：当前流水线有数据且可传送数据
    always @( posedge clk ) begin
        if ( rst ) begin
            pipe1_valid <= 1'b0 ;
        end
        else if ( pipe1_allowin ) begin
            pipe1_valid <= validin ;
        end
        if ( validin && pipe1_allowin ) begin
            pipe1_data <= datain ;
        end
    end

// pipeline stage2
    assign pipe2_ready_go =1;
    assign pipe2_allowin = ! pipe2_valid || pipe2_ready_go && pipe3_allowin ;
    assign pipe2_to_pipe3_valid = pipe2_valid && pipe2_ready_go ;

    always @( posedge clk ) begin
        if ( rst ) begin
            pipe2_valid <= 1'b0 ;
        end
        else if ( pipe2_allowin ) begin
            pipe2_valid <= pipe1_to_pipe2_valid ;
        end
        if ( pipe1_to_pipe2_valid && pipe2_allowin ) begin
            pipe2_data <= pipe1_data ;
        end
    end

// pipeline stage3
    assign pipe3_ready_go =1;
    assign pipe3_allowin = ! pipe3_valid || pipe3_ready_go && out_allow ;
    always @( posedge clk ) begin
        if ( rst ) begin
            pipe3_valid <= 1'b0 ;
        end
        else if ( pipe3_allowin ) begin
            pipe3_valid <= pipe2_to_pipe3_valid ;
        end
        if ( pipe2_to_pipe3_valid && pipe3_allowin ) begin
            pipe3_data <= pipe2_data ;
        end
    end

assign validout = pipe3_valid && pipe3_ready_go ;
assign dataout = pipe3_data ;

endmodule
