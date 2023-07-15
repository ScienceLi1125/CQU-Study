	.option nopic
	.data
	.text
	.globl	exgcd
	.type	exgcd, @function
exgcd:
	addi	sp,sp,-120
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
	sw	a1, 56(sp)
	sw	a2, 60(sp)
	sw	a3, 64(sp)
	li	s11,0
	sw	s11, 68(sp)
	lw	s11, 56(sp)
	lw	s10, 68(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 72(sp)
	lw	s9, 72(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	lw	s9, 60(sp)
	li	s11,1
	li	s10,0
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 64(sp)
	li	s9,0
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
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
	addi	sp,sp,120
	ret
	j	_ir_goto_label2
_ir_goto_label1:
	lw	s9, 52(sp)
	lw	s10, 56(sp)
	rem	s11,s9,s10
	sw	s11, 76(sp)
	lw	s11, 56(sp)
	mv	a0,s11
	lw	s11, 76(sp)
	mv	a1,s11
	lw	s11, 60(sp)
	mv	a2,s11
	lw	s11, 64(sp)
	mv	a3,s11
	addi	sp,sp,0
	call	exgcd
	addi	sp,sp,0
	sw	a0, 80(sp)
	lw	s10, 80(sp)
	mv	s11,s10
	sw	s11, 88(sp)
	lw	s11, 60(sp)
	li	s10,0
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 92(sp)
	lw	s10, 92(sp)
	mv	s9,s10
	sw	s9, 96(sp)
	lw	s9, 64(sp)
	li	s10,0
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 100(sp)
	lw	s11, 60(sp)
	lw	s9, 100(sp)
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 64(sp)
	li	s10,0
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 104(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	div	s9,s11,s10
	sw	s9, 108(sp)
	lw	s9, 108(sp)
	lw	s10, 104(sp)
	mul	s11,s9,s10
	sw	s11, 112(sp)
	lw	s11, 96(sp)
	lw	s10, 112(sp)
	sub	s9,s11,s10
	sw	s9, 116(sp)
	lw	s9, 64(sp)
	lw	s11, 116(sp)
	li	s10,0
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 88(sp)
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
	addi	sp,sp,120
	ret
_ir_goto_label2:
	nop
	.size	exgcd, .-exgcd
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-96
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
	li	s11,7
	sw	s11, 52(sp)
	li	s11,15
	sw	s11, 56(sp)
	addi	s11,sp,-4
	sw	s11, 60(sp)
	lw	s11, 60(sp)
	li	s9,1
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	addi	s9,sp,-8
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	li	s11,1
	li	s10,0
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	mv	a0,s11
	lw	s11, 56(sp)
	mv	a1,s11
	lw	s11, 60(sp)
	mv	a2,s11
	lw	s11, 64(sp)
	mv	a3,s11
	addi	sp,sp,-8
	call	exgcd
	addi	sp,sp,8
	sw	a0, 68(sp)
	lw	s11, 60(sp)
	li	s10,0
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 76(sp)
	lw	s9, 76(sp)
	lw	s10, 56(sp)
	rem	s11,s9,s10
	sw	s11, 80(sp)
	lw	s11, 80(sp)
	lw	s10, 56(sp)
	add	s9,s11,s10
	sw	s9, 84(sp)
	lw	s9, 84(sp)
	lw	s10, 56(sp)
	rem	s11,s9,s10
	sw	s11, 88(sp)
	lw	s11, 60(sp)
	lw	s9, 88(sp)
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s10,0
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 92(sp)
	lw	s11, 92(sp)
	mv	a0,s11
	addi	sp,sp,-8
	call	putint
	addi	sp,sp,8
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
	addi	sp,sp,96
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
	addi	sp,sp,96
	ret
	.size	main, .-main
