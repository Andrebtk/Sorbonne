.data
	chaine: .space 11	# @ = 0x10010000

.text
	lui $16, 0x1001		# $16 <- @
	
	# Prologue
	# 0($29)=i, 4=nb, 8=r, 12=nbzero
	addiu $29, $29, -16
	
	
	# Corp
	
	# scanf("%d", &nb); 
	ori $2, $0, 5
	syscall
	or $9, $0, $2		# $9(nb) = (input) 
	
	#chaine[10] = 0;
	sb $0, 10($16)
	
	ori $8, $0, 9		# $8(i) <- 9
	ori $12, $0, 10		# $12 <- 10
	
	loop:
		# Fin de boucle:  i < 0
		bltz $8, end_loop
		
		# r = nb % 10;
		div $9, $12		# Lo <- nb / 10 | HI <-	nb % 10
		mfhi $10		# $10(r) <- HI
		
		# nb = nb / 10
		mflo $9			# $9(nb) <- LO
		
		# chaine[i] = r + 0x30;
		addu $13, $0, $10	# $13 <- r
		addiu $13, $13, 0x30	# $13 <- r + 0x30
		
		addu $17, $16, $8	# $17 <- @(chaine[i])
		sb $13, 0($17)		# $13 -> chaine[i]
		
		
		 #i -= 1
		addiu $8, $8, -1	# i -= 1
		
		j loop
	
end_loop:
	
	# printf("%s", chaine);
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	# affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	
	# nbzero = 0;
	ori $11, $0, 0 		# $11(nbzero) <- 0
	
	# i = 0;
	ori $8, $0, 0		# $8(i) <- 0
	ori $15, $0, 0x30	# $15 <- 0x30
	
	loop2:
		# Fin de boucle: i >= 9 || chaine[i] != 0x30
		#  i >= 9
		slti $12, $8, 9			# $12=1 si i<9, 0 si i>=9
		beq $12, $0, end_loop2
		
		# chaine[i] != 0x30
		addu $17, $16, $8		# $17 <- @(chaine[i])
		lb $13, 0($17)			# $13 <- chaine[i]
		bne $13, $15, end_loop2
		
		# nbzero += 1;
		addiu $11, $11, 1		# $11(nbzero) <- $11+1
		
		# i++;
		addiu $8, $8, 1			# $8(i) <- $8 + 1
		
		j loop2
		
end_loop2:
	
	# printf("%d", nbzero);
	ori $2, $0, 1
	or $4, $0, $11
	syscall
	
	# affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# i = 0
	ori $8, $0, 0		# $8(i) <- 0
	addiu $12, $0, 10	# $12 <- 10
	subu $12, $12, $11	# $12 <- 10 - nbzero
	addiu $12, $12, 1	# $12 <- (10 - nbzero + 1)
	
	loop3:
		# fin de boucle:  i >= (10 - nbzero + 1)
		slt $13, $8, $12			# $13=1 si i<(10 - nbzero + 1)
		beq $13, $0, end_loop3
		
		
		# chaine[i] = chaine[i + nbzero];
		addu $14, $8, $11			# $14 <- i + nbzero
		addu $17, $16, $14			# $17 <- @(chaine[i+nbzero])
		lbu $13, 0($17)				# $13 <- chaine[i+nbzero]
		addu $17, $16, $8			# $17 <- @(chaine[i])
		sb $13, 0($17)				# $13 -> chaine[i]
		
		# i+= 1
		addiu $8, $8, 1
		
		j loop3
		
		
end_loop3:	
	
	# printf("%s", chaine);
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	
	# Epilogue
	addiu $29, $29, 16
	
	# Exit
	ori $2, $0, 10
	syscall