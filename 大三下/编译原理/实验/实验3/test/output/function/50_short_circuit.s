	.option nopic
	.data
	.globl	g_block0
	.type	g_block0, @object
	.size	g_block0, 4
	.align	4
g_block0:
	.word	0
	.text
	.globl	func
	.type	func, @function
func:
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
	sw	a0, 52(sp)
	la	s10, g_block0
	lw	s11, 0(s10)
	lw	s10, 52(sp)
	add	s9,s11,s10
	sw	s9, 56(sp)
	lw	s10, 56(sp)
	mv	s9,s10
	la	s10, g_block0
	sw	s9, 0(s10)
	la	s10, g_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	la	s10, g_block0
	lw	s9, 0(s10)
	mv	a0,s9
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
	.size	func, .-func
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-160
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
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 56(sp)
	lw	s10, 56(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	li	s11,10
	sw	s11, 64(sp)
	lw	s11, 52(sp)
	lw	s10, 64(sp)
	slt	s9,s10,s11
	sw	s9, 68(sp)
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	lw	s9, 52(sp)
	mv	a0,s9
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 72(sp)
	lw	s9, 68(sp)
	lw	s10, 72(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 80(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	li	s11,0
	sw	s11, 80(sp)
_ir_goto_label2:
	lw	s11, 80(sp)
	bnez	s11,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
	li	s11,1
	sw	s11, 52(sp)
	j	_ir_goto_label5
_ir_goto_label4:
	li	s11,0
	sw	s11, 52(sp)
_ir_goto_label5:
	nop
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 84(sp)
	lw	s10, 84(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	li	s11,11
	sw	s11, 88(sp)
	lw	s11, 52(sp)
	lw	s10, 88(sp)
	slt	s9,s10,s11
	sw	s9, 92(sp)
	lw	s9, 92(sp)
	bnez	s9,_ir_goto_label6
	j	_ir_goto_label7
_ir_goto_label6:
	lw	s9, 52(sp)
	mv	a0,s9
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 96(sp)
	lw	s9, 92(sp)
	lw	s10, 96(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 100(sp)
	j	_ir_goto_label8
_ir_goto_label7:
	li	s11,0
	sw	s11, 100(sp)
_ir_goto_label8:
	lw	s11, 100(sp)
	bnez	s11,_ir_goto_label9
	j	_ir_goto_label10
_ir_goto_label9:
	li	s11,1
	sw	s11, 52(sp)
	j	_ir_goto_label11
_ir_goto_label10:
	li	s11,0
	sw	s11, 52(sp)
_ir_goto_label11:
	nop
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 104(sp)
	lw	s10, 104(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	li	s11,99
	sw	s11, 108(sp)
	lw	s11, 52(sp)
	lw	s10, 108(sp)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 112(sp)
	lw	s9, 112(sp)
	bnez	s9,_ir_goto_label12
	j	_ir_goto_label13
_ir_goto_label12:
	li	s9,1
	sw	s9, 116(sp)
	j	_ir_goto_label14
_ir_goto_label13:
	lw	s9, 52(sp)
	mv	a0,s9
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 120(sp)
	lw	s9, 112(sp)
	lw	s10, 120(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 116(sp)
_ir_goto_label14:
	lw	s11, 116(sp)
	bnez	s11,_ir_goto_label15
	j	_ir_goto_label16
_ir_goto_label15:
	li	s11,1
	sw	s11, 52(sp)
	j	_ir_goto_label17
_ir_goto_label16:
	li	s11,0
	sw	s11, 52(sp)
_ir_goto_label17:
	nop
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 124(sp)
	lw	s10, 124(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	li	s11,100
	sw	s11, 128(sp)
	lw	s11, 52(sp)
	lw	s10, 128(sp)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 132(sp)
	lw	s9, 132(sp)
	bnez	s9,_ir_goto_label18
	j	_ir_goto_label19
_ir_goto_label18:
	li	s9,1
	sw	s9, 136(sp)
	j	_ir_goto_label20
_ir_goto_label19:
	lw	s9, 52(sp)
	mv	a0,s9
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 140(sp)
	lw	s9, 132(sp)
	lw	s10, 140(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 136(sp)
_ir_goto_label20:
	lw	s11, 136(sp)
	bnez	s11,_ir_goto_label21
	j	_ir_goto_label22
_ir_goto_label21:
	li	s11,1
	sw	s11, 52(sp)
	j	_ir_goto_label23
_ir_goto_label22:
	li	s11,0
	sw	s11, 52(sp)
_ir_goto_label23:
	nop
	li	a0,99
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 144(sp)
	lw	s11, 144(sp)
	sltiu	s10,s11,1
	sw	s10, 148(sp)
	lw	s10, 148(sp)
	bnez	s10,_ir_goto_label24
	j	_ir_goto_label25
_ir_goto_label24:
	li	a0,100
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 152(sp)
	lw	s10, 148(sp)
	lw	s11, 152(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 156(sp)
	j	_ir_goto_label26
_ir_goto_label25:
	li	s9,0
	sw	s9, 156(sp)
_ir_goto_label26:
	lw	s9, 156(sp)
	bnez	s9,_ir_goto_label27
	j	_ir_goto_label28
_ir_goto_label27:
	li	s9,1
	sw	s9, 52(sp)
	j	_ir_goto_label29
_ir_goto_label28:
	li	s9,0
	sw	s9, 52(sp)
_ir_goto_label29:
	nop
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
	addi	sp,sp,160
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
	addi	sp,sp,160
	ret
	.size	main, .-main
