.data 
	p: .word 1		# 0x10010000
	q: .word 10		# 0x10010000
.text	
	lui $16, 0x1001		# $16 <- data
	lw $8, 0($16)		# $8 <- p
	lw $9, 4($16)		# $9 <- q
	xor $10, $10, $10	# $10 <- 0 (sum_val)
	
	loop:
		# fin de boucle: q < p
		slt $11, $9, $8			# $11=1 si q<p, 0 sinon
		bne $11, $0, end_loop
		
		addu $10, $10, $8		# $10 <- $10 + q
		addiu $8, $8, 1			# $8 <- p + 1
		j loop

end_loop:
	
	# Affiche $10 (sum_val)
	ori $2, $0, 1
	or $4, $0, $10
	syscall
	
	# Fin de programme
	ori $2, $0, 10
	syscall