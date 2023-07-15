	.option nopic
	.data
	.text
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-168
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
	addi	s11,sp,-32
	sw	s11, 52(sp)
	lw	s11, 52(sp)
	li	s9,0
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,0
	li	s10,4
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,0
	li	s10,8
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,0
	li	s10,12
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,0
	li	s10,16
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,0
	li	s10,20
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 52(sp)
	li	s9,0
	li	s10,24
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 52(sp)
	li	s11,0
	li	s10,28
	add	s9,s9,s10
	sw	s11,0(s9)
	addi	s11,sp,-64
	sw	s11, 56(sp)
	lw	s11, 56(sp)
	li	s9,1
	li	s10,0
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 56(sp)
	li	s11,2
	li	s10,4
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 56(sp)
	li	s9,3
	li	s10,8
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 56(sp)
	li	s11,4
	li	s10,12
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 56(sp)
	li	s9,5
	li	s10,16
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 56(sp)
	li	s11,6
	li	s10,20
	add	s9,s9,s10
	sw	s11,0(s9)
	lw	s11, 56(sp)
	li	s9,7
	li	s10,24
	add	s11,s11,s10
	sw	s9,0(s11)
	lw	s9, 56(sp)
	li	s11,8
	li	s10,28
	add	s9,s9,s10
	sw	s11,0(s9)
	li	s11,3
	sw	s11, 60(sp)
	li	s11,1
	sw	s11, 64(sp)
	li	s11,2
	sw	s11, 68(sp)
	lw	s11, 60(sp)
	lw	s10, 68(sp)
	mul	s9,s11,s10
	sw	s9, 72(sp)
	lw	s9, 72(sp)
	lw	s10, 64(sp)
	add	s11,s9,s10
	sw	s11, 76(sp)
	lw	s11, 56(sp)
	lw	s10, 76(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 80(sp)
	li	s9,0
	sw	s9, 84(sp)
	li	s9,0
	sw	s9, 88(sp)
	li	s9,2
	sw	s9, 92(sp)
	lw	s9, 84(sp)
	lw	s10, 92(sp)
	mul	s11,s9,s10
	sw	s11, 96(sp)
	lw	s11, 96(sp)
	lw	s10, 88(sp)
	add	s9,s11,s10
	sw	s9, 100(sp)
	lw	s9, 56(sp)
	lw	s10, 100(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 104(sp)
	li	s11,0
	sw	s11, 108(sp)
	li	s11,1
	sw	s11, 112(sp)
	li	s11,2
	sw	s11, 116(sp)
	lw	s11, 108(sp)
	lw	s10, 116(sp)
	mul	s9,s11,s10
	sw	s9, 120(sp)
	lw	s9, 120(sp)
	lw	s10, 112(sp)
	add	s11,s9,s10
	sw	s11, 124(sp)
	lw	s11, 56(sp)
	lw	s10, 124(sp)
	slli	s10,s10,2
	add	s11,s11,s10
	lw	s9,0(s11)
	sw	s9, 128(sp)
	li	s9,2
	sw	s9, 132(sp)
	li	s9,0
	sw	s9, 136(sp)
	li	s9,2
	sw	s9, 140(sp)
	lw	s9, 132(sp)
	lw	s10, 140(sp)
	mul	s11,s9,s10
	sw	s11, 144(sp)
	lw	s11, 144(sp)
	lw	s10, 136(sp)
	add	s9,s11,s10
	sw	s9, 148(sp)
	lw	s9, 56(sp)
	lw	s10, 148(sp)
	slli	s10,s10,2
	add	s9,s9,s10
	lw	s11,0(s9)
	sw	s11, 152(sp)
	lw	s11, 80(sp)
	lw	s10, 104(sp)
	add	s9,s11,s10
	sw	s9, 156(sp)
	lw	s9, 156(sp)
	lw	s10, 128(sp)
	add	s11,s9,s10
	sw	s11, 160(sp)
	lw	s11, 160(sp)
	lw	s10, 152(sp)
	add	s9,s11,s10
	sw	s9, 164(sp)
	lw	s9, 164(sp)
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
	addi	sp,sp,168
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
	addi	sp,sp,168
	ret
	.size	main, .-main
