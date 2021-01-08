; 例程4 分支
		AREA FRTH, CODE, READONLY
		ENTRY
		IMPORT _a			;取c程序中定义的_a
		IMPORT _b			;同上
		IMPORT _c
		IMPORT _d
		IMPORT x
		IMPORT y
		IMPORT z
eg4
		EXPORT eg4			;定义为asmp
		LDR r5, =_a
		LDR r0, [r5]
		LDR r5, =_b
		LDR r1, [r5]
		CMP r0, r1			; 比较R0，R1（a, b）
		LDR r5, =x
		LDR r2, [r5]		; x存到r2
		LDR r5, =_c
		LDR r3, [r5]		; _c存到r3
		LDR r5, =_d	
		LDR r4, [r5]		; _d存到r4
		BGT tblock			; a>b时
		SUB r2, r3, r4;		; x = c - d
		B after
tblock
		MOV r2, #5			; x = 5
		ADD r1, r3, r4		; y = c + d
		LDR r5, =y
		STR r1, [r5]		; 存r1结果到y
after
		LDR r5, =x
		STR r2, [r5]		; 存r2结果到x
		END
