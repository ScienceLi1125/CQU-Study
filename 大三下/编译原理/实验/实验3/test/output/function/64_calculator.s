	.option nopic
	.data
	.globl	intt_block0
	.type	intt_block0, @object
	.size	intt_block0, 4
	.align	4
intt_block0:
	.word	0
	.globl	chat_block0
	.type	chat_block0, @object
	.size	chat_block0, 4
	.align	4
chat_block0:
	.word	0
	.globl	i_block0
	.type	i_block0, @object
	.size	i_block0, 4
	.align	4
i_block0:
	.word	0
	.globl	ii_block0
	.type	ii_block0, @object
	.size	ii_block0, 4
	.align	4
ii_block0:
	.word	1
	.globl	c_block0
	.type	c_block0, @object
	.size	c_block0, 4
	.align	4
c_block0:
	.word	0
	.bss
	.globl	ints_block0
	.type	ints_block0, @object
	.size	ints_block0, 40000
	.align	4
ints_block0:
	.space	40000
	.globl	get2_block0
	.type	get2_block0, @object
	.size	get2_block0, 40000
	.align	4
get2_block0:
	.space	40000
	.globl	chas_block0
	.type	chas_block0, @object
	.size	chas_block0, 40000
	.align	4
chas_block0:
	.space	40000
	.globl	get_block0
	.type	get_block0, @object
	.size	get_block0, 40000
	.align	4
get_block0:
	.space	40000
	.text
	.globl	isdigit
	.type	isdigit, @function
isdigit:
	addi	sp,sp,-76
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
	li	s11,48
	sw	s11, 56(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	slt	s9,s11,s10
	xori	s9,s9,1
	sw	s9, 60(sp)
	lw	s9, 60(sp)
	bnez	s9,_ir_goto_label0
	j	_ir_goto_label1
_ir_goto_label0:
	li	s9,57
	sw	s9, 64(sp)
	lw	s9, 52(sp)
	lw	s10, 64(sp)
	slt	s11,s10,s9
	xori	s11,s11,1
	sw	s11, 68(sp)
	lw	s11, 60(sp)
	lw	s10, 68(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 72(sp)
	j	_ir_goto_label2
_ir_goto_label1:
	li	s9,0
	sw	s9, 72(sp)
_ir_goto_label2:
	lw	s9, 72(sp)
	bnez	s9,_ir_goto_label3
	j	_ir_goto_label4
_ir_goto_label3:
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
	addi	sp,sp,76
	ret
_ir_goto_label4:
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
	addi	sp,sp,76
	ret
	.size	isdigit, .-isdigit
	.globl	power
	.type	power, @function
power:
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
	li	s11,1
	sw	s11, 60(sp)
_ir_goto_label7:
	li	s11,0
	sw	s11, 64(sp)
	lw	s11, 56(sp)
	lw	s10, 64(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 68(sp)
	lw	s9, 68(sp)
	bnez	s9,_ir_goto_label5
	j	_ir_goto_label6
_ir_goto_label5:
	lw	s9, 60(sp)
	lw	s10, 52(sp)
	mul	s11,s9,s10
	sw	s11, 72(sp)
	lw	s10, 72(sp)
	mv	s11,s10
	sw	s11, 60(sp)
	li	s11,1
	sw	s11, 76(sp)
	lw	s11, 56(sp)
	lw	s10, 76(sp)
	sub	s9,s11,s10
	sw	s9, 80(sp)
	lw	s10, 80(sp)
	mv	s9,s10
	sw	s9, 56(sp)
	j	_ir_goto_label7
_ir_goto_label6:
	nop
	lw	s9, 60(sp)
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
	.size	power, .-power
	.globl	getstr
	.type	getstr, @function
getstr:
	addi	sp,sp,-104
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
	addi	sp,sp,0
	call	getch
	addi	sp,sp,0
	sw	a0, 56(sp)
	lw	s10, 56(sp)
	mv	s11,s10
	sw	s11, 64(sp)
	li	s11,0
	sw	s11, 68(sp)
_ir_goto_label13:
	li	s11,13
	sw	s11, 72(sp)
	lw	s11, 64(sp)
	lw	s10, 72(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 76(sp)
	lw	s9, 76(sp)
	bnez	s9,_ir_goto_label8
	j	_ir_goto_label9
_ir_goto_label8:
	li	s9,10
	sw	s9, 80(sp)
	lw	s9, 64(sp)
	lw	s10, 80(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	xori	s11,s11,1
	sw	s11, 84(sp)
	lw	s11, 76(sp)
	lw	s10, 84(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	and	s9,s9,s10
	sw	s9, 88(sp)
	j	_ir_goto_label10
_ir_goto_label9:
	li	s9,0
	sw	s9, 88(sp)
_ir_goto_label10:
	lw	s9, 88(sp)
	bnez	s9,_ir_goto_label11
	j	_ir_goto_label12
_ir_goto_label11:
	lw	s9, 52(sp)
	lw	s10, 68(sp)
	lw	s11, 64(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 92(sp)
	lw	s11, 68(sp)
	lw	s10, 92(sp)
	add	s9,s11,s10
	sw	s9, 96(sp)
	lw	s10, 96(sp)
	mv	s9,s10
	sw	s9, 68(sp)
	addi	sp,sp,0
	call	getch
	addi	sp,sp,0
	sw	a0, 100(sp)
	lw	s10, 100(sp)
	mv	s9,s10
	sw	s9, 64(sp)
	j	_ir_goto_label13
_ir_goto_label12:
	nop
	lw	s9, 68(sp)
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
	addi	sp,sp,104
	ret
	.size	getstr, .-getstr
	.globl	intpush
	.type	intpush, @function
intpush:
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
	sw	a0, 52(sp)
	li	s11,1
	sw	s11, 56(sp)
	la	s10, intt_block0
	lw	s11, 0(s10)
	lw	s10, 56(sp)
	add	s9,s11,s10
	sw	s9, 60(sp)
	lw	s10, 60(sp)
	mv	s9,s10
	la	s10, intt_block0
	sw	s9, 0(s10)
	la	s9, ints_block0
	la	s11, intt_block0
	lw	s10, 0(s11)
	lw	s11, 52(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
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
	.size	intpush, .-intpush
	.globl	chapush
	.type	chapush, @function
chapush:
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
	sw	a0, 52(sp)
	li	s11,1
	sw	s11, 56(sp)
	la	s10, chat_block0
	lw	s11, 0(s10)
	lw	s10, 56(sp)
	add	s9,s11,s10
	sw	s9, 60(sp)
	lw	s10, 60(sp)
	mv	s9,s10
	la	s10, chat_block0
	sw	s9, 0(s10)
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	lw	s11, 52(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
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
	.size	chapush, .-chapush
	.globl	intpop
	.type	intpop, @function
intpop:
	addi	sp,sp,-72
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
	li	s11,1
	sw	s11, 52(sp)
	la	s10, intt_block0
	lw	s11, 0(s10)
	lw	s10, 52(sp)
	sub	s9,s11,s10
	sw	s9, 56(sp)
	lw	s10, 56(sp)
	mv	s9,s10
	la	s10, intt_block0
	sw	s9, 0(s10)
	li	s9,1
	sw	s9, 60(sp)
	la	s10, intt_block0
	lw	s9, 0(s10)
	lw	s10, 60(sp)
	add	s11,s9,s10
	sw	s11, 64(sp)
	la	s11, ints_block0
	lw	s10, 64(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 68(sp)
	lw	s9, 68(sp)
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
	addi	sp,sp,72
	ret
	.size	intpop, .-intpop
	.globl	chapop
	.type	chapop, @function
chapop:
	addi	sp,sp,-72
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
	li	s11,1
	sw	s11, 52(sp)
	la	s10, chat_block0
	lw	s11, 0(s10)
	lw	s10, 52(sp)
	sub	s9,s11,s10
	sw	s9, 56(sp)
	lw	s10, 56(sp)
	mv	s9,s10
	la	s10, chat_block0
	sw	s9, 0(s10)
	li	s9,1
	sw	s9, 60(sp)
	la	s10, chat_block0
	lw	s9, 0(s10)
	lw	s10, 60(sp)
	add	s11,s9,s10
	sw	s11, 64(sp)
	la	s11, chas_block0
	lw	s10, 64(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 68(sp)
	lw	s9, 68(sp)
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
	addi	sp,sp,72
	ret
	.size	chapop, .-chapop
	.globl	intadd
	.type	intadd, @function
intadd:
	addi	sp,sp,-76
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
	la	s11, ints_block0
	la	s9, intt_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 56(sp)
	li	s9,10
	sw	s9, 60(sp)
	lw	s9, 56(sp)
	lw	s10, 60(sp)
	mul	s11,s9,s10
	sw	s11, 64(sp)
	la	s11, ints_block0
	la	s9, intt_block0
	lw	s10, 0(s9)
	lw	s9, 64(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	la	s9, ints_block0
	la	s11, intt_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 68(sp)
	lw	s11, 68(sp)
	lw	s10, 52(sp)
	add	s9,s11,s10
	sw	s9, 72(sp)
	la	s9, ints_block0
	la	s11, intt_block0
	lw	s10, 0(s11)
	lw	s11, 72(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
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
	addi	sp,sp,76
	ret
	.size	intadd, .-intadd
	.globl	find
	.type	find, @function
find:
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
	addi	sp,sp,0
	call	chapop
	addi	sp,sp,0
	sw	a0, 52(sp)
	lw	s10, 52(sp)
	mv	s11,s10
	la	s10, c_block0
	sw	s11, 0(s10)
	la	s11, get2_block0
	la	s9, ii_block0
	lw	s10, 0(s9)
	li	s9,32
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	li	s9,1
	sw	s9, 60(sp)
	la	s10, ii_block0
	lw	s9, 0(s10)
	lw	s10, 60(sp)
	add	s11,s9,s10
	sw	s11, 64(sp)
	la	s11, get2_block0
	lw	s10, 64(sp)
	la	s8, c_block0
	lw	s9, 0(s8)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	li	s9,2
	sw	s9, 68(sp)
	la	s10, ii_block0
	lw	s9, 0(s10)
	lw	s10, 68(sp)
	add	s11,s9,s10
	sw	s11, 72(sp)
	lw	s10, 72(sp)
	mv	s11,s10
	la	s10, ii_block0
	sw	s11, 0(s10)
	li	s11,0
	sw	s11, 76(sp)
	la	s10, chat_block0
	lw	s11, 0(s10)
	lw	s10, 76(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 80(sp)
	lw	s9, 80(sp)
	bnez	s9,_ir_goto_label14
	j	_ir_goto_label15
_ir_goto_label14:
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
	addi	sp,sp,84
	ret
_ir_goto_label15:
	nop
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
	addi	sp,sp,84
	ret
	.size	find, .-find
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-1024
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
	la	s10, intt_block0
	sw	s11, 0(s10)
	li	s11,0
	la	s10, chat_block0
	sw	s11, 0(s10)
	la	s11, get_block0
	mv	a0,s11
	addi	sp,sp,0
	call	getstr
	addi	sp,sp,0
	sw	a0, 52(sp)
	lw	s10, 52(sp)
	mv	s11,s10
	sw	s11, 60(sp)
_ir_goto_label117:
	la	s10, i_block0
	lw	s11, 0(s10)
	lw	s10, 60(sp)
	slt	s9,s11,s10
	sw	s9, 64(sp)
	lw	s9, 64(sp)
	bnez	s9,_ir_goto_label16
	j	_ir_goto_label17
_ir_goto_label16:
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 68(sp)
	lw	s11, 68(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	isdigit
	addi	sp,sp,0
	sw	a0, 72(sp)
	li	s11,1
	sw	s11, 80(sp)
	lw	s11, 72(sp)
	lw	s10, 80(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 84(sp)
	lw	s9, 84(sp)
	bnez	s9,_ir_goto_label18
	j	_ir_goto_label19
_ir_goto_label18:
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 88(sp)
	la	s11, get2_block0
	la	s9, ii_block0
	lw	s10, 0(s9)
	lw	s9, 88(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	sw	s9,0(s11)
	li	s9,1
	sw	s9, 92(sp)
	la	s10, ii_block0
	lw	s9, 0(s10)
	lw	s10, 92(sp)
	add	s11,s9,s10
	sw	s11, 96(sp)
	lw	s10, 96(sp)
	mv	s11,s10
	la	s10, ii_block0
	sw	s11, 0(s10)
	j	_ir_goto_label20
_ir_goto_label19:
	la	s11, get_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 100(sp)
	li	s9,40
	sw	s9, 104(sp)
	lw	s9, 100(sp)
	lw	s10, 104(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 108(sp)
	lw	s11, 108(sp)
	bnez	s11,_ir_goto_label21
	j	_ir_goto_label22
_ir_goto_label21:
	li	a0,40
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label22:
	nop
	la	s11, get_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 112(sp)
	li	s9,94
	sw	s9, 116(sp)
	lw	s9, 112(sp)
	lw	s10, 116(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 120(sp)
	lw	s11, 120(sp)
	bnez	s11,_ir_goto_label23
	j	_ir_goto_label24
_ir_goto_label23:
	li	a0,94
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label24:
	nop
	la	s11, get_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 124(sp)
	li	s9,41
	sw	s9, 128(sp)
	lw	s9, 124(sp)
	lw	s10, 128(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 132(sp)
	lw	s11, 132(sp)
	bnez	s11,_ir_goto_label25
	j	_ir_goto_label26
_ir_goto_label25:
	addi	sp,sp,0
	call	chapop
	addi	sp,sp,0
	sw	a0, 136(sp)
	lw	s10, 136(sp)
	mv	s11,s10
	la	s10, c_block0
	sw	s11, 0(s10)
_ir_goto_label29:
	li	s11,40
	sw	s11, 144(sp)
	la	s10, c_block0
	lw	s11, 0(s10)
	lw	s10, 144(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 148(sp)
	lw	s9, 148(sp)
	bnez	s9,_ir_goto_label27
	j	_ir_goto_label28
_ir_goto_label27:
	la	s9, get2_block0
	la	s11, ii_block0
	lw	s10, 0(s11)
	li	s11,32
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 152(sp)
	la	s10, ii_block0
	lw	s11, 0(s10)
	lw	s10, 152(sp)
	add	s9,s11,s10
	sw	s9, 156(sp)
	la	s9, get2_block0
	lw	s10, 156(sp)
	la	s8, c_block0
	lw	s11, 0(s8)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,2
	sw	s11, 160(sp)
	la	s10, ii_block0
	lw	s11, 0(s10)
	lw	s10, 160(sp)
	add	s9,s11,s10
	sw	s9, 164(sp)
	lw	s10, 164(sp)
	mv	s9,s10
	la	s10, ii_block0
	sw	s9, 0(s10)
	addi	sp,sp,0
	call	chapop
	addi	sp,sp,0
	sw	a0, 168(sp)
	lw	s10, 168(sp)
	mv	s9,s10
	la	s10, c_block0
	sw	s9, 0(s10)
	j	_ir_goto_label29
_ir_goto_label28:
	nop
_ir_goto_label26:
	nop
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 172(sp)
	li	s11,43
	sw	s11, 176(sp)
	lw	s11, 172(sp)
	lw	s10, 176(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 180(sp)
	lw	s9, 180(sp)
	bnez	s9,_ir_goto_label30
	j	_ir_goto_label31
_ir_goto_label30:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 184(sp)
	li	s11,43
	sw	s11, 188(sp)
	lw	s11, 184(sp)
	lw	s10, 188(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 192(sp)
	lw	s9, 192(sp)
	bnez	s9,_ir_goto_label32
	j	_ir_goto_label33
_ir_goto_label32:
	li	s9,1
	sw	s9, 196(sp)
	j	_ir_goto_label34
_ir_goto_label33:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 200(sp)
	li	s11,45
	sw	s11, 204(sp)
	lw	s11, 200(sp)
	lw	s10, 204(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 208(sp)
	lw	s9, 208(sp)
	bnez	s9,_ir_goto_label35
	j	_ir_goto_label36
_ir_goto_label35:
	li	s9,1
	sw	s9, 212(sp)
	j	_ir_goto_label37
_ir_goto_label36:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 216(sp)
	li	s11,42
	sw	s11, 220(sp)
	lw	s11, 216(sp)
	lw	s10, 220(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 224(sp)
	lw	s9, 224(sp)
	bnez	s9,_ir_goto_label38
	j	_ir_goto_label39
_ir_goto_label38:
	li	s9,1
	sw	s9, 228(sp)
	j	_ir_goto_label40
_ir_goto_label39:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 232(sp)
	li	s11,47
	sw	s11, 236(sp)
	lw	s11, 232(sp)
	lw	s10, 236(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 240(sp)
	lw	s9, 240(sp)
	bnez	s9,_ir_goto_label41
	j	_ir_goto_label42
_ir_goto_label41:
	li	s9,1
	sw	s9, 244(sp)
	j	_ir_goto_label43
_ir_goto_label42:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 248(sp)
	li	s11,37
	sw	s11, 252(sp)
	lw	s11, 248(sp)
	lw	s10, 252(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 256(sp)
	lw	s9, 256(sp)
	bnez	s9,_ir_goto_label44
	j	_ir_goto_label45
_ir_goto_label44:
	li	s9,1
	sw	s9, 260(sp)
	j	_ir_goto_label46
_ir_goto_label45:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 264(sp)
	li	s11,94
	sw	s11, 268(sp)
	lw	s11, 264(sp)
	lw	s10, 268(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 272(sp)
	lw	s9, 256(sp)
	lw	s10, 272(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 260(sp)
_ir_goto_label46:
	lw	s11, 240(sp)
	lw	s10, 260(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 244(sp)
_ir_goto_label43:
	lw	s9, 224(sp)
	lw	s10, 244(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 228(sp)
_ir_goto_label40:
	lw	s11, 208(sp)
	lw	s10, 228(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 212(sp)
_ir_goto_label37:
	lw	s9, 192(sp)
	lw	s10, 212(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 196(sp)
_ir_goto_label34:
	lw	s11, 196(sp)
	bnez	s11,_ir_goto_label47
	j	_ir_goto_label48
_ir_goto_label47:
	addi	sp,sp,0
	call	find
	addi	sp,sp,0
	sw	a0, 276(sp)
	li	s11,0
	sw	s11, 284(sp)
	lw	s11, 276(sp)
	lw	s10, 284(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 288(sp)
	lw	s9, 288(sp)
	bnez	s9,_ir_goto_label49
	j	_ir_goto_label50
_ir_goto_label49:
	j	_ir_goto_label48
_ir_goto_label50:
	nop
	j	_ir_goto_label30
_ir_goto_label48:
	nop
	li	a0,43
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label31:
	nop
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 292(sp)
	li	s11,45
	sw	s11, 296(sp)
	lw	s11, 292(sp)
	lw	s10, 296(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 300(sp)
	lw	s9, 300(sp)
	bnez	s9,_ir_goto_label51
	j	_ir_goto_label52
_ir_goto_label51:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 304(sp)
	li	s11,43
	sw	s11, 308(sp)
	lw	s11, 304(sp)
	lw	s10, 308(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 312(sp)
	lw	s9, 312(sp)
	bnez	s9,_ir_goto_label53
	j	_ir_goto_label54
_ir_goto_label53:
	li	s9,1
	sw	s9, 316(sp)
	j	_ir_goto_label55
_ir_goto_label54:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 320(sp)
	li	s11,45
	sw	s11, 324(sp)
	lw	s11, 320(sp)
	lw	s10, 324(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 328(sp)
	lw	s9, 328(sp)
	bnez	s9,_ir_goto_label56
	j	_ir_goto_label57
_ir_goto_label56:
	li	s9,1
	sw	s9, 332(sp)
	j	_ir_goto_label58
_ir_goto_label57:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 336(sp)
	li	s11,42
	sw	s11, 340(sp)
	lw	s11, 336(sp)
	lw	s10, 340(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 344(sp)
	lw	s9, 344(sp)
	bnez	s9,_ir_goto_label59
	j	_ir_goto_label60
_ir_goto_label59:
	li	s9,1
	sw	s9, 348(sp)
	j	_ir_goto_label61
_ir_goto_label60:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 352(sp)
	li	s11,47
	sw	s11, 356(sp)
	lw	s11, 352(sp)
	lw	s10, 356(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 360(sp)
	lw	s9, 360(sp)
	bnez	s9,_ir_goto_label62
	j	_ir_goto_label63
_ir_goto_label62:
	li	s9,1
	sw	s9, 364(sp)
	j	_ir_goto_label64
_ir_goto_label63:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 368(sp)
	li	s11,37
	sw	s11, 372(sp)
	lw	s11, 368(sp)
	lw	s10, 372(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 376(sp)
	lw	s9, 376(sp)
	bnez	s9,_ir_goto_label65
	j	_ir_goto_label66
_ir_goto_label65:
	li	s9,1
	sw	s9, 380(sp)
	j	_ir_goto_label67
_ir_goto_label66:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 384(sp)
	li	s11,94
	sw	s11, 388(sp)
	lw	s11, 384(sp)
	lw	s10, 388(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 392(sp)
	lw	s9, 376(sp)
	lw	s10, 392(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 380(sp)
_ir_goto_label67:
	lw	s11, 360(sp)
	lw	s10, 380(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 364(sp)
_ir_goto_label64:
	lw	s9, 344(sp)
	lw	s10, 364(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 348(sp)
_ir_goto_label61:
	lw	s11, 328(sp)
	lw	s10, 348(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 332(sp)
_ir_goto_label58:
	lw	s9, 312(sp)
	lw	s10, 332(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 316(sp)
_ir_goto_label55:
	lw	s11, 316(sp)
	bnez	s11,_ir_goto_label68
	j	_ir_goto_label69
_ir_goto_label68:
	addi	sp,sp,0
	call	find
	addi	sp,sp,0
	sw	a0, 396(sp)
	li	s11,0
	sw	s11, 400(sp)
	lw	s11, 396(sp)
	lw	s10, 400(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 404(sp)
	lw	s9, 404(sp)
	bnez	s9,_ir_goto_label70
	j	_ir_goto_label71
_ir_goto_label70:
	j	_ir_goto_label69
_ir_goto_label71:
	nop
	j	_ir_goto_label51
_ir_goto_label69:
	nop
	li	a0,45
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label52:
	nop
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 408(sp)
	li	s11,42
	sw	s11, 412(sp)
	lw	s11, 408(sp)
	lw	s10, 412(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 416(sp)
	lw	s9, 416(sp)
	bnez	s9,_ir_goto_label72
	j	_ir_goto_label73
_ir_goto_label72:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 420(sp)
	li	s11,42
	sw	s11, 424(sp)
	lw	s11, 420(sp)
	lw	s10, 424(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 428(sp)
	lw	s9, 428(sp)
	bnez	s9,_ir_goto_label74
	j	_ir_goto_label75
_ir_goto_label74:
	li	s9,1
	sw	s9, 432(sp)
	j	_ir_goto_label76
_ir_goto_label75:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 436(sp)
	li	s11,47
	sw	s11, 440(sp)
	lw	s11, 436(sp)
	lw	s10, 440(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 444(sp)
	lw	s9, 444(sp)
	bnez	s9,_ir_goto_label77
	j	_ir_goto_label78
_ir_goto_label77:
	li	s9,1
	sw	s9, 448(sp)
	j	_ir_goto_label79
_ir_goto_label78:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 452(sp)
	li	s11,37
	sw	s11, 456(sp)
	lw	s11, 452(sp)
	lw	s10, 456(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 460(sp)
	lw	s9, 460(sp)
	bnez	s9,_ir_goto_label80
	j	_ir_goto_label81
_ir_goto_label80:
	li	s9,1
	sw	s9, 464(sp)
	j	_ir_goto_label82
_ir_goto_label81:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 468(sp)
	li	s11,94
	sw	s11, 472(sp)
	lw	s11, 468(sp)
	lw	s10, 472(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 476(sp)
	lw	s9, 460(sp)
	lw	s10, 476(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 464(sp)
_ir_goto_label82:
	lw	s11, 444(sp)
	lw	s10, 464(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 448(sp)
_ir_goto_label79:
	lw	s9, 428(sp)
	lw	s10, 448(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 432(sp)
_ir_goto_label76:
	lw	s11, 432(sp)
	bnez	s11,_ir_goto_label83
	j	_ir_goto_label84
_ir_goto_label83:
	addi	sp,sp,0
	call	find
	addi	sp,sp,0
	sw	a0, 480(sp)
	li	s11,0
	sw	s11, 484(sp)
	lw	s11, 480(sp)
	lw	s10, 484(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 488(sp)
	lw	s9, 488(sp)
	bnez	s9,_ir_goto_label85
	j	_ir_goto_label86
_ir_goto_label85:
	j	_ir_goto_label84
_ir_goto_label86:
	nop
	j	_ir_goto_label72
_ir_goto_label84:
	nop
	li	a0,42
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label73:
	nop
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 492(sp)
	li	s11,47
	sw	s11, 496(sp)
	lw	s11, 492(sp)
	lw	s10, 496(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 500(sp)
	lw	s9, 500(sp)
	bnez	s9,_ir_goto_label87
	j	_ir_goto_label88
_ir_goto_label87:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 504(sp)
	li	s11,42
	sw	s11, 508(sp)
	lw	s11, 504(sp)
	lw	s10, 508(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 512(sp)
	lw	s9, 512(sp)
	bnez	s9,_ir_goto_label89
	j	_ir_goto_label90
_ir_goto_label89:
	li	s9,1
	sw	s9, 516(sp)
	j	_ir_goto_label91
_ir_goto_label90:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 520(sp)
	li	s11,47
	sw	s11, 524(sp)
	lw	s11, 520(sp)
	lw	s10, 524(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 528(sp)
	lw	s9, 528(sp)
	bnez	s9,_ir_goto_label92
	j	_ir_goto_label93
_ir_goto_label92:
	li	s9,1
	sw	s9, 532(sp)
	j	_ir_goto_label94
_ir_goto_label93:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 536(sp)
	li	s11,37
	sw	s11, 540(sp)
	lw	s11, 536(sp)
	lw	s10, 540(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 544(sp)
	lw	s9, 544(sp)
	bnez	s9,_ir_goto_label95
	j	_ir_goto_label96
_ir_goto_label95:
	li	s9,1
	sw	s9, 548(sp)
	j	_ir_goto_label97
_ir_goto_label96:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 552(sp)
	li	s11,94
	sw	s11, 556(sp)
	lw	s11, 552(sp)
	lw	s10, 556(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 560(sp)
	lw	s9, 544(sp)
	lw	s10, 560(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 548(sp)
_ir_goto_label97:
	lw	s11, 528(sp)
	lw	s10, 548(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 532(sp)
_ir_goto_label94:
	lw	s9, 512(sp)
	lw	s10, 532(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 516(sp)
_ir_goto_label91:
	lw	s11, 516(sp)
	bnez	s11,_ir_goto_label98
	j	_ir_goto_label99
_ir_goto_label98:
	addi	sp,sp,0
	call	find
	addi	sp,sp,0
	sw	a0, 564(sp)
	li	s11,0
	sw	s11, 568(sp)
	lw	s11, 564(sp)
	lw	s10, 568(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 572(sp)
	lw	s9, 572(sp)
	bnez	s9,_ir_goto_label100
	j	_ir_goto_label101
_ir_goto_label100:
	j	_ir_goto_label99
_ir_goto_label101:
	nop
	j	_ir_goto_label87
_ir_goto_label99:
	nop
	li	a0,47
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label88:
	nop
	la	s9, get_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 576(sp)
	li	s11,37
	sw	s11, 580(sp)
	lw	s11, 576(sp)
	lw	s10, 580(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 584(sp)
	lw	s9, 584(sp)
	bnez	s9,_ir_goto_label102
	j	_ir_goto_label103
_ir_goto_label102:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 588(sp)
	li	s11,42
	sw	s11, 592(sp)
	lw	s11, 588(sp)
	lw	s10, 592(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 596(sp)
	lw	s9, 596(sp)
	bnez	s9,_ir_goto_label104
	j	_ir_goto_label105
_ir_goto_label104:
	li	s9,1
	sw	s9, 600(sp)
	j	_ir_goto_label106
_ir_goto_label105:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 604(sp)
	li	s11,47
	sw	s11, 608(sp)
	lw	s11, 604(sp)
	lw	s10, 608(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 612(sp)
	lw	s9, 612(sp)
	bnez	s9,_ir_goto_label107
	j	_ir_goto_label108
_ir_goto_label107:
	li	s9,1
	sw	s9, 616(sp)
	j	_ir_goto_label109
_ir_goto_label108:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 620(sp)
	li	s11,37
	sw	s11, 624(sp)
	lw	s11, 620(sp)
	lw	s10, 624(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 628(sp)
	lw	s9, 628(sp)
	bnez	s9,_ir_goto_label110
	j	_ir_goto_label111
_ir_goto_label110:
	li	s9,1
	sw	s9, 632(sp)
	j	_ir_goto_label112
_ir_goto_label111:
	la	s9, chas_block0
	la	s11, chat_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 636(sp)
	li	s11,94
	sw	s11, 640(sp)
	lw	s11, 636(sp)
	lw	s10, 640(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 644(sp)
	lw	s9, 628(sp)
	lw	s10, 644(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 632(sp)
_ir_goto_label112:
	lw	s11, 612(sp)
	lw	s10, 632(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 616(sp)
_ir_goto_label109:
	lw	s9, 596(sp)
	lw	s10, 616(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 600(sp)
_ir_goto_label106:
	lw	s11, 600(sp)
	bnez	s11,_ir_goto_label113
	j	_ir_goto_label114
_ir_goto_label113:
	addi	sp,sp,0
	call	find
	addi	sp,sp,0
	sw	a0, 648(sp)
	li	s11,0
	sw	s11, 652(sp)
	lw	s11, 648(sp)
	lw	s10, 652(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 656(sp)
	lw	s9, 656(sp)
	bnez	s9,_ir_goto_label115
	j	_ir_goto_label116
_ir_goto_label115:
	j	_ir_goto_label114
_ir_goto_label116:
	nop
	j	_ir_goto_label102
_ir_goto_label114:
	nop
	li	a0,37
	addi	sp,sp,0
	call	chapush
	addi	sp,sp,0
_ir_goto_label103:
	nop
	la	s9, get2_block0
	la	s11, ii_block0
	lw	s10, 0(s11)
	li	s11,32
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 660(sp)
	la	s10, ii_block0
	lw	s11, 0(s10)
	lw	s10, 660(sp)
	add	s9,s11,s10
	sw	s9, 664(sp)
	lw	s10, 664(sp)
	mv	s9,s10
	la	s10, ii_block0
	sw	s9, 0(s10)
_ir_goto_label20:
	nop
	li	s9,1
	sw	s9, 668(sp)
	la	s10, i_block0
	lw	s9, 0(s10)
	lw	s10, 668(sp)
	add	s11,s9,s10
	sw	s11, 672(sp)
	lw	s10, 672(sp)
	mv	s11,s10
	la	s10, i_block0
	sw	s11, 0(s10)
	j	_ir_goto_label117
_ir_goto_label17:
	nop
_ir_goto_label120:
	li	s11,0
	sw	s11, 676(sp)
	la	s10, chat_block0
	lw	s11, 0(s10)
	lw	s10, 676(sp)
	slt	s9,s10,s11
	sw	s9, 680(sp)
	lw	s9, 680(sp)
	bnez	s9,_ir_goto_label118
	j	_ir_goto_label119
_ir_goto_label118:
	addi	sp,sp,0
	call	chapop
	addi	sp,sp,0
	sw	a0, 684(sp)
	lw	s10, 684(sp)
	mv	s9,s10
	sw	s9, 688(sp)
	la	s9, get2_block0
	la	s11, ii_block0
	lw	s10, 0(s11)
	li	s11,32
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	sw	s11, 692(sp)
	la	s10, ii_block0
	lw	s11, 0(s10)
	lw	s10, 692(sp)
	add	s9,s11,s10
	sw	s9, 696(sp)
	la	s9, get2_block0
	lw	s10, 696(sp)
	lw	s11, 688(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,2
	sw	s11, 700(sp)
	la	s10, ii_block0
	lw	s11, 0(s10)
	lw	s10, 700(sp)
	add	s9,s11,s10
	sw	s9, 704(sp)
	lw	s10, 704(sp)
	mv	s9,s10
	la	s10, ii_block0
	sw	s9, 0(s10)
	j	_ir_goto_label120
_ir_goto_label119:
	nop
	la	s9, get2_block0
	la	s11, ii_block0
	lw	s10, 0(s11)
	li	s11,64
	slli	s10,s10,2
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,1
	la	s10, i_block0
	sw	s11, 0(s10)
_ir_goto_label158:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 708(sp)
	li	s9,64
	sw	s9, 712(sp)
	lw	s9, 708(sp)
	lw	s10, 712(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	xori	s11,s11,1
	sw	s11, 716(sp)
	lw	s11, 716(sp)
	bnez	s11,_ir_goto_label121
	j	_ir_goto_label122
_ir_goto_label121:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 720(sp)
	li	s9,43
	sw	s9, 724(sp)
	lw	s9, 720(sp)
	lw	s10, 724(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 728(sp)
	lw	s11, 728(sp)
	bnez	s11,_ir_goto_label123
	j	_ir_goto_label124
_ir_goto_label123:
	li	s11,1
	sw	s11, 732(sp)
	j	_ir_goto_label125
_ir_goto_label124:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 736(sp)
	li	s9,45
	sw	s9, 740(sp)
	lw	s9, 736(sp)
	lw	s10, 740(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 744(sp)
	lw	s11, 744(sp)
	bnez	s11,_ir_goto_label126
	j	_ir_goto_label127
_ir_goto_label126:
	li	s11,1
	sw	s11, 748(sp)
	j	_ir_goto_label128
_ir_goto_label127:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 752(sp)
	li	s9,42
	sw	s9, 756(sp)
	lw	s9, 752(sp)
	lw	s10, 756(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 760(sp)
	lw	s11, 760(sp)
	bnez	s11,_ir_goto_label129
	j	_ir_goto_label130
_ir_goto_label129:
	li	s11,1
	sw	s11, 764(sp)
	j	_ir_goto_label131
_ir_goto_label130:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 768(sp)
	li	s9,47
	sw	s9, 772(sp)
	lw	s9, 768(sp)
	lw	s10, 772(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 776(sp)
	lw	s11, 776(sp)
	bnez	s11,_ir_goto_label132
	j	_ir_goto_label133
_ir_goto_label132:
	li	s11,1
	sw	s11, 780(sp)
	j	_ir_goto_label134
_ir_goto_label133:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 784(sp)
	li	s9,37
	sw	s9, 788(sp)
	lw	s9, 784(sp)
	lw	s10, 788(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 792(sp)
	lw	s11, 792(sp)
	bnez	s11,_ir_goto_label135
	j	_ir_goto_label136
_ir_goto_label135:
	li	s11,1
	sw	s11, 796(sp)
	j	_ir_goto_label137
_ir_goto_label136:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 800(sp)
	li	s9,94
	sw	s9, 804(sp)
	lw	s9, 800(sp)
	lw	s10, 804(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 808(sp)
	lw	s11, 792(sp)
	lw	s10, 808(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 796(sp)
_ir_goto_label137:
	lw	s9, 776(sp)
	lw	s10, 796(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 780(sp)
_ir_goto_label134:
	lw	s11, 760(sp)
	lw	s10, 780(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 764(sp)
_ir_goto_label131:
	lw	s9, 744(sp)
	lw	s10, 764(sp)
	sltiu	s11,s9,1
	xori	s11,s11,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s11,s11,s10
	sw	s11, 748(sp)
_ir_goto_label128:
	lw	s11, 728(sp)
	lw	s10, 748(sp)
	sltiu	s9,s11,1
	xori	s9,s9,1
	sltiu	s10,s10,1
	xori	s10,s10,1
	or	s9,s9,s10
	sw	s9, 732(sp)
_ir_goto_label125:
	lw	s9, 732(sp)
	bnez	s9,_ir_goto_label138
	j	_ir_goto_label139
_ir_goto_label138:
	addi	sp,sp,0
	call	intpop
	addi	sp,sp,0
	sw	a0, 812(sp)
	lw	s10, 812(sp)
	mv	s9,s10
	sw	s9, 820(sp)
	addi	sp,sp,0
	call	intpop
	addi	sp,sp,0
	sw	a0, 824(sp)
	lw	s10, 824(sp)
	mv	s9,s10
	sw	s9, 828(sp)
	li	s9,0
	sw	s9, 832(sp)
	la	s9, get2_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 836(sp)
	li	s11,43
	sw	s11, 840(sp)
	lw	s11, 836(sp)
	lw	s10, 840(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 844(sp)
	lw	s9, 844(sp)
	bnez	s9,_ir_goto_label140
	j	_ir_goto_label141
_ir_goto_label140:
	lw	s9, 820(sp)
	lw	s10, 828(sp)
	add	s11,s9,s10
	sw	s11, 848(sp)
	lw	s10, 848(sp)
	mv	s11,s10
	sw	s11, 832(sp)
_ir_goto_label141:
	nop
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 852(sp)
	li	s9,45
	sw	s9, 856(sp)
	lw	s9, 852(sp)
	lw	s10, 856(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 860(sp)
	lw	s11, 860(sp)
	bnez	s11,_ir_goto_label142
	j	_ir_goto_label143
_ir_goto_label142:
	lw	s11, 828(sp)
	lw	s10, 820(sp)
	sub	s9,s11,s10
	sw	s9, 864(sp)
	lw	s10, 864(sp)
	mv	s9,s10
	sw	s9, 832(sp)
_ir_goto_label143:
	nop
	la	s9, get2_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 868(sp)
	li	s11,42
	sw	s11, 872(sp)
	lw	s11, 868(sp)
	lw	s10, 872(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 876(sp)
	lw	s9, 876(sp)
	bnez	s9,_ir_goto_label144
	j	_ir_goto_label145
_ir_goto_label144:
	lw	s9, 820(sp)
	lw	s10, 828(sp)
	mul	s11,s9,s10
	sw	s11, 880(sp)
	lw	s10, 880(sp)
	mv	s11,s10
	sw	s11, 832(sp)
_ir_goto_label145:
	nop
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 884(sp)
	li	s9,47
	sw	s9, 888(sp)
	lw	s9, 884(sp)
	lw	s10, 888(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 892(sp)
	lw	s11, 892(sp)
	bnez	s11,_ir_goto_label146
	j	_ir_goto_label147
_ir_goto_label146:
	lw	s11, 828(sp)
	lw	s10, 820(sp)
	div	s9,s11,s10
	sw	s9, 896(sp)
	lw	s10, 896(sp)
	mv	s9,s10
	sw	s9, 832(sp)
_ir_goto_label147:
	nop
	la	s9, get2_block0
	la	s11, i_block0
	lw	s10, 0(s11)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 900(sp)
	li	s11,37
	sw	s11, 904(sp)
	lw	s11, 900(sp)
	lw	s10, 904(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	sw	s9, 908(sp)
	lw	s9, 908(sp)
	bnez	s9,_ir_goto_label148
	j	_ir_goto_label149
_ir_goto_label148:
	lw	s9, 828(sp)
	lw	s10, 820(sp)
	rem	s11,s9,s10
	sw	s11, 912(sp)
	lw	s10, 912(sp)
	mv	s11,s10
	sw	s11, 832(sp)
_ir_goto_label149:
	nop
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 916(sp)
	li	s9,94
	sw	s9, 920(sp)
	lw	s9, 916(sp)
	lw	s10, 920(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	sw	s11, 924(sp)
	lw	s11, 924(sp)
	bnez	s11,_ir_goto_label150
	j	_ir_goto_label151
_ir_goto_label150:
	lw	s11, 828(sp)
	mv	a0,s11
	lw	s11, 820(sp)
	mv	a1,s11
	addi	sp,sp,0
	call	power
	addi	sp,sp,0
	sw	a0, 928(sp)
	lw	s10, 928(sp)
	mv	s11,s10
	sw	s11, 832(sp)
_ir_goto_label151:
	nop
	lw	s11, 832(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	intpush
	addi	sp,sp,0
	j	_ir_goto_label152
_ir_goto_label139:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 936(sp)
	li	s9,32
	sw	s9, 940(sp)
	lw	s9, 936(sp)
	lw	s10, 940(sp)
	xor	s11,s9,s10
	sltiu	s11,s11,1
	xori	s11,s11,1
	sw	s11, 944(sp)
	lw	s11, 944(sp)
	bnez	s11,_ir_goto_label153
	j	_ir_goto_label154
_ir_goto_label153:
	la	s11, get2_block0
	la	s9, i_block0
	lw	s10, 0(s9)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 948(sp)
	li	s9,48
	sw	s9, 952(sp)
	lw	s9, 948(sp)
	lw	s10, 952(sp)
	sub	s11,s9,s10
	sw	s11, 956(sp)
	lw	s11, 956(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	intpush
	addi	sp,sp,0
	li	s11,1
	la	s10, ii_block0
	sw	s11, 0(s10)
_ir_goto_label157:
	la	s10, i_block0
	lw	s11, 0(s10)
	la	s9, ii_block0
	lw	s10, 0(s9)
	add	s9,s11,s10
	sw	s9, 960(sp)
	la	s9, get2_block0
	lw	s10, 960(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 964(sp)
	li	s11,32
	sw	s11, 968(sp)
	lw	s11, 964(sp)
	lw	s10, 968(sp)
	xor	s9,s11,s10
	sltiu	s9,s9,1
	xori	s9,s9,1
	sw	s9, 972(sp)
	lw	s9, 972(sp)
	bnez	s9,_ir_goto_label155
	j	_ir_goto_label156
_ir_goto_label155:
	la	s10, i_block0
	lw	s9, 0(s10)
	la	s11, ii_block0
	lw	s10, 0(s11)
	add	s11,s9,s10
	sw	s11, 976(sp)
	la	s11, get2_block0
	lw	s10, 976(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 980(sp)
	li	s9,48
	sw	s9, 984(sp)
	lw	s9, 980(sp)
	lw	s10, 984(sp)
	sub	s11,s9,s10
	sw	s11, 988(sp)
	lw	s11, 988(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	intadd
	addi	sp,sp,0
	li	s11,1
	sw	s11, 992(sp)
	la	s10, ii_block0
	lw	s11, 0(s10)
	lw	s10, 992(sp)
	add	s9,s11,s10
	sw	s9, 996(sp)
	lw	s10, 996(sp)
	mv	s9,s10
	la	s10, ii_block0
	sw	s9, 0(s10)
	j	_ir_goto_label157
_ir_goto_label156:
	nop
	la	s10, i_block0
	lw	s9, 0(s10)
	la	s11, ii_block0
	lw	s10, 0(s11)
	add	s11,s9,s10
	sw	s11, 1000(sp)
	li	s11,1
	sw	s11, 1004(sp)
	lw	s11, 1000(sp)
	lw	s10, 1004(sp)
	sub	s9,s11,s10
	sw	s9, 1008(sp)
	lw	s10, 1008(sp)
	mv	s9,s10
	la	s10, i_block0
	sw	s9, 0(s10)
_ir_goto_label154:
	nop
_ir_goto_label152:
	nop
	li	s9,1
	sw	s9, 1012(sp)
	la	s10, i_block0
	lw	s9, 0(s10)
	lw	s10, 1012(sp)
	add	s11,s9,s10
	sw	s11, 1016(sp)
	lw	s10, 1016(sp)
	mv	s11,s10
	la	s10, i_block0
	sw	s11, 0(s10)
	j	_ir_goto_label158
_ir_goto_label122:
	nop
	la	s11, ints_block0
	li	s10,4
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 1020(sp)
	lw	s9, 1020(sp)
	mv	a0,s9
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
	addi	sp,sp,1024
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
	addi	sp,sp,1024
	ret
	.size	main, .-main
