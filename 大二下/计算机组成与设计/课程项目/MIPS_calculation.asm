#主函数流程：
	#读入浮点数和运算码 -> 解析符号、指数、尾数以及带偏阶指数 -> 根据运算功能码跳转到运算功能 -> 输出不同进制表示的结果
.data		#数据段（存放于内存中）
#数据声明，声明代码中使用的变量名：
	num1:		.space 20		#0($s5)：num1；4($s5)：符号位；8($s5)：指数；12($s5)：尾数；16($s5)：偏阶
	num2:		.space 20		#0($s6)：num2；4($s6)：符号位；8($s6)：指数；12($s6)：尾数；16($s6)：偏阶
	result:		.space 16		#0($s7)：二进制小数结果；4($s7)：指数；8($s7)：符号位；12($s7)：IEEE754结果；	
	
	Tips1:		.asciiz "Please input the first float:\0"
	Tips2:		.asciiz "Please input the second float:\0"
	Tips3:     	.asciiz "Please choose one function: 0 for exit, 1 for add, 2 for sub: \0"
	Tips4:		.asciiz "Sorry, your function number is out of index! Please input right function number between 0 and 2. \n"
	Tips5:		.asciiz "Exit\0"
	Overflow1:	.asciiz "Up Overflow Excption!\n"
	Overflow2:	.asciiz "Down Overflow Excption!\n"
	Precision:	.asciiz "Precision loss!\n"
	Ansb:		.asciiz	"The binary result of calculation is:\0"
	Ansh:		.asciiz"The hexadecimal result of calculation is:\0"
	Ansd:		.asciiz	"The decimal result of calculation is:\0"
	NewLine:   	.asciiz "\n"
	
.text		#代码段
	main:	#开始执行
		#将num1、num2的首地址从内存写入寄存器
		la  	$s5, 	num1			#将num1的首地址保存到$s5寄存器
	   	la  	$s6,	num2			#将num2的首地址保存到$s6寄存器
	   	#跳转到输入函数，接收浮点数num1、num2并解析其符号、指数、尾数和带偏阶指数
	   	jal Input_funct				#jal先将当前PC放入$ra再跳转
		#输入计算功能（0退出、1加法、2减法）
		la	$a0,	Tips3
		li	$v0,	4
		syscall					#打印"Please choose one function: 0 for exit, 1 for add, 2 for sub: \0"
		li	$v0,	5
		syscall					#调用系统$v0=5读取输入的整数值并存入$v0
		#此时$v0存储计算功能码，分别比较0、1、2用以跳转至相应函数，若不在该区间则出现异常
		li	$t0,	1
		beq	$v0,	$t0,	add_funct       #加法
		li	$t0,	2                   
		beq	$v0,	$t0,	sub_funct        #减法                
		li	$t0,	0
		beq	$v0,	$t0,	exit_funct  	#退出
		bne	$v0,	$t0,	default_funct	#输入的不是0-4
	
#将输入浮点数存入相应寄存器并截取符号、指数、尾数和带偏阶指数
Input_funct:
	#打印"Please input the first float:\0"
	la $a0,Tips1
	li $v0,4
	syscall
	#系统调用读取输入的浮点数，存入$f0
	li $v0,6
	syscall
	#将$f0中的数据存入$s1并放入内存
	mfc1 $s1,$f0
	sw $s1,0($s5)
       	#打印"Please input the second float:\0"
	la $a0,Tips2
	li $v0,4
	syscall
 	#系统调用读取输入的浮点数，存入$f0
	li $v0,6
	syscall
	#将$f0中的数据存入$s2并放入内存
	mfc1 $s2,$f0
	sw $s2,0($s6)
	#将num1符号位存入4($s5)
	andi $t1,$s1,0x80000000		#0x80000000为16进制数，二进制为32'b1000_...._0000，和$s1中的num1按位与得到num1符号位（31位）
	srl  $t1,$t1,31              	#右移31位对齐
	sw   $t1,4($s5)
	#将num2符号位存入4($s6)
	andi $t1,$s2,0x80000000    
	srl  $t1,$t1,31
	sw   $t1,4($s6)
	#将num1指数存入8($s5)
	andi $t1,$s1,0x7f800000		#二进制为32'b0111_1111_1000_..._0000，和$s1中的num1按位与得到num1指数（23~30位）
	srl  $t2,$t1,23              	#右对齐
	sw   $t2,8($s5)
	#将num2指数存入8($s6)
	andi $t1,$s2,0x7f800000      
	srl  $t3,$t1,23
	sw   $t3,8($s6)
	#将num1尾数存入12($s5)
	andi  $t1,$s1,0x007fffff     	#二进制为32'b0000_..._0111_1111_..._1111，和$s1中的num1按位与得到num1尾数（0~22位）
	sw    $t1,12($s5)
	#将num2尾数存入12($s6)
	andi $t1,$s2,0x007fffff
	sw   $t1,12($s6)
	#将num1带偏阶指数存入16($s5)
	addi $t4,$0,0x0000007f 		#偏阶127
	sub  $t1,$t2,$t4             	#指数-偏阶得到带偏阶指数
	sw   $t1,16($s5)
	#将num2带偏阶指数存入16($s6)
	sub  $t1,$t3,$t4
	sw   $t1,16($s6)
	#跳转回调用函数前的PC（保存在指令寄存器$ra中）
	jr $ra

#加法流程：取num1、num2的符号位、阶、尾数->补全尾数的整数位->对阶->执行加法运算->输出
#add_funct->getAdd->(Align_exp)->beginAdd->Add_Same_sign/Add_Diff_sign->NumSRL->showAns
add_funct:
	jal 	getAdd
	jal	binary
	jal	hex
	j 	main				#本次执行完毕，跳回主函数开头
getAdd:
	#取num1和num2的符号位
	lw	$s0,	4($s5) 			#$s0是num1的符号位，$s1是num2的符号位
	lw	$s1,	4($s6)
	#取num1和num2的阶
	lw	$s2,	8($s5) 			#$s2是num1的阶，$s3是num2的阶
	lw	$s3,	8($s6)
	#取num1和num2的尾数
	lw	$s4,	12($s5)			#$s4是num1的尾数，$s5是num2的尾数
	lw	$s5,	12($s6)
	#补全尾数的整数位1
	ori	$s4,	$s4,	0x00800000	#将整数位1补全
	ori	$s5,	$s5,	0x00800000
	#对阶
	sub	$t0,	$s2,	$s3 		#比较num1和num2的阶数（指数）大小
	bltz	$t0,	Align_exp1 		#$t0小于0，则表明num1的阶小于num2，需将num1右移对阶
	bgtz	$t0,	Align_exp2 		#$t0大于0，需将num2右移对阶
	beqz	$t0,	beginAdd		#两个数阶相同，则直接相加
#对阶：若两个加数阶数不同，进入相加前需要先对阶。将阶数小的向阶数大的对齐，因为反之会降低阶数大的数的精度
#对阶过程采用递归，阶数小的右移1位再判断回到Align_exp函数开头或开始相加
Align_exp1:	#num1的阶小于num2的阶，num1阶数+1，尾数右移
	addi	$s2,	$s2,	1		#num1阶数+1
	srl	$s4,	$s4,	1		#num1尾数右移
	sub	$t0,	$s2,	$s3 		#循环判断
	bltz	$t0,	Align_exp1		#branch if less than zero
	beqz	$t0,	beginAdd		#branch if equal zero跳到相加
Align_exp2:	#num1的阶大于num2的阶，num2阶数+1，尾数右移
	addi	$s3,	$s3,	1
	srl	$s5,	$s5,	1
	sub	$t0,	$s2,	$s3
	bgtz	$t0,	Align_exp2
	beqz	$t0,	beginAdd
#此时num1、num2阶数相同，判断符号后才能相加
beginAdd:
	xor	$t1,	$s0,	$s1 		#按位异或判断num1、num2符号是否相同（相同则$t1存32'b0，不同存32'b1）
	beq	$t1,	$zero,	Add_Same_sign 	#num1、num2符号相同，则直接加(Add_Same_sign)
	j	Add_Diff_sign 			#num1、num2符号不同，跳转到(Add_Diff_sign)
#num1、num2符号相同相加
Add_Same_sign:
	add	$t2,	$s4,	$s5		#尾数相加后的结果即为输出的尾数，但需要先判断是否溢出
	sge	$t3,	$t2,	0x01000000	#set if greater or equal 判断上溢
	#因为两个无符号23bit二进制数相加，如果结果的第24位为1，则发生了上溢，需要右移尾数、阶数+1
	bgtz	$t3,	NumSRL			#上溢则尾数右移 
	j	showAns				#无溢出就跳转到结果输出部分
#num1、num2符号相同相加后上溢出，需要尾数右移，阶数+1
NumSRL:
	srl	$t2,	$t2,	1		#尾数右移
	addi	$s2,	$s2,	1		#阶数+1
	j	showAns				#此时阶数、尾数正确，可以输出
#num1、num2符号不同相加
Add_Diff_sign:
	sub	$t2,	$s4,	$s5		#符号不同的数相加相当于先相减再加符号，但可能出现尾数过大（上溢）或过小（下溢）的情况
	bgtz	$t2,	Add_Diff_sign1		#如果num1的尾数比num2大，则跳转至Add_Diff_sign1（结果与num1同号）
	bltz	$t2,	Add_Diff_sign2		#如果num1的尾数比num2小，则跳转至Add_Diff_sign2（结果与num2同号）
	j	show0				#如果它们的绝对值相等，则结果为0，可以跳转到特殊结果输出
#num1、num2符号不同相加，num1尾数比num2大，输出前需要先判断是否上溢或下溢
Add_Diff_sign1:
	blt	$t2,	0x00800000,	Add_Diff_sign11		#尾数太小，则需左移，将其规格化
	bge	$t2,	0x01000000,	Add_Diff_sign12		#如果尾数没有过小，那么就需要判断上溢
	j	showAns						#既不上溢也不下溢的结果过可以直接输出
#num1、num2符号不同相加，num1尾数比num2大，结果尾数太小
Add_Diff_sign11:
	sll	$t2,	$t2,	1				#左移扩大尾数
	subi	$s2,	$s2,	1				#阶数-1
	blt	$t2,	0x00800000,	Add_Diff_sign11		#循环扩大尾数
	j	showAns
#num1、num2符号不同相加，num1尾数比num2大，结果尾数太大
Add_Diff_sign12:
	srl	$t2,	$t2,	1				#左移缩小尾数
	addi	$s2,	$s2,	1				#阶数+1
	bge	$t2,	0x01000000,	Add_Diff_sign12
	j	showAns
#num1、num2符号不同相加，num1尾数比num2小
Add_Diff_sign2:
	sub	$t2,	$s5,	$s4				#将$t2中数化为正
	xori    $s0     $s0     0x00000001			#结果与num2同号
	j	Add_Diff_sign1					#模块复用

#减法可以复用加法模块（将num2符号取反即可）
sub_funct:
	lw 	$t1,	4($s6)					#num2的符号位存入$t1
	xori 	$t1,	$t1,	1				#将num2符号位按位异或（取反）
	sw 	$t1,	4($s6)
	jal 	getAdd
	jal	binary
	jal	hex
	j main
#op输入0时退出
exit_funct:
	la  	$a0, 	Tips5     
	li  	$v0, 	4           
	syscall
	li 	$v0,	10					#结束程序
	syscall
#op不符合规范时回到main开头重新输入
default_funct:
	la $a0,Tips4
	li $v0,4
	syscall
	j main

#打印不同进制的结果
showAns:
	#打印十进制结果
	li	$v0,	4
	la	$a0,	Ansd
	syscall
	#判断是否下溢
	#单精度浮点数只有8位指数位（含有偏阶）
	#若小于0则原指数小于-128，即结果下溢；
	#若大于255则原指数大于127，即结果上溢出（精度原因，无法通过偏移解决）
	blt 	$s3,	0,	downOverflow	#下溢，跳转到downOverflow打印"Down Overflow Excption!"
	#判断是上溢
	bgt	$s2,	255,	upOverflow	#上溢，跳转到upOverflow打印"Up Overflow Excption!"
	#将结果还原回31位数据
	sll	$s0,	$s0,	31		#前面的处理已经将结果的符号位存入$s0，直接左移至最高位
	sll	$s2,	$s2,	23		#将指数位移动至相应位置
	sll	$t2,	$t2,	9		#$t2中存放了输出的尾数，为防止尾数23位，采用先左移再右移的方式只留下0~22位的数值
	srl	$t2,	$t2,	9
	add	$s2,	$s2,	$t2		#符号位+指数+尾数=结果
	add	$s0,	$s0,	$s2
	mtc1    $s0,	$f12		
	#输出
	li 	$v0,	2									
	syscall 
	li	$v0,	4
	la	$a0,	NewLine
	syscall
	jr $ra
#最终结果下溢
downOverflow:
	la 	$a0,	Overflow2
	li	$v0,	4
	syscall					#打印"Down Overflow Excption!"
	jr $ra
#最终结果上溢
upOverflow:
	la 	$a0,	Overflow1
	li	$v0,	4
	syscall					#打印"Up Overflow Excption!"
	jr $ra

# 转化成二进制
binary:
	li	$v0,	4
	la	$a0,	Ansb
	syscall					#打印"The binary result of calculation is:"
	addu	$t5,	$s0,	$0		#$s0中存放的IEEE754标准的计算结果
	add	$t6,	$t5,	$0
	addi	$t7,	$0,	32
	addi	$t8,	$t0,	0x80000000	#判断结果指数的正负
	addi	$t9,	$0,	0
binary_transfer:				#执行完binary顺序执行binary_transfer
	#$t6:IEEE754标准的计算结果  $t7:32'b0000_..._0100_0000  $t8:结果的指数正负
	subi	$t7,	$t7,	1
	and	$t9,	$t6,	$t8
	srl	$t8,	$t8,	1
	srlv	$t9,	$t9,	$t7
	add	$a0,	$t9,	$0
	li	$v0,	1
	syscall
	beq	$t7,	$t0,	back
	j	binary_transfer
#转化成十六进制（用4位二进制转1位十六进制即可）
hex:
	li	$v0,	4
	la	$a0,	Ansh
	syscall
	addi	$t7,	$0,	8
	add	$t6,	$t5,	$0
	add	$t9,	$t5,	$0
hex_transfer:
	beq	$t7,	$0,	back
	subi	$t7,	$t7,	1
	srl	$t9,	$t6,	28
	sll	$t6,	$t6,	4
	bgt	$t9,	9,	getAscii
	li	$v0,	1
	addi	$a0,	$t9,	0
	syscall
	j	hex_transfer
#转变为ascii码
getAscii:
	addi	$t9,	$t9,	55
	li	$v0,	11
	add	$a0,	$t9,	$0
	syscall
	j	hex_transfer
#计算结果为0的输出
show0:
	mtc1    $zero,	$f12	
	li 	$v0,	2     
	syscall
	jr $ra
#转化为指定进制输出后回到调用函数前的指令
back:				
	la    	$a0,	NewLine		
	li    	$v0,	4
	syscall
	jr $ra
