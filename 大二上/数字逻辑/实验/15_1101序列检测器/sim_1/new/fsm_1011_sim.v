`define clk_period 20

module fsm_1011_sim();
reg clk,set,rst;
reg [7:0] data;
wire z;
wire now;

fsm_1011 uxxx(clk,set,data,rst,z,now);

always #(`clk_period/2) clk = ~clk;

initial begin
    clk = 0;
    set = 0;
    rst = 1;
    data = 8'b0000_0000;
    #(`clk_period*2)
    rst = 0;
    data = 8'b1011_1011;
    #(`clk_period)
    set = 1;
    #(`clk_period)
    set = 0;
    #(`clk_period*10)
    rst = 1;
    #(`clk_period*2) 
    rst = 0;
    #(`clk_period*2)
    data = 8'b0011_0110;
    set = 1;
    #(`clk_period*2)
    set = 0;
    #(`clk_period*10)
    $stop;
    end
endmodule