/// 2位LED位选模块输出
/// s1, s0 状态位
/// dec 减法时钟输入
/// clk 位选刷新的输入
/// p5-p0 如果当前为红灯，输出在p5, p4, 黄灯p3, p2, 绿灯p1, p0、
/// we, ns为指示状态，如果为01或11(南北不通)则000011（东西绿灯），10则为110000
/// s1, s0 为状态，0红灯，1黄灯，2绿灯，3全亮测试
module dLED2(
	we, ns, dec, clk, c1, c0,
	a, b, c, d, e, f, g,
	p5, p4, p3, p2, p1, p0,
	s1, s0
);
	input we, ns, dec, clk, c1, c0;
	output reg a, b, c, d, e, f, g, p5, p4, p3, p2, p1, p0, s1, s0;
	reg [6:0] cnt = 105;
	reg [1:0] state = 3;
	reg [7:0] buffer = 0;
	reg [3:0] temp = 0;
	reg outpos = 1;
	reg [1:0] old_state;					// 保存原有的状态，当状态发生变化就强制黄灯
	always @(posedge dec) begin
		if (buffer == 8'h01)				// skip 00 state
			buffer[3:0] = buffer[3:0] - 1;
		if ((we | ns) == 0) begin 		// 没有置位信息
			if (old_state ^ {we, ns}) begin
				old_state = {we, ns};
				{s1, s0} = 1;
				buffer = 8'h03;
				cnt = 3;
				state = 0;
			end
			if (buffer[3:0] > 0) begin
				buffer[3:0] = buffer[3:0] - 1;
			end
			else begin
				buffer[3:0] = 9;
				if (buffer[7:4] > 0) 	//BCD calculation
					buffer[7:4] = buffer[7:4] - 1;
				else begin					// 00 - 1, state needs to be updated.
					state = state - 1;
					case(state)
						3: begin					// set as red light 60s （105）
							cnt = 105;
							buffer = 8'h60;
							{s1, s0} = 0;
						end
						2: begin					// set as yellow light 3s (45)
							cnt = 45;
							buffer = 8'h03;
							{s1, s0} = 1;
						end
						1: begin					// set as green light 40s (42)
							cnt = 42;
							buffer = 8'h40;
							{s1, s0} = 2;
						end
						0: begin					// set as yello light 3s (2)
							cnt = 3;
							buffer = 8'h03;
							{s1, s0} = 1;
						end
					endcase
				end
			end
		end
		else begin							// when locked(direction we, ns is set. output is 88)
			if (old_state ^ {we, ns}) begin	// 历史状态不等于当前we/ns置位信息
				old_state = {we, ns};
				buffer = 8'h03;
				cnt = 3;
				{s1, s0} = 1;
				state = 0;
				// 输出88
			end
			else begin						// 有置位信息，但历史状态已经更新，黄灯秒数减
				if ((buffer[3:0] > 0) && (buffer[7:4] < 1)) begin
					buffer[3:0] = buffer[3:0] - 1;
					{s1, s0} = 1;			// yellow light
				end
				else begin
					buffer = 8'h11;
					if (we == 1)
						{s1, s0} = 0;		// 东西不可走，输出当前状态为红灯
					else
						{s1, s0} = 2;		// 南北不可走，输出当前状态为绿灯
				end
			end
		end
	end
	always @(negedge clk) begin		// 2LED position decision
		outpos =! outpos;					// 按位取反
		if ((c1 | c0) == 1) begin
			if ((c0 & c1) == 1) begin
				if (outpos == 1) {p5, p4, p3, p2, p1, p0} = 6'b011111;
				else {p5, p4, p3, p2, p1, p0} = 6'b101111;
			end
			else if (c0 == 1) begin
				if (outpos == 1) {p5, p4, p3, p2, p1, p0} = 6'b111101;
				else {p5, p4, p3, p2, p1, p0} = 6'b111110;
			end
			else begin
				if (outpos == 1) {p5, p4, p3, p2, p1, p0} = 6'b110111;
				else {p5, p4, p3, p2, p1, p0} = 6'b111011;
			end
		end
		else begin
			case({s1, s0})
				0: begin
					if (outpos == 1) {p5, p4, p3, p2, p1, p0} = 6'b111101;
					else {p5, p4, p3, p2, p1, p0} = 6'b111110;
				end
				1: begin 
					if (outpos == 1) {p5, p4, p3, p2, p1, p0} = 6'b110111;
					else {p5, p4, p3, p2, p1, p0} = 6'b111011;
				end
				default: begin
					if (outpos == 1) {p5, p4, p3, p2, p1, p0} = 6'b011111;
					else {p5, p4, p3, p2, p1, p0} = 6'b101111;
				end
			endcase
		end
		if (outpos == 1)				// change the output led
			temp = buffer[3:0];
		else temp = buffer[7:4];
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