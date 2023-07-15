	.option nopic
	.data
	.globl	INF_block0
	.type	INF_block0, @object
	.size	INF_block0, 4
	.align	4
INF_block0:
	.word	65535
	.globl	n_block0
	.type	n_block0, @object
	.size	n_block0, 4
	.align	4
n_block0:
	.word	0
	.globl	m_block0
	.type	m_block0, @object
	.size	m_block0, 4
	.align	4
m_block0:
	.word	0
	.globl	v1_block0
	.type	v1_block0, @object
	.size	v1_block0, 4
	.align	4
v1_block0:
	.word	0
	.globl	v2_block0
	.type	v2_block0, @object
	.size	v2_block0, 4
	.align	4
v2_block0:
	.word	0
	.globl	w_block0
	.type	w_block0, @object
	.size	w_block0, 4
	.align	4
w_block0:
	.word	0
	.bss
	.globl	e_block0
	.type	e_block0, @object
	.size	e_block0, 1024
	.align	4
e_block0:
	.space	1024
	.globl	book_block0
	.type	book_block0, @object
	.size	book_block0, 64
	.align	4
book_block0:
	.space	64
	.globl	dis_block0
	.type	dis_block0, @object
	.size	dis_block0, 64
	.align	4
dis_block0:
	.space	64
	.text
	.globl	Dijkstra
	.type	Dijkstra, @function
Dijkstra:
	addi	sp,sp,-288
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
	li	s11,1
	sw	s11, 52(sp)
_ir_goto_label2:
	lw	s11, 52(sp)
	la	s9, n_block0
	lw	s10, 0(s9)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 60(sp)
	lw	s9, 60(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,1
	sw	s9, 64(sp)
	lw	s10, 52(sp)
	mv	s9,s10
	sw	s9, 68(sp)
	li	s9,16
	sw	s9, 72(sp)
	lw	s9, 64(sp)
	lw	s10, 72(sp)
	mul	s11,s9,s10
	sw	s11, 76(sp)
	lw	s11, 76(sp)
	lw	s10, 68(sp)
	add	s9,s11,s10
	sw	s9, 80(sp)
	la	s9, e_block0
	lw	s10, 80(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 84(sp)
	la	s11, dis_block0
	lw	s10, 52(sp)
	lw	s9, 84(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	la	s9, book_block0
	lw	s10, 52(sp)
	li	s11,0
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 88(sp)
	lw	s11, 52(sp)
	lw	s10, 88(sp)
	add	s9,s11,s10
	sw	s9, 92(sp)
	lw	s10, 92(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	nop
	la	s9, book_block0
	li	s11,1
	li	s10,4
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 52(sp)
_ir_goto_label20:
	li	s11,1
	sw	s11, 96(sp)
	la	s10, n_block0
	lw	s11, 0(s10)
	lw	s10, 96(sp)
	sub	s9,s11,s10
	sw	s9, 100(sp)
	lw	s9, 52(sp)
	lw	s10, 100(sp)
	slt	s11,s10,s9
	xori	s11,s11,1
	sw	s11, 104(sp)
	lw	s11, 104(sp)
	bnez	s11,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
	li	s11,65535
	sw	s11, 108(sp)
	li	s11,0
	sw	s11, 112(sp)
	li	s11,1
	sw	s11, 116(sp)
_ir_goto_label12:
	lw	s11, 116(sp)
	la	s9, n_block0
	lw	s10, 0(s9)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 120(sp)
	lw	s9, 120(sp)
	bnez	s9,_ir_goto_label5
	j	_ir_goto_label6
_ir_goto_label5:
	la	s9, dis_block0
	lw	s10, 116(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 124(sp)
	lw	s11, 108(sp)
	lw	s10, 124(sp)
	slt	s9,s10,s11
	sw	s9, 128(sp)
	lw	s9, 128(sp)
	bnez	s9,_ir_goto_label7
	j	_ir_goto_label8
_ir_goto_label7:
	la	s9, book_block0
	lw	s10, 116(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 132(sp)
	li	s11,0
	sw	s11, 136(sp)
	lw	s11, 132(sp)
	lw	s10, 136(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 140(sp)
	lw	s9, 128(sp)
	lw	s10, 140(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s11,s11,s10
	sw	s11, 144(sp)
	j	_ir_goto_label9
_ir_goto_label8:
	li	s11,0
	sw	s11, 144(sp)
_ir_goto_label9:
	lw	s11, 144(sp)
	bnez	s11,_ir_goto_label10
	j	_ir_goto_label11
_ir_goto_label10:
	la	s11, dis_block0
	lw	s10, 116(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 148(sp)
	lw	s10, 148(sp)
	mv	s9,s10
	sw	s9, 108(sp)
	lw	s10, 116(sp)
	mv	s9,s10
	sw	s9, 112(sp)
_ir_goto_label11:
	nop
	li	s9,1
	sw	s9, 152(sp)
	lw	s9, 116(sp)
	lw	s10, 152(sp)
	add	s11,s9,s10
	sw	s11, 156(sp)
	lw	s10, 156(sp)
	mv	s11,s10
	sw	s11, 116(sp)
	j	_ir_goto_label12
_ir_goto_label6:
	nop
	la	s11, book_block0
	lw	s10, 112(sp)
	li	s9,1
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	li	s9,1
	sw	s9, 160(sp)
_ir_goto_label19:
	lw	s9, 160(sp)
	la	s11, n_block0
	lw	s10, 0(s11)
	slt	s11,s10,s9
	xori	s11,s11,1
	sw	s11, 164(sp)
	lw	s11, 164(sp)
	bnez	s11,_ir_goto_label13
	j	_ir_goto_label14
_ir_goto_label13:
	lw	s10, 112(sp)
	mv	s11,s10
	sw	s11, 168(sp)
	lw	s10, 160(sp)
	mv	s11,s10
	sw	s11, 172(sp)
	li	s11,16
	sw	s11, 176(sp)
	lw	s11, 168(sp)
	lw	s10, 176(sp)
	mul	s9,s11,s10
	sw	s9, 180(sp)
	lw	s9, 180(sp)
	lw	s10, 172(sp)
	add	s11,s9,s10
	sw	s11, 184(sp)
	la	s11, e_block0
	lw	s10, 184(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 188(sp)
	li	s9,65535
	sw	s9, 192(sp)
	lw	s9, 188(sp)
	lw	s10, 192(sp)
	slt	s11,s9,s10
	sw	s11, 196(sp)
	lw	s11, 196(sp)
	bnez	s11,_ir_goto_label15
	j	_ir_goto_label16
_ir_goto_label15:
	la	s11, dis_block0
	lw	s10, 160(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 200(sp)
	la	s9, dis_block0
	lw	s10, 112(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 204(sp)
	lw	s10, 112(sp)
	mv	s11,s10
	sw	s11, 208(sp)
	lw	s10, 160(sp)
	mv	s11,s10
	sw	s11, 212(sp)
	li	s11,16
	sw	s11, 216(sp)
	lw	s11, 208(sp)
	lw	s10, 216(sp)
	mul	s9,s11,s10
	sw	s9, 220(sp)
	lw	s9, 220(sp)
	lw	s10, 212(sp)
	add	s11,s9,s10
	sw	s11, 224(sp)
	la	s11, e_block0
	lw	s10, 224(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 228(sp)
	lw	s9, 204(sp)
	lw	s10, 228(sp)
	add	s11,s9,s10
	sw	s11, 232(sp)
	lw	s11, 200(sp)
	lw	s10, 232(sp)
	slt	s9,s10,s11
	sw	s9, 236(sp)
	lw	s9, 236(sp)
	bnez	s9,_ir_goto_label17
	j	_ir_goto_label18
_ir_goto_label17:
	la	s9, dis_block0
	lw	s10, 112(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 240(sp)
	lw	s10, 112(sp)
	mv	s11,s10
	sw	s11, 244(sp)
	lw	s10, 160(sp)
	mv	s11,s10
	sw	s11, 248(sp)
	li	s11,16
	sw	s11, 252(sp)
	lw	s11, 244(sp)
	lw	s10, 252(sp)
	mul	s9,s11,s10
	sw	s9, 256(sp)
	lw	s9, 256(sp)
	lw	s10, 248(sp)
	add	s11,s9,s10
	sw	s11, 260(sp)
	la	s11, e_block0
	lw	s10, 260(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 264(sp)
	lw	s9, 240(sp)
	lw	s10, 264(sp)
	add	s11,s9,s10
	sw	s11, 268(sp)
	la	s11, dis_block0
	lw	s10, 160(sp)
	lw	s9, 268(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
_ir_goto_label18:
	nop
_ir_goto_label16:
	nop
	li	s9,1
	sw	s9, 272(sp)
	lw	s9, 160(sp)
	lw	s10, 272(sp)
	add	s11,s9,s10
	sw	s11, 276(sp)
	lw	s10, 276(sp)
	mv	s11,s10
	sw	s11, 160(sp)
	j	_ir_goto_label19
_ir_goto_label14:
	nop
	li	s11,1
	sw	s11, 280(sp)
	lw	s11, 52(sp)
	lw	s10, 280(sp)
	add	s9,s11,s10
	sw	s9, 284(sp)
	lw	s10, 284(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	j	_ir_goto_label20
_ir_goto_label4:
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
	addi	sp,sp,288
	ret
	.size	Dijkstra, .-Dijkstra
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
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 56(sp)
	lw	s10, 56(sp)
	mv	s11,s10
	la	s10, n_block0
	sw	s11, 0(s10)
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 64(sp)
	lw	s10, 64(sp)
	mv	s11,s10
	la	s10, m_block0
	sw	s11, 0(s10)
	li	s11,1
	sw	s11, 52(sp)
_ir_goto_label29:
	lw	s11, 52(sp)
	la	s9, n_block0
	lw	s10, 0(s9)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 68(sp)
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label21
	j	_ir_goto_label22
_ir_goto_label21:
	li	s9,1
	sw	s9, 72(sp)
_ir_goto_label28:
	lw	s9, 72(sp)
	la	s11, n_block0
	lw	s10, 0(s11)
	slt	s11,s10,s9
	xori	s11,s11,1
	sw	s11, 76(sp)
	lw	s11, 76(sp)
	bnez	s11,_ir_goto_label23
	j	_ir_goto_label24
_ir_goto_label23:
	lw	s11, 52(sp)
	lw	s10, 72(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 80(sp)
	lw	s9, 80(sp)
	bnez	s9,_ir_goto_label25
	j	_ir_goto_label26
_ir_goto_label25:
	lw	s10, 52(sp)
	mv	s9,s10
	sw	s9, 84(sp)
	lw	s10, 72(sp)
	mv	s9,s10
	sw	s9, 88(sp)
	li	s9,16
	sw	s9, 92(sp)
	lw	s9, 84(sp)
	lw	s10, 92(sp)
	mul	s11,s9,s10
	sw	s11, 96(sp)
	lw	s11, 96(sp)
	lw	s10, 88(sp)
	add	s9,s11,s10
	sw	s9, 100(sp)
	la	s9, e_block0
	lw	s10, 100(sp)
	li	s11,0
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	j	_ir_goto_label27
_ir_goto_label26:
	lw	s10, 52(sp)
	mv	s11,s10
	sw	s11, 104(sp)
	lw	s10, 72(sp)
	mv	s11,s10
	sw	s11, 108(sp)
	li	s11,16
	sw	s11, 112(sp)
	lw	s11, 104(sp)
	lw	s10, 112(sp)
	mul	s9,s11,s10
	sw	s9, 116(sp)
	lw	s9, 116(sp)
	lw	s10, 108(sp)
	add	s11,s9,s10
	sw	s11, 120(sp)
	la	s11, e_block0
	lw	s10, 120(sp)
	li	s9,65535
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
_ir_goto_label27:
	nop
	li	s9,1
	sw	s9, 124(sp)
	lw	s9, 72(sp)
	lw	s10, 124(sp)
	add	s11,s9,s10
	sw	s11, 128(sp)
	lw	s10, 128(sp)
	mv	s11,s10
	sw	s11, 72(sp)
	j	_ir_goto_label28
_ir_goto_label24:
	nop
	li	s11,1
	sw	s11, 132(sp)
	lw	s11, 52(sp)
	lw	s10, 132(sp)
	add	s9,s11,s10
	sw	s9, 136(sp)
	lw	s10, 136(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	j	_ir_goto_label29
_ir_goto_label22:
	nop
	li	s9,1
	sw	s9, 52(sp)
_ir_goto_label32:
	lw	s9, 52(sp)
	la	s11, m_block0
	lw	s10, 0(s11)
	slt	s11,s10,s9
	xori	s11,s11,1
	sw	s11, 140(sp)
	lw	s11, 140(sp)
	bnez	s11,_ir_goto_label30
	j	_ir_goto_label31
_ir_goto_label30:
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 144(sp)
	lw	s10, 144(sp)
	mv	s11,s10
	sw	s11, 148(sp)
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 152(sp)
	lw	s10, 152(sp)
	mv	s11,s10
	sw	s11, 156(sp)
	addi	sp,sp,0
	call	getint
	addi	sp,sp,0
	sw	a0, 160(sp)
	lw	s10, 148(sp)
	mv	s11,s10
	sw	s11, 164(sp)
	lw	s10, 156(sp)
	mv	s11,s10
	sw	s11, 168(sp)
	li	s11,16
	sw	s11, 172(sp)
	lw	s11, 164(sp)
	lw	s10, 172(sp)
	mul	s9,s11,s10
	sw	s9, 176(sp)
	lw	s9, 176(sp)
	lw	s10, 168(sp)
	add	s11,s9,s10
	sw	s11, 180(sp)
	la	s11, e_block0
	lw	s10, 180(sp)
	lw	s9, 160(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	li	s9,1
	sw	s9, 184(sp)
	lw	s9, 52(sp)
	lw	s10, 184(sp)
	add	s11,s9,s10
	sw	s11, 188(sp)
	lw	s10, 188(sp)
	mv	s11,s10
	sw	s11, 52(sp)
	j	_ir_goto_label32
_ir_goto_label31:
	nop
	addi	sp,sp,0
	call	Dijkstra
	addi	sp,sp,0
	li	s11,1
	sw	s11, 52(sp)
_ir_goto_label35:
	lw	s11, 52(sp)
	la	s9, n_block0
	lw	s10, 0(s9)
	slt	s9,s10,s11
	xori	s9,s9,1
	sw	s9, 192(sp)
	lw	s9, 192(sp)
	bnez	s9,_ir_goto_label33
	j	_ir_goto_label34
_ir_goto_label33:
	la	s9, dis_block0
	lw	s10, 52(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 196(sp)
	lw	s11, 196(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	a0,32
	addi	sp,sp,0
	call	putch
	addi	sp,sp,0
	li	s11,1
	sw	s11, 200(sp)
	lw	s11, 52(sp)
	lw	s10, 200(sp)
	add	s9,s11,s10
	sw	s9, 204(sp)
	lw	s10, 204(sp)
	mv	s9,s10
	sw	s9, 52(sp)
	j	_ir_goto_label35
_ir_goto_label34:
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
