// 红绿灯主模块，绿灯40s，红灯60s，黄灯3s
// 个人认为，需要LED的前3位输出当前状态，使用真正的LED进行输出
// @param we 东西是否存在车辆
// @param ns 南北是否存在车辆
// @param sec 输入的时钟信号
// @param bits 输出给LED秒数显示模块使用的信号（8位）
// @param lights 输出5位，LED灯控制
// 实现的功能，模93的计数器（可以完全使用verilog写吗？），开始时为30s绿灯，此后3s黄灯，此后60s红灯
// 循环，使用if条件进行判定
module traffic(
	sec, we, ns
	bits, lights
);
	input sec, we, ns;
	output reg [7:0] bits;
	output reg [4:0] lights;
	reg [7:0] cnt = 105;
	// 添加we, ns old_state以保存之前的状态，如果发生改变，根据改变后的值，重新3s
	always @(posedge sec) begin
		cnt = cnt - 1;
		if (cnt > 105) cnt = 105
		case({we, ns})
			2'b00: begin
				if (cnt > 45) begin		// 红灯输出
					bits = cnt - 45;
					// 红灯输出控制（注意方向）
				end
				else if (cnt > 42) begin	// 全部黄灯
					bits = cnt - 42;
					// 黄灯输出控制
				end
				else if (cnt > 2) begin		// 输出绿灯
					bits = cnt - 2;
					// 绿灯输出控制
				end
				else begin					// 输出黄灯
					bits = cnt + 1;
					// 黄灯输出控制
				end
			end
			2'b01: begin
				;
			end
			2'b10: begin
				;
			end
			default: begin
				;
			end
		endcase
	end
endmodule