// 分频器
// @param cnt为16位reg变量，最大支持65536分频
// 24MHz需要分频为精确1s输出，则需要24M分频
// 需要使用24000 * 1000分频 换为paramter 可调
module divider(
   clk,
	speed,
	out
);
	input clk, speed;
	output reg out;
   reg    [7:0] cnt;
	parameter max_cnt = 240;
	always @(posedge clk) begin
		if (speed == 1) begin
			cnt <= cnt + 2;
		end
		else
			cnt <= cnt + 1;
		if (cnt >= max_cnt) begin
			cnt <= 0;
			out = 1;
		end
		else begin
			out = 0;
		end
	end
endmodule