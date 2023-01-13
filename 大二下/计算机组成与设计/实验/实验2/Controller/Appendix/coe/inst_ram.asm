addi $2, $0, 5 		# initialize $2=5 		0  20020005
add $5, $5, $4 		# $5 = 4 + 7 = 11 		14 00a42820
lw $2, 80($0) 		# $2 = [80] = 7 		3c 8c020050
sw $2, 84($0)		# write adr 84=7 		4c ac020054
beq $5, $7, end 	# shouldn't be taken 	18 10a7000c
j end 				# should be taken 		40 08000013