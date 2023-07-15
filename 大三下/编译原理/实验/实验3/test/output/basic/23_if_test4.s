	.option nopic
	.data
	.text
	.globl	if_ifElse_
	.type	if_ifElse_, @function
if_ifElse_:
	addi	sp,sp,-84
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
	li	s11,10
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
	li	s9,10
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
	li	s11,25
	sw	s11, 52(sp)
	j	_ir_goto_label4
_ir_goto_label3:
	li	s11,15
	sw	s11, 76(sp)
	lw	s11, 52(sp)
	lw	s10, 76(sp)
	add	s9,s11,s10
	sw	s9, 80(sp)
	lw	s10, 80(sp)
	mv	s9,s10
	sw	s9, 52(sp)
_ir_goto_label4:
	nop
_ir_goto_label1:
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
	addi	sp,sp,84
	ret
	.size	if_ifElse_, .-if_ifElse_
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
	call	if_ifElse_
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
