; switch case的实现，为了方便起见，只有4个case
		AREA FFTH, CODE, READONLY
		ENTRY
		IMPORT _a			;取c程序中定义的_a
		IMPORT _b			;同上
		IMPORT _c
		IMPORT _d
		IMPORT x
eg5
		EXPORT eg5			;定义为eg5
		LDR r5, =x
		LDR r0, [r5]
		ADR r1, switch		; 取得switch块的地址
		LDR pc, [r1, r0, LSL #2];
switch	DCD case0
		DCD case1
		DCD case2
		DCD default
		
case0
		LDR r5, =_a
		B break

case1
		LDR r5, =_b
		B break
case2
		LDR r5, =_c
		B break

default
		LDR r5, =_d
break
		MOV r0, #1
		STR r0, [r5]			; STR不支持立即数
		