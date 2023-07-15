	.option nopic
	.data
	.globl	a_block0
	.type	a_block0, @object
	.size	a_block0, 4
	.align	4
a_block0:
	.word	7
	.text
	.globl	func
	.type	func, @function
func:
	addi	sp,sp,-72
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
	lw	s11, 56(sp)
	lw	s10, 52(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 60(sp)
	lw	s9, 60(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,1
	sw	s9, 64(sp)
	lw	s9, 56(sp)
	lw	s10, 64(sp)
	add	s11,s9,s10
	sw	s11, 68(sp)
	lw	s10, 68(sp)
	mv	s11,s10
	sw	s11, 56(sp)
	li	a0,1
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
	addi	sp,sp,72
	ret
	j	_ir_goto_label2
_ir_goto_label1:
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
	addi	sp,sp,72
	ret
_ir_goto_label2:
	nop
	.size	func, .-func
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-108
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
	li	s11,100
	sw	s11, 60(sp)
	lw	s11, 56(sp)
	lw	s10, 60(sp)
	slt	s9,s11,s10
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	bnez	s9,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 68(sp)
	li	s9,1
	sw	s9, 76(sp)
	lw	s9, 68(sp)
	lw	s10, 76(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 80(sp)
	lw	s11, 80(sp)
	bnez	s11,_ir_goto_label5
	j	_ir_goto_label6
_ir_goto_label5:
	li	s11,1
	sw	s11, 84(sp)
	lw	s11, 52(sp)
	lw	s10, 84(sp)
	add	s9,s11,s10
	sw	s9, 88(sp)
	lw	s10, 88(sp)
	mv	s9,s10
	sw	s9, 52(sp)
_ir_goto_label6:
	nop
	li	s9,1
	sw	s9, 92(sp)
	lw	s9, 56(sp)
	lw	s10, 92(sp)
	add	s11,s9,s10
	sw	s11, 96(sp)
	lw	s10, 96(sp)
	mv	s11,s10
	sw	s11, 56(sp)
	j	_ir_goto_label7
_ir_goto_label4:
	nop
	li	s11,100
	sw	s11, 100(sp)
	lw	s11, 52(sp)
	lw	s10, 100(sp)
	slt	s9,s11,s10
	sw	s9, 104(sp)
	lw	s9, 104(sp)
	bnez	s9,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	a0,1
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	j	_ir_goto_label10
_ir_goto_label9:
	li	a0,0
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
_ir_goto_label10:
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
	addi	sp,sp,108
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
	addi	sp,sp,108
	ret
	.size	main, .-main
