		AREA SEC, CODE, READONLY
		ENTRY
		IMPORT _a			;取c程序中定义的_a
		IMPORT _b			;同上
		IMPORT _c
		IMPORT _d
eg2
		EXPORT eg2			;定义为asmp
		LDR r3, =_b
		LDR r0, [r3]
		LDR r3, =_c
		LDR r1, [r3]
		ADD r2, r1, r0		; b + c
		LDR r3, =_a
		LDR r1, [r3]
		MUL r2, r2, r1		;a*(b+c)
		LDR r3, =_d
		STR r2, [r3]		; 存到_d中,结果应该是 1 * (2 + 3) = 5
		END
