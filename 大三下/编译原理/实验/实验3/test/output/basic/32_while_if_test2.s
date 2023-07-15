	.option nopic
	.data
	.text
	.globl	ifWhile
	.type	ifWhile, @function
ifWhile:
	addi	sp,sp,-116
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
	sw	s11, 52(sp)
	li	s11,0
	sw	s11, 56(sp)
	li	s11,3
	sw	s11, 56(sp)
	li	s11,5
	sw	s11, 60(sp)
	lw	s11, 52(sp)
	lw	s10, 60(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,2
	sw	s9, 68(sp)
	lw	s9, 56(sp)
	lw	s10, 68(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 72(sp)
	lw	s11, 72(sp)
	bnez	s11,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	li	s11,2
	sw	s11, 76(sp)
	lw	s11, 56(sp)
	lw	s10, 76(sp)
	add	s9,s11,s10
	sw	s9, 80(sp)
	lw	s10, 80(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label0
_ir_goto_label3:
	nop
	li	s9,25
	sw	s9, 84(sp)
	lw	s9, 56(sp)
	lw	s10, 84(sp)
	add	s11,s9,s10
	sw	s11, 88(sp)
	lw	s10, 88(sp)
	mv	s11,s10
	sw	s11, 56(sp)
	j	_ir_goto_label4
_ir_goto_label1:
	li	s11,5
	sw	s11, 92(sp)
	lw	s11, 52(sp)
	lw	s10, 92(sp)
	slt	s9,s11,s10
	sw	s9, 96(sp)
	lw	s9, 96(sp)
	bnez	s9,_ir_goto_label5
	j	_ir_goto_label6
_ir_goto_label5:
	li	s9,2
	sw	s9, 100(sp)
	lw	s9, 56(sp)
	lw	s10, 100(sp)
	mul	s11,s9,s10
	sw	s11, 104(sp)
	lw	s10, 104(sp)
	mv	s11,s10
	sw	s11, 56(sp)
	li	s11,1
	sw	s11, 108(sp)
	lw	s11, 52(sp)
	lw	s10, 108(sp)
	add	s9,s11,s10
	sw	s9, 112(sp)
	lw	s10, 112(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	j	_ir_goto_label1
_ir_goto_label6:
	nop
_ir_goto_label4:
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
	addi	sp,sp,116
	ret
	.size	ifWhile, .-ifWhile
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
	call	ifWhile
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
