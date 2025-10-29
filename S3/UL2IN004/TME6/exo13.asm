# NE PAS UTILISER LES REGISTE DE PARAM
# UTILISER DES REGISTRE PERMANANT POUR L'OPTIMISATION
.data

	chaine: .space 11 	# chaine[11] 

.text 
	# Prologue
	addiu $29, $29, -16 	# 4 int  donc 4*4 octets
	#i +0; nb +4; r +8; nbzero +12
	
	#scanf("%d", &nd);
	# $5 -> nb
	# $6 -> i
	# $7 -> r
	# $8 -> nbzero
	ori $2, $0, 5
	syscall
	or $5, $0, $2		# $5 <- input

	
	#chaine[10] = 0
	lui $16, 0x1001		# $16 <- @ chaine
	sb $0, 10($16)		# chaine[10] = 0
	
	# i = 9
	ori $6, $0, 9		# $6 = 9
	
	loop:
		# i < 0
		bltz $6, end_loop
		
		# r = nb % 10
		xor $7, $7, $7		# $7 <- 0
		ori $10, $0, 10 	# $10 <- 10
		div $5, $10		# nb / 10
		mfhi $7			# r = nb % 10
		
		# nb = nb / 10
		ori $10, $0, 10 	# $10 <- 10
		div $5, $10		
		mflo $5			# $5 <- nb / 10
		
		#chaine[i] = r + 0x30
		lui $16, 0x1001		# $16 <- @chaine
		addu $10, $6, $16	# $10 <- chaine + i
		addiu $11, $7, 0x30	# $11 <- r + 0x30
		sb $11, 0($10)		# chaine[i] = r + 0x30
		
		#i -= 1
		addiu $6, $6, -1	# i-=1
		
		j loop
	
end_loop:	
	
	# printf("%s", chaine)
	ori $2, $0, 4
	lui $4, 0x1001
	syscall
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall				# affiche '\n'
	
	ori $8, $0, 0 			# nbzero = 0
	ori $6, $0, 0 			# i = 0
	
	while:
		# i >= 9
		slti $9, $6, 9
		beq $9, $0, end_while	# fin boucle si i>=9
		
		# chaine[i] != 0x30
		addu $10, $6, $16	# $10 <- @ chaine[i]
		lb $11, 0($10)		# $11 <- chaine[i]
		ori $12, $0, 0x30	# $12 <- 0x30
		bne $11, $12, end_while # fin boucle si chaine[i] != 0x30
		
		# nbzero += 1
		addiu $8, $8, 1
		# i++
		addiu $6, $6, 1
		
		j while

end_while:
	#printf("%d", nbzero)
	ori $2, $0, 1
	or $4, $0, $8			#$4 <- nbzero
	syscall
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall				# affiche '\n'
	
	
	ori $6, $0, 0			# i = 0
	while2:
		# i >= (10-nbzero+1)
		ori $10, $0, 11		# $10 <- 11
		addu $10, $10, $8	# $10 <- 11-nbzero
		
		slt $9, $6, $10
		beq $9, $0, end_while2	# fin de boucle
		
		addu $17, $6, $16	# $17 <- @ chaine[i]
		addu $18, $17, $8	# $18 <- @ chaine[i + nbzero]
		lb $19, 0($18)		# $19 <- chaine[i + nbzero]
		sb $19, 0($17)		# $19 -> chain[i]
		
		addiu $6, $6, 1		# i += 1
		
		j while2
		
		
end_while2:
	
	# printf("%s", chaine)
	ori $2, $0, 4
	lui $4, 0x1001
	syscall
	
	# Epilogue
	addiu $29, $29, +16
	
	# exit()
	ori $2, $0, 10
	syscall