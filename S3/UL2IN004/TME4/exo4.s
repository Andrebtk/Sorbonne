.data
	chain: .byte 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x00

	

.text
	
	lui $16, 0x1001		# @ segemnt Data
	
	
	lbu $17, 2($16)		# $17 <- MEM($16 + 2)
	
	ori $2, $0, 1
	or $4, $0, $17		# decimal($17) -> 51
	syscall			# Affiche l'entier $17
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche la valeur de '\n'
	
	ori $18, $0, 48		# $18 <- 0x30(code ascii pour 0)
	sub $19, $17, $18	# $19 <- $17 - 0x30 | $19 est la valeur rechercher
	
	
	ori $2, $0, 1
	or $4, $0, $19
	syscall			# Syscall pour affiche l'entier $19
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche la valeur de '\n'
	
	
	ori $2, $0, 4
	or $4, $0, $16
	syscall			# Affiche chain
	
	ori $2, $0, 10
	syscall			# Fin de programe