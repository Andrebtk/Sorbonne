.data
.text
	ori $16, $0, 0xAABBCCDD
	# o3 = AA, o2=BB, o1=CC, o0=DD
	
	
	# Affichage 0xAABBCCDD
	ori $2, $0, 34
	or $4, $0, $16
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	andi $17, $16, 0xFF000000 	# $17 <- o3
	andi $18, $16, 0x00FF0000	# $18 <- o2
	andi $19, $16, 0x0000FF00	# $19 <- o1
	andi $20, $16, 0x000000FF	# $20 <- o0
	
	srl $17, $17, 16		# $17 <- 0x000000XX00
	srl $19, $19, 8			# $19 <- 0x00000000XX
	sll $20, $20, 24		# $20 <- 0xXX00000000
	
	# Assemble le mot
	or $3, $0, $17
	or $3, $3, $18
	or $3, $3, $19
	or $3, $3, $20
	
	# Affichage $3
	ori $2, $0, 34
	or $4, $0, $3
	syscall
	
	
	# Fin de program
	ori $2, $0, 10
	syscall