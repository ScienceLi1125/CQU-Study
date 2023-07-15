	.option nopic
	.data
	.globl	n_block0
	.type	n_block0, @object
	.size	n_block0, 4
	.align	4
n_block0:
	.word	0
	.text
	.globl	bubblesort
	.type	bubblesort, @function
bubblesort:
	addi	sp,sp,-156
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
	li	s11,0
	sw	s11, 56(sp)
	li	s11,0
	sw	s11, 60(sp)
	li	s11,0
	sw	s11, 56(sp)
_ir_goto_label7:
	li	s11,1
	sw	s11, 64(sp)
	la	s10, n_block0
	lw	s11, 0(s10)
	lw	s10, 64(sp)
	sub	s9,s11,s10
	sw	s9, 68(sp)
	lw	s9, 56(sp)
	lw	s10, 68(sp)
	slt	s11,s9,s10
	sw	s11, 72(sp)
	lw	s11, 72(sp)
	bnez	s11,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s11,0
	sw	s11, 60(sp)
_ir_goto_label6:
	la	s10, n_block0
	lw	s11, 0(s10)
	lw	s10, 56(sp)
	sub	s9,s11,s10
	sw	s9, 76(sp)
	li	s9,1
	sw	s9, 80(sp)
	lw	s9, 76(sp)
	lw	s10, 80(sp)
	sub	s11,s9,s10
	sw	s11, 84(sp)
	lw	s11, 60(sp)
	lw	s10, 84(sp)
	slt	s9,s11,s10
	sw	s9, 88(sp)
	lw	s9, 88(sp)
	bnez	s9,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	lw	s9, 52(sp)
	lw	s10, 60(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 92(sp)
	li	s11,1
	sw	s11, 96(sp)
	lw	s11, 60(sp)
	lw	s10, 96(sp)
	add	s9,s11,s10
	sw	s9, 100(sp)
	lw	s9, 52(sp)
	lw	s10, 100(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 104(sp)
	lw	s11, 92(sp)
	lw	s10, 104(sp)
	slt	s9,s10,s11
	sw	s9, 108(sp)
	lw	s9, 108(sp)
	bnez	s9,_ir_goto_label4
	j	_ir_goto_label5
_ir_goto_label4:
	li	s9,0
	sw	s9, 112(sp)
	li	s9,1
	sw	s9, 116(sp)
	lw	s9, 60(sp)
	lw	s10, 116(sp)
	add	s11,s9,s10
	sw	s11, 120(sp)
	lw	s11, 52(sp)
	lw	s10, 120(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 124(sp)
	lw	s10, 124(sp)
	mv	s9,s10
	sw	s9, 112(sp)
	lw	s9, 52(sp)
	lw	s10, 60(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 128(sp)
	li	s11,1
	sw	s11, 132(sp)
	lw	s11, 60(sp)
	lw	s10, 132(sp)
	add	s9,s11,s10
	sw	s9, 136(sp)
	lw	s9, 52(sp)
	lw	s10, 136(sp)
	lw	s11, 128(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	lw	s10, 60(sp)
	lw	s9, 112(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
_ir_goto_label5:
	nop
	li	s9,1
	sw	s9, 140(sp)
	lw	s9, 60(sp)
	lw	s10, 140(sp)
	add	s11,s9,s10
	sw	s11, 144(sp)
	lw	s10, 144(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	j	_ir_goto_label6
_ir_goto_label3:
	nop
	li	s11,1
	sw	s11, 148(sp)
	lw	s11, 56(sp)
	lw	s10, 148(sp)
	add	s9,s11,s10
	sw	s9, 152(sp)
	lw	s10, 152(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label7
_ir_goto_label1:
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
	addi	sp,sp,156
	ret
	.size	bubblesort, .-bubblesort
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
	li	s11,10
	la	s10, n_block0
	sw	s11, 0(s10)
	addi	s11,sp,-40
	sw	s11, 52(sp)
	lw	s11, 52(sp)
	li	s9,4
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,3
	li	s10,4
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,9
	li	s10,8
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,2
	li	s10,12
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,0
	li	s10,16
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,1
	li	s10,20
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,6
	li	s10,24
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,5
	li	s10,28
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,7
	li	s10,32
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,8
	li	s10,36
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,0
	sw	s11, 56(sp)
	lw	s11, 52(sp)
	mv	a0,s11
	addi	sp,sp,-40
	call	bubblesort
	addi	sp,sp,40
	sw	a0, 60(sp)
	lw	s10, 60(sp)
	mv	s11,s10
	sw	s11, 56(sp)
_ir_goto_label10:
	lw	s11, 56(sp)
	la	s9, n_block0
	lw	s10, 0(s9)
	slt	s9,s11,s10
	sw	s9, 68(sp)
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	s9,0
	sw	s9, 72(sp)
	lw	s9, 52(sp)
	lw	s10, 56(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 76(sp)
	lw	s10, 76(sp)
	mv	s11,s10
	sw	s11, 72(sp)
	lw	s11, 72(sp)
	mv	a0,s11
	addi	sp,sp,-40
	call	putint
	addi	sp,sp,40
	li	s11,10
	sw	s11, 72(sp)
	lw	s11, 72(sp)
	mv	a0,s11
	addi	sp,sp,-40
	call	putch
	addi	sp,sp,40
	li	s11,1
	sw	s11, 80(sp)
	lw	s11, 56(sp)
	lw	s10, 80(sp)
	add	s9,s11,s10
	sw	s9, 84(sp)
	lw	s10, 84(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label10
_ir_goto_label9:
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
