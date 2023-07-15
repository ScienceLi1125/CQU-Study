	.option nopic
	.data
	.text
	.globl	FourWhile
	.type	FourWhile, @function
FourWhile:
	addi	sp,sp,-168
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
_ir_goto_label11:
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
_ir_goto_label10:
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
_ir_goto_label9:
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
_ir_goto_label8:
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
	j	_ir_goto_label8
_ir_goto_label7:
	nop
	li	s11,1
	sw	s11, 132(sp)
	lw	s11, 64(sp)
	lw	s10, 132(sp)
	sub	s9,s11,s10
	sw	s9, 136(sp)
	lw	s10, 136(sp)
	mv	s9,s10
	sw	s9, 64(sp)
	j	_ir_goto_label9
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
	j	_ir_goto_label10
_ir_goto_label3:
	nop
	li	s11,2
	sw	s11, 148(sp)
	lw	s11, 56(sp)
	lw	s10, 148(sp)
	sub	s9,s11,s10
	sw	s9, 152(sp)
	lw	s10, 152(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label11
_ir_goto_label1:
	nop
	lw	s9, 56(sp)
	lw	s10, 64(sp)
	add	s11,s9,s10
	sw	s11, 156(sp)
	lw	s11, 52(sp)
	lw	s10, 156(sp)
	add	s9,s11,s10
	sw	s9, 160(sp)
	lw	s9, 160(sp)
	lw	s10, 60(sp)
	add	s11,s9,s10
	sw	s11, 164(sp)
	lw	s11, 164(sp)
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
	addi	sp,sp,168
	ret
	.size	FourWhile, .-FourWhile
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
	call	FourWhile
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
