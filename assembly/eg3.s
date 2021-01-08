; 更加复杂的例程，为了对比，在c中有等价实现
		AREA THRD, CODE, READONLY
		ENTRY
		IMPORT _a			;取c程序中定义的_a
		IMPORT _b			;同上
		IMPORT _d
		IMPORT z
eg3
		EXPORT eg3			;定义为asmp
		LDR r3, =_a
		LDR r0, [r3]
		LSL r0, #2			; 左移2
		LDR r3, =_b
		LDR r1, [r3]
		AND r1, #15			; 与15
		ORR  r2, r0, r1		; 或
		LDR r3, =_d
		STR r2, [r3]		; 存到_d中,结果应该是 1 * (2 + 3) = 5
		END
