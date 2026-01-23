.data
	tab: .word 4, 23, 12, 3, 8, 1	# @ -> 0x10010000
		
		.align 2
	s: 	.space 4		# @ + 4*6 = @ + 24
	 
		.align 2
	p: 	.space 4		# ((@ + 24) + 4)
	
.text
	lui $16, 0x1001			# @ Data segment
	
	lbu $17, 12($16)		# $17 <- tab[3]
	sb $17, 24($16)			# s <- $17
	
	lbu $18, 16($16)		# $18 <- tab[4]
	sb $18, 28($16)			# p <- $18
	
	addi $19, $17, 1		# $19 <- s + 1
	add $20, $17, $18 		# $20 <- s + p
	
	sb $19, 0($16)			# tab[0] <- $19 (s + 1)
	sb $20, 4($16)			# tab[1] <- $20 (s + p)  			
	
	lbu $21, 20($16)		# $21 <- tab[5]
	sb $21, 8($16)
	
	ori $2, $0, 10
	syscall				# Fin de program