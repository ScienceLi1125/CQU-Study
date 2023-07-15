	.option nopic
	.data
	.text
	.globl	doubleWhile
	.type	doubleWhile, @function
doubleWhile:
	addi	sp,sp,-100
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
	li	s11,7
	sw	s11, 56(sp)
_ir_goto_label5:
	li	s11,100
	sw	s11, 60(sp)
	lw	s11, 52(sp)
	lw	s10, 60(sp)
	slt	s9,s11,s10
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,30
	sw	s9, 68(sp)
	lw	s9, 52(sp)
	lw	s10, 68(sp)
	add	s11,s9,s10
	sw	s11, 72(sp)
	lw	s10, 72(sp)
	mv	s11,s10
	sw	s11, 52(sp)
_ir_goto_label4:
	li	s11,100
	sw	s11, 76(sp)
	lw	s11, 56(sp)
	lw	s10, 76(sp)
	slt	s9,s11,s10
	sw	s9, 80(sp)
	lw	s9, 80(sp)
	bnez	s9,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	li	s9,6
	sw	s9, 84(sp)
	lw	s9, 56(sp)
	lw	s10, 84(sp)
	add	s11,s9,s10
	sw	s11, 88(sp)
	lw	s10, 88(sp)
	mv	s11,s10
	sw	s11, 56(sp)
	j	_ir_goto_label4
_ir_goto_label3:
	nop
	li	s11,100
	sw	s11, 92(sp)
	lw	s11, 56(sp)
	lw	s10, 92(sp)
	sub	s9,s11,s10
	sw	s9, 96(sp)
	lw	s10, 96(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label5
_ir_goto_label1:
	nop
	lw	s9, 56(sp)
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
	addi	sp,sp,100
	ret
	.size	doubleWhile, .-doubleWhile
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
	addi	sp,sp,0
	call	doubleWhile
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
