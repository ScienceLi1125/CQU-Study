	.option nopic
	.data
	.text
	.globl	main
	.type	main, @function
main:
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
	li	s11,0
	sw	s11, 56(sp)
	li	s11,56
	sw	s11, 52(sp)
	li	s11,4
	sw	s11, 56(sp)
	li	s11,-4
	sw	s11, 60(sp)
	lw	s11, 52(sp)
	lw	s10, 60(sp)
	sub	s9,s11,s10
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	lw	s10, 56(sp)
	add	s11,s9,s10
	sw	s11, 68(sp)
	lw	s10, 68(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	lw	s11, 52(sp)
	sltiu	s10,s11,1
	sw	s10, 72(sp)
	lw	s10, 72(sp)
	sltiu	s11,s10,1
	sw	s11, 76(sp)
	lw	s11, 76(sp)
	sltiu	s10,s11,1
	sw	s10, 80(sp)
	li	s10,0
	sw	s10, 84(sp)
	lw	s10, 84(sp)
	lw	s11, 80(sp)
	sub	s9,s10,s11
	sw	s9, 88(sp)
	lw	s9, 88(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,-1
	sw	s9, 52(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	li	s9,0
	sw	s9, 92(sp)
	lw	s9, 92(sp)
	lw	s11, 56(sp)
	add	s10,s9,s11
	sw	s10, 96(sp)
	lw	s11, 96(sp)
	mv	s10,s11
	sw	s10, 52(sp)
_ir_goto_label2:
	nop
	lw	s10, 52(sp)
	mv	a0,s10
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
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
	addi	sp,sp,100
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
	addi	sp,sp,100
	ret
	.size	main, .-main
