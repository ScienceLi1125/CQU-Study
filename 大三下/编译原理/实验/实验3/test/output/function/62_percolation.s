	.option nopic
	.data
	.globl	n_block0
	.type	n_block0, @object
	.size	n_block0, 4
	.align	4
n_block0:
	.word	0
	.bss
	.globl	array_block0
	.type	array_block0, @object
	.size	array_block0, 440
	.align	4
array_block0:
	.space	440
	.text
	.globl	init
	.type	init, @function
init:
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
	sw	a0, 52(sp)
	li	s11,1
	sw	s11, 56(sp)
_ir_goto_label2:
	lw	s11, 52(sp)
	lw	s10, 52(sp)
	mul	s9,s11,s10
	sw	s9, 60(sp)
	li	s9,1
	sw	s9, 64(sp)
	lw	s9, 60(sp)
	lw	s10, 64(sp)
	add	s11,s9,s10
	sw	s11, 68(sp)
	lw	s11, 56(sp)
	lw	s10, 68(sp)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 72(sp)
	lw	s9, 72(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	la	s9, array_block0
	lw	s10, 56(sp)
	li	s11,-1.000000
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 76(sp)
	lw	s11, 56(sp)
	lw	s10, 76(sp)
	add	s9,s11,s10
	sw	s9, 80(sp)
	lw	s10, 80(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	nop
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
	.size	init, .-init
	.globl	findfa
	.type	findfa, @function
findfa:
	addi	sp,sp,-80
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
	la	s11, array_block0
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 56(sp)
	lw	s9, 56(sp)
	lw	s10, 52(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 60(sp)
	lw	s11, 60(sp)
	bnez	s11,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
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
	addi	sp,sp,80
	ret
	j	_ir_goto_label5
_ir_goto_label4:
	la	s11, array_block0
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	mv	a0,s9
	addi	sp,sp,0
	call	findfa
	addi	sp,sp,0
	sw	a0, 68(sp)
	la	s9, array_block0
	lw	s10, 52(sp)
	lw	s11, 68(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	la	s11, array_block0
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 76(sp)
	lw	s9, 76(sp)
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
	addi	sp,sp,80
	ret
_ir_goto_label5:
	nop
	.size	findfa, .-findfa
	.globl	mmerge
	.type	mmerge, @function
mmerge:
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
	sw	a0, 52(sp)
	sw	a1, 56(sp)
	lw	s11, 52(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	findfa
	addi	sp,sp,0
	sw	a0, 60(sp)
	lw	s10, 60(sp)
	mv	s11,s10
	sw	s11, 68(sp)
	lw	s11, 56(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	findfa
	addi	sp,sp,0
	sw	a0, 72(sp)
	lw	s10, 72(sp)
	mv	s11,s10
	sw	s11, 76(sp)
	lw	s11, 68(sp)
	lw	s10, 76(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 80(sp)
	lw	s9, 80(sp)
	bnez	s9,_ir_goto_label6
	j	_ir_goto_label7
_ir_goto_label6:
	la	s9, array_block0
	lw	s10, 68(sp)
	lw	s11, 76(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
_ir_goto_label7:
	nop
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
	.size	mmerge, .-mmerge
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-360
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
	li	s11,1
	sw	s11, 52(sp)
_ir_goto_label49:
	lw	s11, 52(sp)
	bnez	s11,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	s11,1
	sw	s11, 68(sp)
	lw	s11, 52(sp)
	lw	s10, 68(sp)
	sub	s9,s11,s10
	sw	s9, 72(sp)
	lw	s10, 72(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	li	s9,4
	la	s10, n_block0
	sw	s9, 0(s10)
	li	s9,10
	sw	s9, 56(sp)
	li	s9,0
	sw	s9, 76(sp)
	li	s9,0
	sw	s9, 80(sp)
	la	s10, n_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	init
	addi	sp,sp,0
	la	s10, n_block0
	lw	s9, 0(s10)
	la	s11, n_block0
	lw	s10, 0(s11)
	mul	s11,s9,s10
	sw	s11, 84(sp)
	li	s11,1
	sw	s11, 88(sp)
	lw	s11, 84(sp)
	lw	s10, 88(sp)
	add	s9,s11,s10
	sw	s9, 92(sp)
	lw	s10, 92(sp)
	mv	s9,s10
	sw	s9, 96(sp)
_ir_goto_label46:
	lw	s9, 76(sp)
	lw	s10, 56(sp)
	slt	s11,s9,s10
	sw	s11, 100(sp)
	lw	s11, 100(sp)
	bnez	s11,_ir_goto_label10
	j	_ir_goto_label11
_ir_goto_label10:
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 104(sp)
	lw	s10, 104(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 112(sp)
	lw	s10, 112(sp)
	mv	s11,s10
	sw	s11, 64(sp)
	lw	s11, 80(sp)
	sltiu	s10,s11,1
	sw	s10, 116(sp)
	lw	s10, 116(sp)
	bnez	s10,_ir_goto_label12
	j	_ir_goto_label13
_ir_goto_label12:
	li	s10,1
	sw	s10, 120(sp)
	lw	s10, 60(sp)
	lw	s11, 120(sp)
	sub	s9,s10,s11
	sw	s9, 124(sp)
	la	s11, n_block0
	lw	s9, 0(s11)
	lw	s11, 124(sp)
	mul	s10,s9,s11
	sw	s10, 128(sp)
	lw	s10, 128(sp)
	lw	s11, 64(sp)
	add	s9,s10,s11
	sw	s9, 132(sp)
	lw	s11, 132(sp)
	mv	s9,s11
	sw	s9, 136(sp)
	la	s9, array_block0
	lw	s11, 136(sp)
	lw	s10, 136(sp)
	slli	s11,s11,2
	add	s9,s9,s11
	sw	s10,0(s9)
	li	s10,1
	sw	s10, 140(sp)
	lw	s10, 60(sp)
	lw	s11, 140(sp)
	xor	s9,s10,s11
	sltiu	s9,s9,1
	sw	s9, 144(sp)
	lw	s9, 144(sp)
	bnez	s9,_ir_goto_label14
	j	_ir_goto_label15
_ir_goto_label14:
	la	s9, array_block0
	li	s10,0
	li	s11,0
	add	s9,s9,s11
	sw	s10,0(s9)
	lw	s10, 136(sp)
	mv	a0,s10
	li	a1,0
	addi	sp,sp,0
	call	mmerge
	addi	sp,sp,0
_ir_goto_label15:
	nop
	lw	s10, 60(sp)
	la	s9, n_block0
	lw	s11, 0(s9)
	xor	s9,s10,s11
	sltiu	s9,s9,1
	sw	s9, 148(sp)
	lw	s9, 148(sp)
	bnez	s9,_ir_goto_label16
	j	_ir_goto_label17
_ir_goto_label16:
	la	s9, array_block0
	lw	s11, 96(sp)
	lw	s10, 96(sp)
	slli	s11,s11,2
	add	s9,s9,s11
	sw	s10,0(s9)
	lw	s10, 136(sp)
	mv	a0,s10
	lw	s10, 96(sp)
	mv	a1,s10
	addi	sp,sp,0
	call	mmerge
	addi	sp,sp,0
_ir_goto_label17:
	nop
	lw	s10, 64(sp)
	la	s9, n_block0
	lw	s11, 0(s9)
	slt	s9,s10,s11
	sw	s9, 152(sp)
	lw	s9, 152(sp)
	bnez	s9,_ir_goto_label18
	j	_ir_goto_label19
_ir_goto_label18:
	li	s9,1
	sw	s9, 156(sp)
	lw	s9, 136(sp)
	lw	s11, 156(sp)
	add	s10,s9,s11
	sw	s10, 160(sp)
	la	s10, array_block0
	lw	s11, 160(sp)
	slli	s11,s11,2
	add	s10,s10,s11
	lw	s9,0(s10)
	sw	s9, 164(sp)
	li	s9,-1
	sw	s9, 168(sp)
	lw	s9, 164(sp)
	lw	s11, 168(sp)
	xor	s10,s9,s11
	sltiu	s10,s10,1
	xori	s10,s10,1
	sw	s10, 172(sp)
	lw	s10, 152(sp)
	lw	s11, 172(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 176(sp)
	j	_ir_goto_label20
_ir_goto_label19:
	li	s9,0
	sw	s9, 176(sp)
_ir_goto_label20:
	lw	s9, 176(sp)
	bnez	s9,_ir_goto_label21
	j	_ir_goto_label22
_ir_goto_label21:
	li	s9,1
	sw	s9, 180(sp)
	lw	s9, 136(sp)
	lw	s11, 180(sp)
	add	s10,s9,s11
	sw	s10, 184(sp)
	lw	s10, 136(sp)
	mv	a0,s10
	lw	s10, 184(sp)
	mv	a1,s10
	addi	sp,sp,0
	call	mmerge
	addi	sp,sp,0
_ir_goto_label22:
	nop
	li	s10,1
	sw	s10, 188(sp)
	lw	s10, 64(sp)
	lw	s11, 188(sp)
	slt	s9,s11,s10
	sw	s9, 192(sp)
	lw	s9, 192(sp)
	bnez	s9,_ir_goto_label23
	j	_ir_goto_label24
_ir_goto_label23:
	li	s9,1
	sw	s9, 196(sp)
	lw	s9, 136(sp)
	lw	s11, 196(sp)
	sub	s10,s9,s11
	sw	s10, 200(sp)
	la	s10, array_block0
	lw	s11, 200(sp)
	slli	s11,s11,2
	add	s10,s10,s11
	lw	s9,0(s10)
	sw	s9, 204(sp)
	li	s9,-1
	sw	s9, 208(sp)
	lw	s9, 204(sp)
	lw	s11, 208(sp)
	xor	s10,s9,s11
	sltiu	s10,s10,1
	xori	s10,s10,1
	sw	s10, 212(sp)
	lw	s10, 192(sp)
	lw	s11, 212(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 216(sp)
	j	_ir_goto_label25
_ir_goto_label24:
	li	s9,0
	sw	s9, 216(sp)
_ir_goto_label25:
	lw	s9, 216(sp)
	bnez	s9,_ir_goto_label26
	j	_ir_goto_label27
_ir_goto_label26:
	li	s9,1
	sw	s9, 220(sp)
	lw	s9, 136(sp)
	lw	s11, 220(sp)
	sub	s10,s9,s11
	sw	s10, 224(sp)
	lw	s10, 136(sp)
	mv	a0,s10
	lw	s10, 224(sp)
	mv	a1,s10
	addi	sp,sp,0
	call	mmerge
	addi	sp,sp,0
_ir_goto_label27:
	nop
	lw	s10, 60(sp)
	la	s9, n_block0
	lw	s11, 0(s9)
	slt	s9,s10,s11
	sw	s9, 228(sp)
	lw	s9, 228(sp)
	bnez	s9,_ir_goto_label28
	j	_ir_goto_label29
_ir_goto_label28:
	lw	s9, 136(sp)
	la	s10, n_block0
	lw	s11, 0(s10)
	add	s10,s9,s11
	sw	s10, 232(sp)
	la	s10, array_block0
	lw	s11, 232(sp)
	slli	s11,s11,2
	add	s10,s10,s11
	lw	s9,0(s10)
	sw	s9, 236(sp)
	li	s9,-1
	sw	s9, 240(sp)
	lw	s9, 236(sp)
	lw	s11, 240(sp)
	xor	s10,s9,s11
	sltiu	s10,s10,1
	xori	s10,s10,1
	sw	s10, 244(sp)
	lw	s10, 228(sp)
	lw	s11, 244(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 248(sp)
	j	_ir_goto_label30
_ir_goto_label29:
	li	s9,0
	sw	s9, 248(sp)
_ir_goto_label30:
	lw	s9, 248(sp)
	bnez	s9,_ir_goto_label31
	j	_ir_goto_label32
_ir_goto_label31:
	lw	s9, 136(sp)
	la	s10, n_block0
	lw	s11, 0(s10)
	add	s10,s9,s11
	sw	s10, 252(sp)
	lw	s10, 136(sp)
	mv	a0,s10
	lw	s10, 252(sp)
	mv	a1,s10
	addi	sp,sp,0
	call	mmerge
	addi	sp,sp,0
_ir_goto_label32:
	nop
	li	s10,1
	sw	s10, 256(sp)
	lw	s10, 60(sp)
	lw	s11, 256(sp)
	slt	s9,s11,s10
	sw	s9, 260(sp)
	lw	s9, 260(sp)
	bnez	s9,_ir_goto_label33
	j	_ir_goto_label34
_ir_goto_label33:
	lw	s9, 136(sp)
	la	s10, n_block0
	lw	s11, 0(s10)
	sub	s10,s9,s11
	sw	s10, 264(sp)
	la	s10, array_block0
	lw	s11, 264(sp)
	slli	s11,s11,2
	add	s10,s10,s11
	lw	s9,0(s10)
	sw	s9, 268(sp)
	li	s9,-1
	sw	s9, 272(sp)
	lw	s9, 268(sp)
	lw	s11, 272(sp)
	xor	s10,s9,s11
	sltiu	s10,s10,1
	xori	s10,s10,1
	sw	s10, 276(sp)
	lw	s10, 260(sp)
	lw	s11, 276(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 280(sp)
	j	_ir_goto_label35
_ir_goto_label34:
	li	s9,0
	sw	s9, 280(sp)
_ir_goto_label35:
	lw	s9, 280(sp)
	bnez	s9,_ir_goto_label36
	j	_ir_goto_label37
_ir_goto_label36:
	lw	s9, 136(sp)
	la	s10, n_block0
	lw	s11, 0(s10)
	sub	s10,s9,s11
	sw	s10, 284(sp)
	lw	s10, 136(sp)
	mv	a0,s10
	lw	s10, 284(sp)
	mv	a1,s10
	addi	sp,sp,0
	call	mmerge
	addi	sp,sp,0
_ir_goto_label37:
	nop
	la	s10, array_block0
	li	s11,0
	add	s10,s10,s11
	lw	s9,0(s10)
	sw	s9, 288(sp)
	li	s9,-1
	sw	s9, 292(sp)
	lw	s9, 288(sp)
	lw	s11, 292(sp)
	xor	s10,s9,s11
	sltiu	s10,s10,1
	xori	s10,s10,1
	sw	s10, 296(sp)
	lw	s10, 296(sp)
	bnez	s10,_ir_goto_label38
	j	_ir_goto_label39
_ir_goto_label38:
	la	s10, array_block0
	lw	s11, 96(sp)
	slli	s11,s11,2
	add	s10,s10,s11
	lw	s9,0(s10)
	sw	s9, 300(sp)
	li	s9,-1
	sw	s9, 304(sp)
	lw	s9, 300(sp)
	lw	s11, 304(sp)
	xor	s10,s9,s11
	sltiu	s10,s10,1
	xori	s10,s10,1
	sw	s10, 308(sp)
	lw	s10, 308(sp)
	bnez	s10,_ir_goto_label40
	j	_ir_goto_label41
_ir_goto_label40:
	li	a0,0
	addi	sp,sp,0
	call	findfa
	addi	sp,sp,0
	sw	a0, 312(sp)
	lw	s10, 96(sp)
	mv	a0,s10
	addi	sp,sp,0
	call	findfa
	addi	sp,sp,0
	sw	a0, 320(sp)
	lw	s10, 312(sp)
	lw	s11, 320(sp)
	xor	s9,s10,s11
	sltiu	s9,s9,1
	sw	s9, 324(sp)
	lw	s9, 308(sp)
	lw	s11, 324(sp)
	sltiu	s10,s9,1
	xori	s10,s10,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s10,s10,s11
	sw	s10, 328(sp)
	j	_ir_goto_label42
_ir_goto_label41:
	li	s10,0
	sw	s10, 328(sp)
_ir_goto_label42:
	lw	s10, 296(sp)
	lw	s11, 328(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 332(sp)
	j	_ir_goto_label43
_ir_goto_label39:
	li	s9,0
	sw	s9, 332(sp)
_ir_goto_label43:
	lw	s9, 332(sp)
	bnez	s9,_ir_goto_label44
	j	_ir_goto_label45
_ir_goto_label44:
	li	s9,1
	sw	s9, 80(sp)
	li	s9,1
	sw	s9, 336(sp)
	lw	s9, 76(sp)
	lw	s11, 336(sp)
	add	s10,s9,s11
	sw	s10, 340(sp)
	lw	s11, 340(sp)
	mv	s10,s11
	sw	s10, 344(sp)
	lw	s10, 344(sp)
	mv	a0,s10
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label45:
	nop
_ir_goto_label13:
	nop
	li	s10,1
	sw	s10, 348(sp)
	lw	s10, 76(sp)
	lw	s11, 348(sp)
	add	s9,s10,s11
	sw	s9, 352(sp)
	lw	s11, 352(sp)
	mv	s9,s11
	sw	s9, 76(sp)
	j	_ir_goto_label46
_ir_goto_label11:
	nop
	lw	s9, 80(sp)
	sltiu	s11,s9,1
	sw	s11, 356(sp)
	lw	s11, 356(sp)
	bnez	s11,_ir_goto_label47
	j	_ir_goto_label48
_ir_goto_label47:
	li	a0,-1.000000
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label48:
	nop
	j	_ir_goto_label49
_ir_goto_label9:
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
	addi	sp,sp,360
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
	addi	sp,sp,360
	ret
	.size	main, .-main
