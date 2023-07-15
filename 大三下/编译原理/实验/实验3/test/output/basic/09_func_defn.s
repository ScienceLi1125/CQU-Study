	.option nopic
	.data
	.globl	a_block0
	.type	a_block0, @object
	.size	a_block0, 4
	.align	4
a_block0:
	.word	0
	.text
	.globl	func
	.type	func, @function
func:
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
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	sub	s9,s11,s10
	sw	s9, 60(sp)
	lw	s10, 60(sp)
	mv	s9,s10
	sw	s9, 52(sp)
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
	addi	sp,sp,64
	ret
	.size	func, .-func
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
	li	s11,10
	la	s10, a_block0
	sw	s11, 0(s10)
	la	s10, a_block0
	lw	s11, 0(s10)
	mv	a0,s11
	addi	sp,sp,0
	call	func
	addi	sp,sp,0
	sw	a0, 56(sp)
	lw	s10, 56(sp)
	mv	s11,s10
	sw	s11, 52(sp)
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
