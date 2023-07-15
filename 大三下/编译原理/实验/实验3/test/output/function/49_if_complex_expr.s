	.option nopic
	.data
	.text
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-208
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
	li	s11,0
	sw	s11, 60(sp)
	li	s11,0
	sw	s11, 64(sp)
	li	s11,0
	sw	s11, 68(sp)
	li	s11,5
	sw	s11, 52(sp)
	li	s11,5
	sw	s11, 56(sp)
	li	s11,1
	sw	s11, 60(sp)
	li	s11,-2
	sw	s11, 64(sp)
	li	s11,2
	sw	s11, 68(sp)
	li	s11,1
	sw	s11, 72(sp)
	lw	s11, 64(sp)
	lw	s10, 72(sp)
	mul	s9,s11,s10
	sw	s9, 76(sp)
	li	s9,2
	sw	s9, 80(sp)
	lw	s9, 76(sp)
	lw	s10, 80(sp)
	div	s11,s9,s10
	sw	s11, 84(sp)
	li	s11,0
	sw	s11, 88(sp)
	lw	s11, 84(sp)
	lw	s10, 88(sp)
	slt	s9,s11,s10
	sw	s9, 92(sp)
	lw	s9, 92(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,1
	sw	s9, 96(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	lw	s9, 52(sp)
	lw	s10, 56(sp)
	sub	s11,s9,s10
	sw	s11, 100(sp)
	li	s11,0
	sw	s11, 104(sp)
	lw	s11, 100(sp)
	lw	s10, 104(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 108(sp)
	lw	s9, 108(sp)
	bnez	s9,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
	li	s9,3
	sw	s9, 112(sp)
	lw	s9, 60(sp)
	lw	s10, 112(sp)
	add	s11,s9,s10
	sw	s11, 116(sp)
	li	s11,2
	sw	s11, 120(sp)
	lw	s11, 116(sp)
	lw	s10, 120(sp)
	rem	s9,s11,s10
	sw	s9, 124(sp)
	li	s9,0
	sw	s9, 128(sp)
	lw	s9, 124(sp)
	lw	s10, 128(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	xori	s11,s11,1
	sw	s11, 132(sp)
	lw	s11, 108(sp)
	lw	s10, 132(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 136(sp)
	j	_ir_goto_label5
_ir_goto_label4:
	li	s9,0
	sw	s9, 136(sp)
_ir_goto_label5:
	lw	s9, 92(sp)
	lw	s10, 136(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 96(sp)
_ir_goto_label2:
	lw	s11, 96(sp)
	bnez	s11,_ir_goto_label6
	j	_ir_goto_label7
_ir_goto_label6:
	lw	s11, 68(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
_ir_goto_label7:
	nop
	li	s11,2
	sw	s11, 140(sp)
	lw	s11, 64(sp)
	lw	s10, 140(sp)
	rem	s9,s11,s10
	sw	s9, 144(sp)
	li	s9,67
	sw	s9, 148(sp)
	lw	s9, 144(sp)
	lw	s10, 148(sp)
	add	s11,s9,s10
	sw	s11, 152(sp)
	li	s11,0
	sw	s11, 156(sp)
	lw	s11, 152(sp)
	lw	s10, 156(sp)
	slt	s9,s11,s10
	sw	s9, 160(sp)
	lw	s9, 160(sp)
	bnez	s9,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	s9,1
	sw	s9, 164(sp)
	j	_ir_goto_label10
_ir_goto_label9:
	lw	s9, 52(sp)
	lw	s10, 56(sp)
	sub	s11,s9,s10
	sw	s11, 168(sp)
	li	s11,0
	sw	s11, 172(sp)
	lw	s11, 168(sp)
	lw	s10, 172(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 176(sp)
	lw	s9, 176(sp)
	bnez	s9,_ir_goto_label11
	j	_ir_goto_label12
_ir_goto_label11:
	li	s9,2
	sw	s9, 180(sp)
	lw	s9, 60(sp)
	lw	s10, 180(sp)
	add	s11,s9,s10
	sw	s11, 184(sp)
	li	s11,2
	sw	s11, 188(sp)
	lw	s11, 184(sp)
	lw	s10, 188(sp)
	rem	s9,s11,s10
	sw	s9, 192(sp)
	li	s9,0
	sw	s9, 196(sp)
	lw	s9, 192(sp)
	lw	s10, 196(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	xori	s11,s11,1
	sw	s11, 200(sp)
	lw	s11, 176(sp)
	lw	s10, 200(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 204(sp)
	j	_ir_goto_label13
_ir_goto_label12:
	li	s9,0
	sw	s9, 204(sp)
_ir_goto_label13:
	lw	s9, 160(sp)
	lw	s10, 204(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 164(sp)
_ir_goto_label10:
	lw	s11, 164(sp)
	bnez	s11,_ir_goto_label14
	j	_ir_goto_label15
_ir_goto_label14:
	li	s11,4
	sw	s11, 68(sp)
	lw	s11, 68(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
_ir_goto_label15:
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
	addi	sp,sp,208
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
	addi	sp,sp,208
	ret
	.size	main, .-main
