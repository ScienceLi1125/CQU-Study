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
	.globl	d_block0
	.type	d_block0, @object
	.size	d_block0, 4
	.align	4
d_block0:
	.word	0
	.text
	.globl	set_a
	.type	set_a, @function
set_a:
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
	lw	s10, 52(sp)
	mv	s11,s10
	la	s10, a_block0
	sw	s11, 0(s10)
	la	s10, a_block0
	lw	s11, 0(s10)
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
	addi	sp,sp,56
	ret
	.size	set_a, .-set_a
	.globl	set_b
	.type	set_b, @function
set_b:
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
	lw	s10, 52(sp)
	mv	s11,s10
	la	s10, b_block0
	sw	s11, 0(s10)
	la	s10, b_block0
	lw	s11, 0(s10)
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
	addi	sp,sp,56
	ret
	.size	set_b, .-set_b
	.globl	set_d
	.type	set_d, @function
set_d:
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
	lw	s10, 52(sp)
	mv	s11,s10
	la	s10, d_block0
	sw	s11, 0(s10)
	la	s10, d_block0
	lw	s11, 0(s10)
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
	addi	sp,sp,56
	ret
	.size	set_d, .-set_d
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
	li	s11,2
	la	s10, a_block0
	sw	s11, 0(s10)
	li	s11,3
	la	s10, b_block0
	sw	s11, 0(s10)
	li	a0,0
	addi	sp,sp,0
	call	set_a
	addi	sp,sp,0
	sw	a0, 52(sp)
	lw	s11, 52(sp)
	bnez	s11,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	a0,1
	addi	sp,sp,0
	call	set_b
	addi	sp,sp,0
	sw	a0, 60(sp)
	lw	s11, 52(sp)
	lw	s10, 60(sp)
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
	j	_ir_goto_label3
_ir_goto_label3:
	nop
	la	s10, a_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	la	s10, b_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s9,2
	la	s10, a_block0
	sw	s9, 0(s10)
	li	s9,3
	la	s10, b_block0
	sw	s9, 0(s10)
	li	a0,0
	addi	sp,sp,0
	call	set_a
	addi	sp,sp,0
	sw	a0, 72(sp)
	lw	s9, 72(sp)
	bnez	s9,_ir_goto_label4
	j	_ir_goto_label5
_ir_goto_label4:
	li	a0,1
	addi	sp,sp,0
	call	set_b
	addi	sp,sp,0
	sw	a0, 76(sp)
	lw	s9, 72(sp)
	lw	s10, 76(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 80(sp)
	j	_ir_goto_label6
_ir_goto_label5:
	li	s11,0
	sw	s11, 80(sp)
_ir_goto_label6:
	lw	s11, 80(sp)
	bnez	s11,_ir_goto_label7
	j	_ir_goto_label7
_ir_goto_label7:
	nop
	la	s10, a_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	la	s10, b_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s11,1
	sw	s11, 84(sp)
	li	s11,2
	la	s10, d_block0
	sw	s11, 0(s10)
	li	s11,1
	bnez	s11,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	a0,3
	addi	sp,sp,0
	call	set_d
	addi	sp,sp,0
	sw	a0, 88(sp)
	lw	s10, 88(sp)
	li	s11,1
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 96(sp)
	j	_ir_goto_label10
_ir_goto_label9:
	li	s9,0
	sw	s9, 96(sp)
_ir_goto_label10:
	lw	s9, 96(sp)
	bnez	s9,_ir_goto_label11
	j	_ir_goto_label11
_ir_goto_label11:
	nop
	la	s10, d_block0
	lw	s9, 0(s10)
	mv	a0,s9
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s9,1
	bnez	s9,_ir_goto_label12
	j	_ir_goto_label13
_ir_goto_label12:
	li	s9,1
	sw	s9, 100(sp)
	j	_ir_goto_label14
_ir_goto_label13:
	li	a0,4
	addi	sp,sp,0
	call	set_d
	addi	sp,sp,0
	sw	a0, 104(sp)
	lw	s10, 104(sp)
	li	s9,1
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 100(sp)
_ir_goto_label14:
	lw	s11, 100(sp)
	bnez	s11,_ir_goto_label15
	j	_ir_goto_label15
_ir_goto_label15:
	nop
	la	s10, d_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s11,1
	bnez	s11,_ir_goto_label16
	j	_ir_goto_label17
_ir_goto_label16:
	li	a0,65
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label17:
	nop
	li	s11,0
	bnez	s11,_ir_goto_label18
	j	_ir_goto_label19
_ir_goto_label18:
	li	a0,66
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label19:
	nop
	li	s11,0
	bnez	s11,_ir_goto_label20
	j	_ir_goto_label21
_ir_goto_label20:
	li	a0,67
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label21:
	nop
	li	s11,1
	bnez	s11,_ir_goto_label22
	j	_ir_goto_label23
_ir_goto_label22:
	li	a0,68
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label23:
	nop
	li	s11,0
	bnez	s11,_ir_goto_label24
	j	_ir_goto_label25
_ir_goto_label24:
	li	a0,69
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label25:
	nop
	li	s11,1
	bnez	s11,_ir_goto_label26
	j	_ir_goto_label27
_ir_goto_label26:
	li	a0,70
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label27:
	nop
	li	a0,10
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s11,0
	sw	s11, 108(sp)
	li	s11,1
	sw	s11, 112(sp)
	li	s11,2
	sw	s11, 116(sp)
	li	s11,3
	sw	s11, 120(sp)
	li	s11,4
	sw	s11, 124(sp)
_ir_goto_label33:
	lw	s11, 108(sp)
	bnez	s11,_ir_goto_label28
	j	_ir_goto_label29
_ir_goto_label28:
	lw	s11, 108(sp)
	lw	s10, 112(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 128(sp)
	j	_ir_goto_label30
_ir_goto_label29:
	li	s9,0
	sw	s9, 128(sp)
_ir_goto_label30:
	lw	s9, 128(sp)
	bnez	s9,_ir_goto_label31
	j	_ir_goto_label32
_ir_goto_label31:
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	j	_ir_goto_label33
_ir_goto_label32:
	nop
	lw	s9, 108(sp)
	bnez	s9,_ir_goto_label34
	j	_ir_goto_label35
_ir_goto_label34:
	li	s9,1
	sw	s9, 132(sp)
	j	_ir_goto_label36
_ir_goto_label35:
	lw	s9, 108(sp)
	lw	s10, 112(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 132(sp)
_ir_goto_label36:
	lw	s11, 132(sp)
	bnez	s11,_ir_goto_label37
	j	_ir_goto_label38
_ir_goto_label37:
	li	a0,67
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label38:
	nop
	lw	s11, 108(sp)
	lw	s10, 112(sp)
	slt	s9,s11,s10
	xori	s9,s9,1
	sw	s9, 136(sp)
	lw	s9, 136(sp)
	bnez	s9,_ir_goto_label39
	j	_ir_goto_label40
_ir_goto_label39:
	li	s9,1
	sw	s9, 140(sp)
	j	_ir_goto_label41
_ir_goto_label40:
	lw	s9, 112(sp)
	lw	s10, 108(sp)
	slt	s11,s10,s9
	xori	s11,s11,1
	sw	s11, 144(sp)
	lw	s11, 136(sp)
	lw	s10, 144(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 140(sp)
_ir_goto_label41:
	lw	s9, 140(sp)
	bnez	s9,_ir_goto_label42
	j	_ir_goto_label43
_ir_goto_label42:
	li	a0,72
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label43:
	nop
	lw	s9, 116(sp)
	lw	s10, 112(sp)
	slt	s11,s9,s10
	xori	s11,s11,1
	sw	s11, 148(sp)
	lw	s11, 148(sp)
	bnez	s11,_ir_goto_label44
	j	_ir_goto_label45
_ir_goto_label44:
	lw	s11, 124(sp)
	lw	s10, 120(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 152(sp)
	lw	s9, 148(sp)
	lw	s10, 152(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 156(sp)
	j	_ir_goto_label46
_ir_goto_label45:
	li	s11,0
	sw	s11, 156(sp)
_ir_goto_label46:
	lw	s11, 156(sp)
	bnez	s11,_ir_goto_label47
	j	_ir_goto_label48
_ir_goto_label47:
	li	a0,73
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label48:
	nop
	lw	s11, 112(sp)
	sltiu	s10,s11,1
	sw	s10, 160(sp)
	lw	s10, 108(sp)
	lw	s11, 160(sp)
	xor	s9,s10,s11
	sltiu	s9,s9,1
	sw	s9, 164(sp)
	lw	s9, 164(sp)
	bnez	s9,_ir_goto_label49
	j	_ir_goto_label50
_ir_goto_label49:
	lw	s9, 120(sp)
	lw	s11, 120(sp)
	slt	s10,s9,s11
	sw	s10, 168(sp)
	lw	s10, 164(sp)
	lw	s11, 168(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	and	s9,s9,s11
	sw	s9, 172(sp)
	j	_ir_goto_label51
_ir_goto_label50:
	li	s9,0
	sw	s9, 172(sp)
_ir_goto_label51:
	lw	s9, 172(sp)
	bnez	s9,_ir_goto_label52
	j	_ir_goto_label53
_ir_goto_label52:
	li	s9,1
	sw	s9, 176(sp)
	j	_ir_goto_label54
_ir_goto_label53:
	lw	s9, 124(sp)
	lw	s11, 124(sp)
	slt	s10,s9,s11
	xori	s10,s10,1
	sw	s10, 180(sp)
	lw	s10, 172(sp)
	lw	s11, 180(sp)
	sltiu	s9,s10,1
	xori	s9,s9,1
	sltiu	s11,s11,1
	xori	s11,s11,1
	or	s9,s9,s11
	sw	s9, 176(sp)
_ir_goto_label54:
	lw	s9, 176(sp)
	bnez	s9,_ir_goto_label55
	j	_ir_goto_label56
_ir_goto_label55:
	li	a0,74
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label56:
	nop
	lw	s9, 112(sp)
	sltiu	s11,s9,1
	sw	s11, 184(sp)
	lw	s11, 108(sp)
	lw	s9, 184(sp)
	xor	s10,s11,s9
	sltiu	s10,s10,1
	sw	s10, 188(sp)
	lw	s10, 188(sp)
	bnez	s10,_ir_goto_label57
	j	_ir_goto_label58
_ir_goto_label57:
	li	s10,1
	sw	s10, 192(sp)
	j	_ir_goto_label59
_ir_goto_label58:
	lw	s10, 120(sp)
	lw	s9, 120(sp)
	slt	s11,s10,s9
	sw	s11, 196(sp)
	lw	s11, 196(sp)
	bnez	s11,_ir_goto_label60
	j	_ir_goto_label61
_ir_goto_label60:
	lw	s11, 124(sp)
	lw	s9, 124(sp)
	slt	s10,s11,s9
	xori	s10,s10,1
	sw	s10, 200(sp)
	lw	s10, 196(sp)
	lw	s9, 200(sp)
	sltiu	s11,s10,1
	xori	s11,s11,1
	sltiu	s9,s9,1
	xori	s9,s9,1
	and	s11,s11,s9
	sw	s11, 204(sp)
	j	_ir_goto_label62
_ir_goto_label61:
	li	s11,0
	sw	s11, 204(sp)
_ir_goto_label62:
	lw	s11, 188(sp)
	lw	s9, 204(sp)
	sltiu	s10,s11,1
	xori	s10,s10,1
	sltiu	s9,s9,1
	xori	s9,s9,1
	or	s10,s10,s9
	sw	s10, 192(sp)
_ir_goto_label59:
	lw	s10, 192(sp)
	bnez	s10,_ir_goto_label63
	j	_ir_goto_label64
_ir_goto_label63:
	li	a0,75
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
_ir_goto_label64:
	nop
	li	a0,10
	addi	sp,sp,0
	call	putch
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
