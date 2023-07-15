	.option nopic
	.data
	.text
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-132
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
	li	s11,2
	sw	s11, 52(sp)
	li	s11,20
	sw	s11, 56(sp)
	addi	s11,sp,-80
	sw	s11, 60(sp)
	lw	s11, 60(sp)
	li	s9,1
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,2
	li	s10,4
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,8
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,12
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,16
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,20
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,24
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,28
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,32
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,36
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,40
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,44
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,48
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,52
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,56
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,60
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,64
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,68
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 60(sp)
	li	s9,0
	li	s10,72
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	li	s11,0
	li	s10,76
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,0
	sw	s11, 64(sp)
_ir_goto_label2:
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
	lw	s9, 60(sp)
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 76(sp)
	li	s11,1
	sw	s11, 80(sp)
	lw	s11, 52(sp)
	lw	s10, 80(sp)
	sub	s9,s11,s10
	sw	s9, 84(sp)
	lw	s9, 60(sp)
	lw	s10, 84(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 88(sp)
	li	s11,2
	sw	s11, 92(sp)
	lw	s11, 52(sp)
	lw	s10, 92(sp)
	sub	s9,s11,s10
	sw	s9, 96(sp)
	lw	s9, 60(sp)
	lw	s10, 96(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 100(sp)
	lw	s11, 76(sp)
	lw	s10, 88(sp)
	add	s9,s11,s10
	sw	s9, 104(sp)
	lw	s9, 104(sp)
	lw	s10, 100(sp)
	add	s11,s9,s10
	sw	s11, 108(sp)
	lw	s11, 60(sp)
	lw	s10, 52(sp)
	lw	s9, 108(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 60(sp)
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 112(sp)
	lw	s11, 64(sp)
	lw	s10, 112(sp)
	add	s9,s11,s10
	sw	s9, 116(sp)
	lw	s10, 116(sp)
	mv	s9,s10
	sw	s9, 64(sp)
	lw	s9, 60(sp)
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 120(sp)
	lw	s11, 120(sp)
	mv	a0,s11
	addi	sp,sp,-80
	call	putint
	addi	sp,sp,80
	li	a0,10
	addi	sp,sp,-80
	call	putch
	addi	sp,sp,80
	li	s11,1
	sw	s11, 124(sp)
	lw	s11, 52(sp)
	lw	s10, 124(sp)
	add	s9,s11,s10
	sw	s9, 128(sp)
	lw	s10, 128(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	nop
	lw	s9, 64(sp)
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
	addi	sp,sp,132
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
	addi	sp,sp,132
	ret
	.size	main, .-main
