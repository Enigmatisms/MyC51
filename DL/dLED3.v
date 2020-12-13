// LED3输出集成模块
// 根据输入的信号
// @param clk 24000 分频得到的1KHz信号，用于LED动态刷新
// @param bits 输入的8位信息，为当前需要输出的数字
// @param output outs 输出：4位数码管段选信号（0~9） + 3位数码管位选信号(3个LED)
// 实现的功能是：clk每来一个低脉冲，动态LED位选变一个，根据当前的buffer
// bits(输入)改变时，会改变送出的outs, bits由红绿灯主模块送来
// 红绿灯主模块会根据当前的计时送出当前计数值（8bits）
module dLED3(
	clk, x7, x6, x5, x4, x3, x2, x1, x0,
	p2, p1, p0, a, b, c, d, e, f, g
);
	input clk;
	input x7, x6, x5, x4, x3, x2, x1, x0;
	output reg a, b, c, d, e, f, g;
	output reg p2, p1, p0;
	reg [4:0] temp;
	reg [1:0] cnt = 0;
	
	always @(posedge clk) begin	// 每来一个1KHz的clk信号，位选变一次
		cnt = cnt + 1;
		if (cnt == 3) cnt = 0;
		case(cnt)
			0: begin
				{p2, p1, p0} = 3'b001;
				temp = {x7, x6, x5, x4, x3, x2, x1, x0} % 4'b1010;	// 取个位
			end
			1: begin
				{p2, p1, p0} = 3'b010;
				temp = {x7, x6, x5, x4, x3, x2, x1, x0} / 4'b1010;
			end
			2: begin
				{p2, p1, p0} = 3'b100;
				temp = 0;
			end
		endcase
		case(temp)
			4'b0000: {a, b, c, d, e, f, g} = 7'b1111110;
			4'b0001: {a, b, c, d, e, f, g} = 7'b0110000;
			4'b0010: {a, b, c, d, e, f, g} = 7'b1101101;
			4'b0011: {a, b, c, d, e, f, g} = 7'b1111001;
			4'b0100: {a, b, c, d, e, f, g} = 7'b0110011;
			4'b0101: {a, b, c, d, e, f, g} = 7'b1011011;
			4'b0110: {a, b, c, d, e, f, g} = 7'b1011111;
			4'b0111: {a, b, c, d, e, f, g} = 7'b1110000;
			4'b1000: {a, b, c, d, e, f, g} = 7'b1111111;
			4'b1001: {a, b, c, d, e, f, g} = 7'b1111011;
		endcase
	end
endmodule