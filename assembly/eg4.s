; ����4 ��֧
		AREA FRTH, CODE, READONLY
		ENTRY
		IMPORT _a			;ȡc�����ж����_a
		IMPORT _b			;ͬ��
		IMPORT _c
		IMPORT _d
		IMPORT x
		IMPORT y
		IMPORT z
eg4
		EXPORT eg4			;����Ϊasmp
		LDR r5, =_a
		LDR r0, [r5]
		LDR r5, =_b
		LDR r1, [r5]
		CMP r0, r1			; �Ƚ�R0��R1��a, b��
		LDR r5, =x
		LDR r2, [r5]		; x�浽r2
		LDR r5, =_c
		LDR r3, [r5]		; _c�浽r3
		LDR r5, =_d	
		LDR r4, [r5]		; _d�浽r4
		BGT tblock			; a>bʱ
		SUB r2, r3, r4;		; x = c - d
		B after
tblock
		MOV r2, #5			; x = 5
		ADD r1, r3, r4		; y = c + d
		LDR r5, =y
		STR r1, [r5]		; ��r1�����y
after
		LDR r5, =x
		STR r2, [r5]		; ��r2�����x
		END
