	.option nopic
	.data
	.text
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-192
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
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	sub	s9,s11,s10
	sw	s9, 88(sp)
	li	s9,3
	sw	s9, 92(sp)
	lw	s9, 60(sp)
	lw	s10, 92(sp)
	add	s11,s9,s10
	sw	s11, 96(sp)
	li	s11,0
	sw	s11, 100(sp)
	lw	s11, 100(sp)
	lw	s10, 96(sp)
	sub	s9,s11,s10
	sw	s9, 104(sp)
	li	s9,2
	sw	s9, 108(sp)
	lw	s9, 104(sp)
	lw	s10, 108(sp)
	rem	s11,s9,s10
	sw	s11, 112(sp)
	lw	s11, 84(sp)
	lw	s10, 88(sp)
	add	s9,s11,s10
	sw	s9, 116(sp)
	lw	s9, 116(sp)
	lw	s10, 112(sp)
	sub	s11,s9,s10
	sw	s11, 120(sp)
	lw	s10, 120(sp)
	mv	s11,s10
	sw	s11, 68(sp)
	lw	s11, 68(sp)
	mv	a0,s11
	addi	sp,sp,0
	call	putint
	addi	sp,sp,0
	li	s11,2
	sw	s11, 124(sp)
	lw	s11, 64(sp)
	lw	s10, 124(sp)
	rem	s9,s11,s10
	sw	s9, 128(sp)
	li	s9,67
	sw	s9, 132(sp)
	lw	s9, 128(sp)
	lw	s10, 132(sp)
	add	s11,s9,s10
	sw	s11, 136(sp)
	lw	s11, 52(sp)
	lw	s10, 56(sp)
	sub	s9,s11,s10
	sw	s9, 140(sp)
	li	s9,0
	sw	s9, 144(sp)
	lw	s9, 144(sp)
	lw	s10, 140(sp)
	sub	s11,s9,s10
	sw	s11, 148(sp)
	li	s11,2
	sw	s11, 152(sp)
	lw	s11, 60(sp)
	lw	s10, 152(sp)
	add	s9,s11,s10
	sw	s9, 156(sp)
	li	s9,2
	sw	s9, 160(sp)
	lw	s9, 156(sp)
	lw	s10, 160(sp)
	rem	s11,s9,s10
	sw	s11, 164(sp)
	li	s11,0
	sw	s11, 168(sp)
	lw	s11, 168(sp)
	lw	s10, 164(sp)
	sub	s9,s11,s10
	sw	s9, 172(sp)
	lw	s9, 136(sp)
	lw	s10, 148(sp)
	add	s11,s9,s10
	sw	s11, 176(sp)
	lw	s11, 176(sp)
	lw	s10, 172(sp)
	sub	s9,s11,s10
	sw	s9, 180(sp)
	lw	s10, 180(sp)
	mv	s9,s10
	sw	s9, 68(sp)
	li	s9,3
	sw	s9, 184(sp)
	lw	s9, 68(sp)
	lw	s10, 184(sp)
	add	s11,s9,s10
	sw	s11, 188(sp)
	lw	s10, 188(sp)
	mv	s11,s10
	sw	s11, 68(sp)
	lw	s11, 68(sp)
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
	addi	sp,sp,192
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
	addi	sp,sp,192
	ret
	.size	main, .-main
