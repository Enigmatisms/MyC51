; FIR的卷积过程
		AREA SXTH, CODE, READONLY
		ENTRY
		IMPORT c			;取数组1
		IMPORT f			;取数组2
		IMPORT x
		IMPORT y
eg6
		EXPORT eg6			;定义为eg6
		MOV r0, #0			; r0 为循环计数变量(步长1)
		MOV r1, #0			; r1 为循环地址指针(步长4)
		MOV r2, #0			; 初始化值
		LDR r3, =c			; 取得数组的地址
		LDR r4, =f
		LDR r8, =y
		LDR r7, [r8]		; r7储存循环次数
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
		STR r2, [r8]		; 结果输出
	