	.option nopic
	.data
	.globl	g_block0
	.type	g_block0, @object
	.size	g_block0, 4
	.align	4
g_block0:
	.word	0
	.globl	h_block0
	.type	h_block0, @object
	.size	h_block0, 4
	.align	4
h_block0:
	.word	0
	.globl	f_block0
	.type	f_block0, @object
	.size	f_block0, 4
	.align	4
f_block0:
	.word	0
	.globl	e_block0
	.type	e_block0, @object
	.size	e_block0, 4
	.align	4
e_block0:
	.word	0
	.text
	.globl	EightWhile
	.type	EightWhile, @function
EightWhile:
	addi	sp,sp,-280
	sw	s0,0(sp)
	sw	s1,4(sp)
	sw	s2,8(sp)
	sw	s3,12(sp)
	sw	s4,16(sp)
	sw	s5,20(sp)
	sw	s6,24(sp)
	sw	s7,28(sp)
	sw	s8,32(sp)
	sw	s9,36(sp)
	sw	s10,40(sp)
	sw	s11,44(sp)
	sw	ra,48(sp)
	li	s11,0
	sw	s11, 52(sp)
	li	s11,5
	sw	s11, 52(sp)
	li	s11,0
	sw	s11, 56(sp)
	li	s11,0
	sw	s11, 60(sp)
	li	s11,6
	sw	s11, 56(sp)
	li	s11,7
	sw	s11, 60(sp)
	li	s11,0
	sw	s11, 64(sp)
	li	s11,10
	sw	s11, 64(sp)
_ir_goto_label23:
	li	s11,20
	sw	s11, 68(sp)
	lw	s11, 52(sp)
	lw	s10, 68(sp)
	slt	s9,s11,s10
	sw	s9, 72(sp)
	lw	s9, 72(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,3
	sw	s9, 76(sp)
	lw	s9, 52(sp)
	lw	s10, 76(sp)
	add	s11,s9,s10
	sw	s11, 80(sp)
	lw	s10, 80(sp)
	mv	s11,s10
	sw	s11, 52(sp)
_ir_goto_label22:
	li	s11,10
	sw	s11, 84(sp)
	lw	s11, 56(sp)
	lw	s10, 84(sp)
	slt	s9,s11,s10
	sw	s9, 88(sp)
	lw	s9, 88(sp)
	bnez	s9,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	li	s9,1
	sw	s9, 92(sp)
	lw	s9, 56(sp)
	lw	s10, 92(sp)
	add	s11,s9,s10
	sw	s11, 96(sp)
	lw	s10, 96(sp)
	mv	s11,s10
	sw	s11, 56(sp)
_ir_goto_label21:
	li	s11,7
	sw	s11, 100(sp)
	lw	s11, 60(sp)
	lw	s10, 100(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 104(sp)
	lw	s9, 104(sp)
	bnez	s9,_ir_goto_label4
	j	_ir_goto_label5
_ir_goto_label4:
	li	s9,1
	sw	s9, 108(sp)
	lw	s9, 60(sp)
	lw	s10, 108(sp)
	sub	s11,s9,s10
	sw	s11, 112(sp)
	lw	s10, 112(sp)
	mv	s11,s10
	sw	s11, 60(sp)
_ir_goto_label20:
	li	s11,20
	sw	s11, 116(sp)
	lw	s11, 64(sp)
	lw	s10, 116(sp)
	slt	s9,s11,s10
	sw	s9, 120(sp)
	lw	s9, 120(sp)
	bnez	s9,_ir_goto_label6
	j	_ir_goto_label7
_ir_goto_label6:
	li	s9,3
	sw	s9, 124(sp)
	lw	s9, 64(sp)
	lw	s10, 124(sp)
	add	s11,s9,s10
	sw	s11, 128(sp)
	lw	s10, 128(sp)
	mv	s11,s10
	sw	s11, 64(sp)
_ir_goto_label19:
	li	s11,1
	sw	s11, 132(sp)
	la	s10, e_block0
	lw	s11, 0(s10)
	lw	s10, 132(sp)
	slt	s9,s10,s11
	sw	s9, 136(sp)
	lw	s9, 136(sp)
	bnez	s9,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	s9,1
	sw	s9, 140(sp)
	la	s10, e_block0
	lw	s9, 0(s10)
	lw	s10, 140(sp)
	sub	s11,s9,s10
	sw	s11, 144(sp)
	lw	s10, 144(sp)
	mv	s11,s10
	la	s10, e_block0
	sw	s11, 0(s10)
_ir_goto_label18:
	li	s11,2
	sw	s11, 148(sp)
	la	s10, f_block0
	lw	s11, 0(s10)
	lw	s10, 148(sp)
	slt	s9,s10,s11
	sw	s9, 152(sp)
	lw	s9, 152(sp)
	bnez	s9,_ir_goto_label10
	j	_ir_goto_label11
_ir_goto_label10:
	li	s9,2
	sw	s9, 156(sp)
	la	s10, f_block0
	lw	s9, 0(s10)
	lw	s10, 156(sp)
	sub	s11,s9,s10
	sw	s11, 160(sp)
	lw	s10, 160(sp)
	mv	s11,s10
	la	s10, f_block0
	sw	s11, 0(s10)
_ir_goto_label17:
	li	s11,3
	sw	s11, 164(sp)
	la	s10, g_block0
	lw	s11, 0(s10)
	lw	s10, 164(sp)
	slt	s9,s11,s10
	sw	s9, 168(sp)
	lw	s9, 168(sp)
	bnez	s9,_ir_goto_label12
	j	_ir_goto_label13
_ir_goto_label12:
	li	s9,10
	sw	s9, 172(sp)
	la	s10, g_block0
	lw	s9, 0(s10)
	lw	s10, 172(sp)
	add	s11,s9,s10
	sw	s11, 176(sp)
	lw	s10, 176(sp)
	mv	s11,s10
	la	s10, g_block0
	sw	s11, 0(s10)
_ir_goto_label16:
	li	s11,10
	sw	s11, 180(sp)
	la	s10, h_block0
	lw	s11, 0(s10)
	lw	s10, 180(sp)
	slt	s9,s11,s10
	sw	s9, 184(sp)
	lw	s9, 184(sp)
	bnez	s9,_ir_goto_label14
	j	_ir_goto_label15
_ir_goto_label14:
	li	s9,8
	sw	s9, 188(sp)
	la	s10, h_block0
	lw	s9, 0(s10)
	lw	s10, 188(sp)
	add	s11,s9,s10
	sw	s11, 192(sp)
	lw	s10, 192(sp)
	mv	s11,s10
	la	s10, h_block0
	sw	s11, 0(s10)
	j	_ir_goto_label16
_ir_goto_label15:
	nop
	li	s11,1
	sw	s11, 196(sp)
	la	s10, h_block0
	lw	s11, 0(s10)
	lw	s10, 196(sp)
	sub	s9,s11,s10
	sw	s9, 200(sp)
	lw	s10, 200(sp)
	mv	s9,s10
	la	s10, h_block0
	sw	s9, 0(s10)
	j	_ir_goto_label17
_ir_goto_label13:
	nop
	li	s9,8
	sw	s9, 204(sp)
	la	s10, g_block0
	lw	s9, 0(s10)
	lw	s10, 204(sp)
	sub	s11,s9,s10
	sw	s11, 208(sp)
	lw	s10, 208(sp)
	mv	s11,s10
	la	s10, g_block0
	sw	s11, 0(s10)
	j	_ir_goto_label18
_ir_goto_label11:
	nop
	li	s11,1
	sw	s11, 212(sp)
	la	s10, f_block0
	lw	s11, 0(s10)
	lw	s10, 212(sp)
	add	s9,s11,s10
	sw	s9, 216(sp)
	lw	s10, 216(sp)
	mv	s9,s10
	la	s10, f_block0
	sw	s9, 0(s10)
	j	_ir_goto_label19
_ir_goto_label9:
	nop
	li	s9,1
	sw	s9, 220(sp)
	la	s10, e_block0
	lw	s9, 0(s10)
	lw	s10, 220(sp)
	add	s11,s9,s10
	sw	s11, 224(sp)
	lw	s10, 224(sp)
	mv	s11,s10
	la	s10, e_block0
	sw	s11, 0(s10)
	j	_ir_goto_label20
_ir_goto_label7:
	nop
	li	s11,1
	sw	s11, 228(sp)
	lw	s11, 64(sp)
	lw	s10, 228(sp)
	sub	s9,s11,s10
	sw	s9, 232(sp)
	lw	s10, 232(sp)
	mv	s9,s10
	sw	s9, 64(sp)
	j	_ir_goto_label21
_ir_goto_label5:
	nop
	li	s9,1
	sw	s9, 236(sp)
	lw	s9, 60(sp)
	lw	s10, 236(sp)
	add	s11,s9,s10
	sw	s11, 240(sp)
	lw	s10, 240(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	j	_ir_goto_label22
_ir_goto_label3:
	nop
	li	s11,2
	sw	s11, 244(sp)
	lw	s11, 56(sp)
	lw	s10, 244(sp)
	sub	s9,s11,s10
	sw	s9, 248(sp)
	lw	s10, 248(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label23
_ir_goto_label1:
	nop
	lw	s9, 56(sp)
	lw	s10, 64(sp)
	add	s11,s9,s10
	sw	s11, 252(sp)
	lw	s11, 52(sp)
	lw	s10, 252(sp)
	add	s9,s11,s10
	sw	s9, 256(sp)
	lw	s9, 256(sp)
	lw	s10, 60(sp)
	add	s11,s9,s10
	sw	s11, 260(sp)
	la	s10, e_block0
	lw	s11, 0(s10)
	lw	s10, 64(sp)
	add	s9,s11,s10
	sw	s9, 264(sp)
	lw	s9, 264(sp)
	la	s11, g_block0
	lw	s10, 0(s11)
	sub	s11,s9,s10
	sw	s11, 268(sp)
	lw	s11, 268(sp)
	la	s9, h_block0
	lw	s10, 0(s9)
	add	s9,s11,s10
	sw	s9, 272(sp)
	lw	s9, 260(sp)
	lw	s10, 272(sp)
	sub	s11,s9,s10
	sw	s11, 276(sp)
	lw	s11, 276(sp)
	mv	a0,s11
	lw	s0,0(sp)
	lw	s1,4(sp)
	lw	s2,8(sp)
	lw	s3,12(sp)
	lw	s4,16(sp)
	lw	s5,20(sp)
	lw	s6,24(sp)
	lw	s7,28(sp)
	lw	s8,32(sp)
	lw	s9,36(sp)
	lw	s10,40(sp)
	lw	s11,44(sp)
	lw	ra,48(sp)
	addi	sp,sp,280
	ret
	.size	EightWhile, .-EightWhile
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-60
	sw	s0,0(sp)
	sw	s1,4(sp)
	sw	s2,8(sp)
	sw	s3,12(sp)
	sw	s4,16(sp)
	sw	s5,20(sp)
	sw	s6,24(sp)
	sw	s7,28(sp)
	sw	s8,32(sp)
	sw	s9,36(sp)
	sw	s10,40(sp)
	sw	s11,44(sp)
	sw	ra,48(sp)
	li	s11,1
	la	s10, g_block0
	sw	s11, 0(s10)
	li	s11,2
	la	s10, h_block0
	sw	s11, 0(s10)
	li	s11,4
	la	s10, e_block0
	sw	s11, 0(s10)
	li	s11,6
	la	s10, f_block0
	sw	s11, 0(s10)
	addi	sp,sp,0
	call	EightWhile
	addi	sp,sp,0
	sw	a0, 52(sp)
	lw	s11, 52(sp)
	mv	a0,s11
	lw	s0,0(sp)
	lw	s1,4(sp)
	lw	s2,8(sp)
	lw	s3,12(sp)
	lw	s4,16(sp)
	lw	s5,20(sp)
	lw	s6,24(sp)
	lw	s7,28(sp)
	lw	s8,32(sp)
	lw	s9,36(sp)
	lw	s10,40(sp)
	lw	s11,44(sp)
	lw	ra,48(sp)
	addi	sp,sp,60
	ret
	li	a0,0
	lw	s0,0(sp)
	lw	s1,4(sp)
	lw	s2,8(sp)
	lw	s3,12(sp)
	lw	s4,16(sp)
	lw	s5,20(sp)
	lw	s6,24(sp)
	lw	s7,28(sp)
	lw	s8,32(sp)
	lw	s9,36(sp)
	lw	s10,40(sp)
	lw	s11,44(sp)
	lw	ra,48(sp)
	addi	sp,sp,60
	ret
	.size	main, .-main
