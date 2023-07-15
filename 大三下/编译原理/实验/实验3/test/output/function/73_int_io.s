	.option nopic
	.data
	.globl	ascii_0_block0
	.type	ascii_0_block0, @object
	.size	ascii_0_block0, 4
	.align	4
ascii_0_block0:
	.word	48
	.text
	.globl	my_getint
	.type	my_getint, @function
my_getint:
	addi	sp,sp,-140
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
	li	s11,0
	sw	s11, 56(sp)
_ir_goto_label7:
	li	s11,1
	bnez	s11,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	addi	sp,sp,0
	call	getch
	addi	sp,sp,0
	sw	a0, 60(sp)
	li	s11,48
	sw	s11, 68(sp)
	lw	s11, 60(sp)
	lw	s10, 68(sp)
	sub	s9,s11,s10
	sw	s9, 72(sp)
	lw	s10, 72(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	li	s9,0
	sw	s9, 76(sp)
	lw	s9, 56(sp)
	lw	s10, 76(sp)
	slt	s11,s9,s10
	sw	s11, 80(sp)
	lw	s11, 80(sp)
	bnez	s11,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	li	s11,1
	sw	s11, 84(sp)
	j	_ir_goto_label4
_ir_goto_label3:
	li	s11,9
	sw	s11, 88(sp)
	lw	s11, 56(sp)
	lw	s10, 88(sp)
	slt	s9,s10,s11
	sw	s9, 92(sp)
	lw	s9, 80(sp)
	lw	s10, 92(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 84(sp)
_ir_goto_label4:
	lw	s11, 84(sp)
	bnez	s11,_ir_goto_label5
	j	_ir_goto_label6
_ir_goto_label5:
	j	_ir_goto_label7
	j	_ir_goto_label8
_ir_goto_label6:
	j	_ir_goto_label1
_ir_goto_label8:
	nop
	j	_ir_goto_label7
_ir_goto_label1:
	nop
	lw	s10, 56(sp)
	mv	s11,s10
	sw	s11, 52(sp)
_ir_goto_label17:
	li	s11,1
	bnez	s11,_ir_goto_label9
	j	_ir_goto_label10
_ir_goto_label9:
	addi	sp,sp,0
	call	getch
	addi	sp,sp,0
	sw	a0, 96(sp)
	li	s11,48
	sw	s11, 100(sp)
	lw	s11, 96(sp)
	lw	s10, 100(sp)
	sub	s9,s11,s10
	sw	s9, 104(sp)
	lw	s10, 104(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	li	s9,0
	sw	s9, 108(sp)
	lw	s9, 56(sp)
	lw	s10, 108(sp)
	slt	s11,s9,s10
	xori	s11,s11,1
	sw	s11, 112(sp)
	lw	s11, 112(sp)
	bnez	s11,_ir_goto_label11
	j	_ir_goto_label12
_ir_goto_label11:
	li	s11,9
	sw	s11, 116(sp)
	lw	s11, 56(sp)
	lw	s10, 116(sp)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 120(sp)
	lw	s9, 112(sp)
	lw	s10, 120(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 124(sp)
	j	_ir_goto_label13
_ir_goto_label12:
	li	s11,0
	sw	s11, 124(sp)
_ir_goto_label13:
	lw	s11, 124(sp)
	bnez	s11,_ir_goto_label14
	j	_ir_goto_label15
_ir_goto_label14:
	li	s11,10
	sw	s11, 128(sp)
	lw	s11, 52(sp)
	lw	s10, 128(sp)
	mul	s9,s11,s10
	sw	s9, 132(sp)
	lw	s9, 132(sp)
	lw	s10, 56(sp)
	add	s11,s9,s10
	sw	s11, 136(sp)
	lw	s10, 136(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	j	_ir_goto_label16
_ir_goto_label15:
	j	_ir_goto_label10
_ir_goto_label16:
	nop
	j	_ir_goto_label17
_ir_goto_label10:
	nop
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
	addi	sp,sp,140
	ret
	.size	my_getint, .-my_getint
	.globl	my_putint
	.type	my_putint, @function
my_putint:
	addi	sp,sp,-124
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
	addi	s11,sp,-64
	sw	s11, 56(sp)
	li	s11,0
	sw	s11, 60(sp)
_ir_goto_label20:
	li	s11,0
	sw	s11, 64(sp)
	lw	s11, 52(sp)
	lw	s10, 64(sp)
	slt	s9,s10,s11
	sw	s9, 68(sp)
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label18
	j	_ir_goto_label19
_ir_goto_label18:
	li	s9,10
	sw	s9, 72(sp)
	lw	s9, 52(sp)
	lw	s10, 72(sp)
	rem	s11,s9,s10
	sw	s11, 76(sp)
	li	s11,48
	sw	s11, 80(sp)
	lw	s11, 76(sp)
	lw	s10, 80(sp)
	add	s9,s11,s10
	sw	s9, 84(sp)
	lw	s9, 56(sp)
	lw	s10, 60(sp)
	lw	s11, 84(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,10
	sw	s11, 88(sp)
	lw	s11, 52(sp)
	lw	s10, 88(sp)
	div	s9,s11,s10
	sw	s9, 92(sp)
	lw	s10, 92(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	li	s9,1
	sw	s9, 96(sp)
	lw	s9, 60(sp)
	lw	s10, 96(sp)
	add	s11,s9,s10
	sw	s11, 100(sp)
	lw	s10, 100(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	j	_ir_goto_label20
_ir_goto_label19:
	nop
_ir_goto_label23:
	li	s11,0
	sw	s11, 104(sp)
	lw	s11, 60(sp)
	lw	s10, 104(sp)
	slt	s9,s10,s11
	sw	s9, 108(sp)
	lw	s9, 108(sp)
	bnez	s9,_ir_goto_label21
	j	_ir_goto_label22
_ir_goto_label21:
	li	s9,1
	sw	s9, 112(sp)
	lw	s9, 60(sp)
	lw	s10, 112(sp)
	sub	s11,s9,s10
	sw	s11, 116(sp)
	lw	s10, 116(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	lw	s11, 56(sp)
	lw	s10, 60(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 120(sp)
	lw	s9, 120(sp)
	mv	a0,s9
	addi	sp,sp,-64
	call	putch
	addi	sp,sp,64
	j	_ir_goto_label23
_ir_goto_label22:
	nop
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
	addi	sp,sp,124
	ret
	.size	my_putint, .-my_putint
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-88
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
	addi	sp,sp,0
	call	my_getint
	addi	sp,sp,0
	sw	a0, 52(sp)
	lw	s10, 52(sp)
	mv	s11,s10
	sw	s11, 60(sp)
_ir_goto_label26:
	li	s11,0
	sw	s11, 64(sp)
	lw	s11, 60(sp)
	lw	s10, 64(sp)
	slt	s9,s10,s11
	sw	s9, 68(sp)
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label24
	j	_ir_goto_label25
_ir_goto_label24:
	addi	sp,sp,0
	call	my_getint
	addi	sp,sp,0
	sw	a0, 72(sp)
	lw	s10, 72(sp)
	mv	s9,s10
	sw	s9, 76(sp)
	lw	s9, 76(sp)
	mv	a0,s9
	addi	sp,sp,0
	call	my_putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s9,1
	sw	s9, 80(sp)
	lw	s9, 60(sp)
	lw	s10, 80(sp)
	sub	s11,s9,s10
	sw	s11, 84(sp)
	lw	s10, 84(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	j	_ir_goto_label26
_ir_goto_label25:
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
	addi	sp,sp,88
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
	addi	sp,sp,88
	ret
	.size	main, .-main
