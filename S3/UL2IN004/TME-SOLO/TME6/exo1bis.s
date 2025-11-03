.data

	chaine: .space 11			# @ = 0x10010000

.text
	# Prologue
	# 0($29)=i, 4($29)=nb, 8($29)=r, 12($29)=nbzero
	addiu $29, $29, -16			# 4 entier
	
	# Corp
	
	lui $16, 0x1001				# $16 <- @
	
	# scanf("%d", &nb);
	ori $2,$0, 5
	syscall 
	or $9, $0, $2				# $9(nb) <- (input)
	
	# chaine[10] = 0;
	sb $0, 10($16)				# $0 -> chaine[10]
	
	# i = 9
	ori $8, $0, 9				# $8(i) <- 9
	ori $12, $0, 10				# $12 <- 10
	
	loop:
		# Fin de boucle: i < 0
		bltz $8, end_loop
		
		# r = nb % 10;
		div $9, $12			# LO <- (nb / 10)| HI <- nb % 10
		mfhi $10			# $10(r) <- HI
		
		# nb = nb / 10;
		mflo $9				# $9(nb) <- HI
		
		# chaine[i] = r + 0x30;
		ori $13, $0, 0x30		# $13 <- 0x30
		addu $13, $13, $10		# $13 <- $13 + $10(r)
		or $17, $0, $16			# $17 <- @
		addu $17, $17, $8		# $17 <- @(chaine[i])
		sb $13, 0($17)			# $13 -> chaine[i]
		
		
		#  i -= 1
		addiu $8, $8, -1
		j loop
end_loop:

	# printf("%s", chaine);
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	# nbzero = 0;
	ori $11, $0, 0				# $11(nbzero) <- 0
	
	# i = 0;
	ori $8, $0, 0				# $8(i) <- 0
	
	loop2:
		# Fin de boucle: i >= 9 || chaine[i] != 0x30
		# i >= 9
		slti $10, $8, 9			# $10=1 si i<9, $10=0 si i>=9
		beq $10, $0, end_loop2
		
		# chaine[i] != 0x30
		ori $12, $0, 0x30		# $12 <- 0x30
		addu $17, $16, $8		# $17 <- @(chaine[i])
		lbu $13, 0($17)			# $13 <- chaine[i]
		bne $13, $12, end_loop2
		
		# nbzero += 1;
		addiu $11, $11, 1
		
		# i++;
		addiu $8, $8, 1			
		
		j loop2
		
end_loop2:
	
	
	# printf("%d", nbzero); 
	ori $2, $0, 1
	or $4, $0, $11
	syscall
	
	
	# i = 0
	ori $8, $0, 0				# $8(i) <- 0
	ori $12, $0, 10				# $12 <- 10
	subu $12, $12, $11			# $12 <- $12 - $11(nbzero)
	addiu $12, $12, 1			# $12 <- $12 + 1
	
	loop3:
		# Fin de boucle: i >= 10 - nbzero + 1
		slt $13, $8, $12		# $13=1 si i <  10 - nbzero + 1, $13=0 si i >= 10 - nbzero + 1
		beq $13, $0, end_loop3
		
		# chaine[i] = chaine[i + nbzero];
		addu $14, $8, $11		# $14 <- i + nbzero
		addu $14, $16, $14		# $14 <- @(chaine[i+nbzero])
		lbu $15, 0($14)			# $15 <- chaine[i+nbzero]
		addu $14, $16, $8		# $14 <- @chaine[i]
		sb $15, 0($14)			# $15 -> chaine[i]
		
		# i += 1;
		addiu $8, $8, 1
		
		j loop3
end_loop3:	 
	
	# printf("%s", chaine);
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	
	# Epilogue
	addiu $29, $29, +16
	
	
	ori $2, $0, 10
	syscall

	