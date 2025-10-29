.data	
		.align 2
	p: 	.space 4		# 0x10010000
	
		.align 2
	q: 	.space 4		# 0x10010004

.text	
	lui $16, 0x1001
	lw $19, 0($16)		# $19 <- p
	lw $20, 4($16)		# $20 <- q
	xor $11, $11, $11 	# $11 <- 0
	
	ori $2, $0, 5
	syscall 		# $2 <- entier lu
	sw $2, 0($16)		# p <- entier lu($2)
	or $19, $0, $2		# $19 <- $2
	
	
	ori $2, $0, 5
	syscall 		# $2 <- entier lu
	sw $2, 4($16)		# q <- entier lu($2)
	or $20, $0, $2		# $20 <- $2
	
	or $10, $0, $19		# n <- p
	
loop:	
		
	slt $12, $20, $10	# $12 <- q < n
	bne $12, $0, end	# fin de boucle
	
	addu $11, $11, $10	# sum(n)
	addiu $10, $10, 1	# n++
	j loop
	

end:
	ori $2, $0, 1
	or $4, $0, $11
	syscall
	
	ori $2, $0, 10
	syscall			# Fin de programme
