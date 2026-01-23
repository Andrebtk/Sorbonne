.data

.text 
	# Prologue
	
	# 0($29)=chaine[0], ... 12()=i, 16=nb, 20=r, 24=nbzero
	addiu $29, $29, -28 		# 4 entier + (11+1) char
	
	# scanf("%d", &nb); 
	ori $2, $0, 5
	syscall
	or $16, $0, $2			# $16(nb) <- input
	
	# chaine[10] = 0;
	sb $0, 10($29)
	
	ori $8, $0, 9			# $8 <- 9
	ori $10, $0, 10			# $10 <- 10
	loop:
		# Fin de boucle: i < 0
		bltz $8, end_loop
		
		# r = nb % 10
		div $16, $10		# LO <- nb / 10, HI <- nb % 10
		mfhi $9			# $9(r) <- LO
		
		
		# nb = nb / 10;
		mflo $16		# $16(nb) <- HI
		
		# chaine[i] = r + 0x30;
		addu $17, $29, $8	# $17 <- @(chaine[i])
		addiu $11, $9, 0x30	# $11 <- $9(r) + 0x30
		sb $11, 0($17)		# $11 -> chain[i]
		
		# i -= 1
		addiu $8, $8, -1
		j loop
	
end_loop:

	# printf("%s", chaine);
	ori $2, $0, 4
	or $4, $0, $29
	syscall
	
	
	# Epilogue 
	addiu $29, $29, 28
	
	# exit()
	ori $2, $0, 10
	syscall