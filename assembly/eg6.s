; FIR�ľ������
		AREA SXTH, CODE, READONLY
		ENTRY
		IMPORT c			;ȡ����1
		IMPORT f			;ȡ����2
		IMPORT x
		IMPORT y
eg6
		EXPORT eg6			;����Ϊeg6
		MOV r0, #0			; r0 Ϊѭ����������(����1)
		MOV r1, #0			; r1 Ϊѭ����ַָ��(����4)
		MOV r2, #0			; ��ʼ��ֵ
		LDR r3, =c			; ȡ������ĵ�ַ
		LDR r4, =f
		LDR r8, =y
		LDR r7, [r8]		; r7����ѭ������
body	
		LDR r5, [r3, r1]
		LDR r6, [r4, r1]
		MUL r5, r5, r6
		ADD r2, r2, r5
		ADD r0, r0, #1
		ADD r1, r1, #4
		CMP r0, r7
		BLT body
		
		LDR r8, =x
		STR r2, [r8]		; ������
	