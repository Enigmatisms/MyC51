; ���Ӹ��ӵ����̣�Ϊ�˶Աȣ���c���еȼ�ʵ��
		AREA THRD, CODE, READONLY
		ENTRY
		IMPORT _a			;ȡc�����ж����_a
		IMPORT _b			;ͬ��
		IMPORT _d
		IMPORT z
eg3
		EXPORT eg3			;����Ϊasmp
		LDR r3, =_a
		LDR r0, [r3]
		LSL r0, #2			; ����2
		LDR r3, =_b
		LDR r1, [r3]
		AND r1, #15			; ��15
		ORR  r2, r0, r1		; ��
		LDR r3, =_d
		STR r2, [r3]		; �浽_d��,���Ӧ���� 1 * (2 + 3) = 5
		END
