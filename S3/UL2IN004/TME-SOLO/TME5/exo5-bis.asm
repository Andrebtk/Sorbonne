.data
	n: .word 0xFEDCBA98		# @ <- n
	
	# 123 -> 6
	# -1 -> 32
	# 0xFEDCBA98 -> 20

.text
	lui $16, 0x1001		# $16 <- @
	ori $8, $0, 0		# $8(cpt) <- 0
	ori $9, $0, 0		# $9(i) <- 0
	lw $17, 0($16)		# $17 <- n
	
	loop:
		# Fin de boucle: i >= 32
		slti $10, $9, 32		# $10=1 si i<32, 0 sinon (i>=32) 
		beq $10, $0, end_loop
		
		andi $11, $17, 0x1		# $11 <- n & 0x1
		
		# Else: $11 == 0
		beq $11, $0, else
		addiu $8, $8, 1			# cpt+=1
		
	else:
		srl $17, $17, 1			# n <- n >> 1
		addiu $9, $9, 1			# i+=1
		
		j loop 
		
	
end_loop:
	
	# Affichage $8(cpt)
	ori $2, $0, 1
	or $4, $0, $8
	syscall
	
	# Exit
	ori $2, $0, 10
	syscall