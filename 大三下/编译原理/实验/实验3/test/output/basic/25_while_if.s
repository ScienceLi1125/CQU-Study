	.option nopic
	.data
	.text
	.globl	get_one
	.type	get_one, @function
get_one:
	addi	sp,sp,-56
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
	addi	sp,sp,56
	ret
	.size	get_one, .-get_one
	.globl	deepWhileBr
	.type	deepWhileBr, @function
deepWhileBr:
	addi	sp,sp,-136
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
	li	s11,0
	sw	s11, 60(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	add	s9,s11,s10
	sw	s9, 64(sp)
	lw	s10, 64(sp)
	mv	s9,s10
	sw	s9, 60(sp)
_ir_goto_label8:
	li	s9,75
	sw	s9, 68(sp)
	lw	s9, 60(sp)
	lw	s10, 68(sp)
	slt	s11,s9,s10
	sw	s11, 72(sp)
	lw	s11, 72(sp)
	bnez	s11,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s11,0
	sw	s11, 76(sp)
	li	s11,42
	sw	s11, 76(sp)
	li	s11,100
	sw	s11, 80(sp)
	lw	s11, 60(sp)
	lw	s10, 80(sp)
	slt	s9,s11,s10
	sw	s9, 84(sp)
	lw	s9, 84(sp)
	bnez	s9,_ir_goto_label2
	j	_ir_goto_label3
_ir_goto_label2:
	lw	s9, 60(sp)
	lw	s10, 76(sp)
	add	s11,s9,s10
	sw	s11, 88(sp)
	lw	s10, 88(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	li	s11,99
	sw	s11, 92(sp)
	lw	s11, 60(sp)
	lw	s10, 92(sp)
	slt	s9,s10,s11
	sw	s9, 96(sp)
	lw	s9, 96(sp)
	bnez	s9,_ir_goto_label4
	j	_ir_goto_label5
_ir_goto_label4:
	li	s9,0
	sw	s9, 100(sp)
	li	s9,2
	sw	s9, 104(sp)
	lw	s9, 76(sp)
	lw	s10, 104(sp)
	mul	s11,s9,s10
	sw	s11, 108(sp)
	lw	s10, 108(sp)
	mv	s11,s10
	sw	s11, 100(sp)
	li	a0,0
	addi	sp,sp,0
	call	get_one
	addi	sp,sp,0
	sw	a0, 112(sp)
	li	s11,1
	sw	s11, 120(sp)
	lw	s11, 112(sp)
	lw	s10, 120(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 124(sp)
	lw	s9, 124(sp)
	bnez	s9,_ir_goto_label6
	j	_ir_goto_label7
_ir_goto_label6:
	li	s9,2
	sw	s9, 128(sp)
	lw	s9, 100(sp)
	lw	s10, 128(sp)
	mul	s11,s9,s10
	sw	s11, 132(sp)
	lw	s10, 132(sp)
	mv	s11,s10
	sw	s11, 60(sp)
_ir_goto_label7:
	nop
_ir_goto_label5:
	nop
_ir_goto_label3:
	nop
	j	_ir_goto_label8
_ir_goto_label1:
	nop
	lw	s11, 60(sp)
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
	addi	sp,sp,136
	ret
	.size	deepWhileBr, .-deepWhileBr
	.globl	main
	.type	main, @function
main:
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
	li	s11,0
	sw	s11, 52(sp)
	li	s11,2
	sw	s11, 52(sp)
	lw	s11, 52(sp)
	mv	a0,s11
	lw	s11, 52(sp)
	mv	a1,s11
	addi	sp,sp,0
	call	deepWhileBr
	addi	sp,sp,0
	sw	a0, 56(sp)
	lw	s10, 56(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	lw	s11, 52(sp)
	mv	a0,s11
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
	addi	sp,sp,64
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
	addi	sp,sp,64
	ret
	.size	main, .-main
