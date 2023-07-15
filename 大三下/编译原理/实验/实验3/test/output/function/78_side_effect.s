	.option nopic
	.data
	.globl	a_block0
	.type	a_block0, @object
	.size	a_block0, 4
	.align	4
a_block0:
	.word	-1.000000
	.globl	b_block0
	.type	b_block0, @object
	.size	b_block0, 4
	.align	4
b_block0:
	.word	1
	.text
	.globl	inc_a
	.type	inc_a, @function
inc_a:
	addi	sp,sp,-64
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
	la	s9, a_block0
	lw	s10, 0(s9)
	mv	s11,s10
	sw	s11, 52(sp)
	li	s11,1
	sw	s11, 56(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	add	s9,s11,s10
	sw	s9, 60(sp)
	lw	s10, 60(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	lw	s10, 52(sp)
	mv	s9,s10
	la	s10, a_block0
	sw	s9, 0(s10)
	la	s10, a_block0
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
	addi	sp,sp,64
	ret
	.size	inc_a, .-inc_a
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-152
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
	li	s11,5
	sw	s11, 52(sp)
_ir_goto_label19:
	li	s11,0
	sw	s11, 56(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	slt	s9,s11,s10
	xori	s9,s9,1
	sw	s9, 60(sp)
	lw	s9, 60(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 64(sp)
	lw	s9, 64(sp)
	bnez	s9,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 72(sp)
	lw	s9, 72(sp)
	bnez	s9,_ir_goto_label4
	j	_ir_goto_label5
_ir_goto_label4:
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 76(sp)
	lw	s9, 72(sp)
	lw	s10, 76(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 80(sp)
	j	_ir_goto_label6
_ir_goto_label5:
	li	s11,0
	sw	s11, 80(sp)
_ir_goto_label6:
	lw	s11, 64(sp)
	lw	s10, 80(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 84(sp)
	j	_ir_goto_label7
_ir_goto_label3:
	li	s9,0
	sw	s9, 84(sp)
_ir_goto_label7:
	lw	s9, 84(sp)
	bnez	s9,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	la	s10, a_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	la	s10, b_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label9:
	nop
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 88(sp)
	li	s9,14
	sw	s9, 92(sp)
	lw	s9, 88(sp)
	lw	s10, 92(sp)
	slt	s11,s9,s10
	sw	s11, 96(sp)
	lw	s11, 96(sp)
	bnez	s11,_ir_goto_label10
	j	_ir_goto_label11
_ir_goto_label10:
	li	s11,1
	sw	s11, 100(sp)
	j	_ir_goto_label12
_ir_goto_label11:
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 104(sp)
	lw	s11, 104(sp)
	bnez	s11,_ir_goto_label13
	j	_ir_goto_label14
_ir_goto_label13:
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 108(sp)
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 112(sp)
	lw	s11, 108(sp)
	lw	s10, 112(sp)
	sub	s9,s11,s10
	sw	s9, 116(sp)
	li	s9,1
	sw	s9, 120(sp)
	lw	s9, 116(sp)
	lw	s10, 120(sp)
	add	s11,s9,s10
	sw	s11, 124(sp)
	lw	s11, 104(sp)
	lw	s10, 124(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 128(sp)
	j	_ir_goto_label15
_ir_goto_label14:
	li	s9,0
	sw	s9, 128(sp)
_ir_goto_label15:
	lw	s9, 96(sp)
	lw	s10, 128(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 100(sp)
_ir_goto_label12:
	lw	s11, 100(sp)
	bnez	s11,_ir_goto_label16
	j	_ir_goto_label17
_ir_goto_label16:
	la	s10, a_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s11,2
	sw	s11, 132(sp)
	la	s10, b_block0
	lw	s11, 0(s10)
	lw	s10, 132(sp)
	mul	s9,s11,s10
	sw	s9, 136(sp)
	lw	s10, 136(sp)
	mv	s9,s10
	la	s10, b_block0
	sw	s9, 0(s10)
	j	_ir_goto_label18
_ir_goto_label17:
	addi	sp,sp,0
	call	inc_a
	addi	sp,sp,0
	sw	a0, 140(sp)
_ir_goto_label18:
	nop
	li	s9,1
	sw	s9, 144(sp)
	lw	s9, 52(sp)
	lw	s10, 144(sp)
	sub	s11,s9,s10
	sw	s11, 148(sp)
	lw	s10, 148(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	j	_ir_goto_label19
_ir_goto_label1:
	nop
	la	s10, a_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	la	s10, b_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	la	s10, a_block0
	lw	s11, 0(s10)
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
	addi	sp,sp,152
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
	addi	sp,sp,152
	ret
	.size	main, .-main
