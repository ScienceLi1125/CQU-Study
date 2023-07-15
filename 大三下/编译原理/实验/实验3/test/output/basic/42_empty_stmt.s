	.option nopic
	.data
	.text
	.globl	main
	.type	main, @function
main:
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
	li	s11,10
	sw	s11, 52(sp)
	li	s11,2
	sw	s11, 56(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	mul	s9,s11,s10
	sw	s9, 60(sp)
	li	s9,1
	sw	s9, 64(sp)
	lw	s9, 60(sp)
	lw	s10, 64(sp)
	add	s11,s9,s10
	sw	s11, 68(sp)
	lw	s11, 68(sp)
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
	addi	sp,sp,72
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
	addi	sp,sp,72
	ret
	.size	main, .-main
