.data

	chaine: .space 11 	# chaine[11] 

.text 
	# Prologue
	addiu $29, $29, -16 	# 4 int  donc 4*4 octets
	#i +0; nb +4; r +8; nbzero +12
	
	#scanf("%d", &nd);
	lw $5, 4($29)		# $5 <- nb
	ori $2, $0, 5
	syscall
	or $5, $0, $2		# $5 <- input
	sw $5, 4($29)		# $5 -> nb
	
	#chaine[10] = 0
	lui $16, 0x1001		# $16 <- @ chaine
	sb $0, 10($16)		# chaine[10] = 0
	
	# i = 9
	ori $6, $0, 9		# $6 = 9
	sw $6, 0($29)		# $6 -> i
	
	loop:
		# i < 0
		lw $6, 0($29)	# $6 <- i
		bltz $6, end_loop
		
		# r = nb % 10

		lw $8, 4($29)		# $8 <- nb
		ori $10, $0, 10 	# $10 <- 10
		div $8, $10		# nb / 10
		mfhi $7			# r = nb % 10
		sw $7, 8($29)		# $7 -> r
		
		# nb = nb / 10
		lw $8, 4($29) 		# $8 <- nb
		ori $10, $0, 10 	# $10 <- 10
		div $8, $10		
		mflo $8			# $8 <- nb / 10
		sw $8, 4($29)		# $8 -> nb
		
		#chaine[i] = r + 0x30
		lui $16, 0x1001		# $16 <- @chaine
		lw $7, 8($29)		# $7 <- r
		lw $6, 0($29)		# $6 <- i
		addu $10, $6, $16	# $10 <- chaine + i
		addiu $11, $7, 0x30	# $11 <- r + 0x30
		sb $11, 0($10)		# chaine[i] = r + 0x30
		
		
		#i -= 1
		lw $6, 0($29)		# $6 <- i
		addiu $6, $6, -1	# i-=1
		sw $6, 0($29)		# $6 -> i
		
		j loop
	
	end_loop:	
	
	# printf("%s", chaine)
	ori $2, $0, 4
	lui $4, 0x1001
	syscall
		
	
	# Epilogue
	addiu $29, $29, +16
	
	# exit()
	ori $2, $0, 10
	syscall