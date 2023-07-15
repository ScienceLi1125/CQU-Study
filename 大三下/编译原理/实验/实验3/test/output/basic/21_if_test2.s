	.option nopic
	.data
	.text
	.globl	ifElseIf
	.type	ifElseIf, @function
ifElseIf:
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
	li	s11,0
	sw	s11, 52(sp)
	li	s11,5
	sw	s11, 52(sp)
	li	s11,0
	sw	s11, 56(sp)
	li	s11,10
	sw	s11, 56(sp)
	li	s11,6
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
	li	s9,1
	sw	s9, 68(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	li	s9,11
	sw	s9, 72(sp)
	lw	s9, 56(sp)
	lw	s10, 72(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 76(sp)
	lw	s11, 64(sp)
	lw	s10, 76(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 68(sp)
_ir_goto_label2:
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
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
	addi	sp,sp,136
	ret
	j	_ir_goto_label5
_ir_goto_label4:
	li	s9,10
	sw	s9, 80(sp)
	lw	s9, 56(sp)
	lw	s10, 80(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 84(sp)
	lw	s11, 84(sp)
	bnez	s11,_ir_goto_label6
	j	_ir_goto_label7
_ir_goto_label6:
	li	s11,1
	sw	s11, 88(sp)
	lw	s11, 52(sp)
	lw	s10, 88(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 92(sp)
	lw	s9, 84(sp)
	lw	s10, 92(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 96(sp)
	j	_ir_goto_label8
_ir_goto_label7:
	li	s11,0
	sw	s11, 96(sp)
_ir_goto_label8:
	lw	s11, 96(sp)
	bnez	s11,_ir_goto_label9
	j	_ir_goto_label10
_ir_goto_label9:
	li	s11,25
	sw	s11, 52(sp)
	j	_ir_goto_label11
_ir_goto_label10:
	li	s11,10
	sw	s11, 100(sp)
	lw	s11, 56(sp)
	lw	s10, 100(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 104(sp)
	lw	s9, 104(sp)
	bnez	s9,_ir_goto_label12
	j	_ir_goto_label13
_ir_goto_label12:
	li	s9,-5
	sw	s9, 108(sp)
	lw	s9, 52(sp)
	lw	s10, 108(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 112(sp)
	lw	s11, 104(sp)
	lw	s10, 112(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 116(sp)
	j	_ir_goto_label14
_ir_goto_label13:
	li	s9,0
	sw	s9, 116(sp)
_ir_goto_label14:
	lw	s9, 116(sp)
	bnez	s9,_ir_goto_label15
	j	_ir_goto_label16
_ir_goto_label15:
	li	s9,15
	sw	s9, 120(sp)
	lw	s9, 52(sp)
	lw	s10, 120(sp)
	add	s11,s9,s10
	sw	s11, 124(sp)
	lw	s10, 124(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	j	_ir_goto_label17
_ir_goto_label16:
	li	s11,0
	sw	s11, 128(sp)
	lw	s11, 128(sp)
	lw	s10, 52(sp)
	sub	s9,s11,s10
	sw	s9, 132(sp)
	lw	s10, 132(sp)
	mv	s9,s10
	sw	s9, 52(sp)
_ir_goto_label17:
	nop
_ir_goto_label11:
	nop
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
	addi	sp,sp,136
	ret
	.size	ifElseIf, .-ifElseIf
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
	call	ifElseIf
	addi	sp,sp,0
	sw	a0, 52(sp)
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
