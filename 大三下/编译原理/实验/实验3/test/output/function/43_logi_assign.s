	.option nopic
	.data
	.globl	a_block0
	.type	a_block0, @object
	.size	a_block0, 4
	.align	4
a_block0:
	.word	0
	.globl	b_block0
	.type	b_block0, @object
	.size	b_block0, 4
	.align	4
b_block0:
	.word	0
	.text
	.globl	main
	.type	main, @function
main:
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
	li	s11,4
	la	s10, a_block0
	sw	s11, 0(s10)
	li	s11,4
	la	s10, b_block0
	sw	s11, 0(s10)
	li	s11,0
	sw	s11, 52(sp)
	la	s10, a_block0
	lw	s11, 0(s10)
	la	s9, b_block0
	lw	s10, 0(s9)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 56(sp)
	lw	s9, 56(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,3
	sw	s9, 60(sp)
	la	s10, a_block0
	lw	s9, 0(s10)
	lw	s10, 60(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	xori	s11,s11,1
	sw	s11, 64(sp)
	lw	s11, 56(sp)
	lw	s10, 64(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 68(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	li	s9,0
	sw	s9, 68(sp)
_ir_goto_label2:
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
	li	s9,1
	sw	s9, 52(sp)
	j	_ir_goto_label5
_ir_goto_label4:
	li	s9,0
	sw	s9, 52(sp)
_ir_goto_label5:
	nop
	lw	s9, 52(sp)
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
	addi	sp,sp,72
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
	addi	sp,sp,72
	ret
	.size	main, .-main
