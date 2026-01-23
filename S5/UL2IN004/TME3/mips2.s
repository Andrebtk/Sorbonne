.data

.text
	ori $2, $0, 5
	syscall			
	or $18, $0, $2		# Lit un entier et le stock dans $18 (84)
	
	ori $2, $0, 5
	syscall
	or $19, $0, $2		# Lit un entier et le stock dans $19 (10)

	
	div $18, $19 		# division de $18 et $19 (84/10)
	
	mfhi $16 		# $16 <- HIGH (Reste) (4)
	mflo $17		# $17 <- LOW (quotien) (8)
		
	ori $2, $0, 1
	or $4, $0, $17
	syscall			# Affiche le quotien (8) sur la console
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche '\n'
	
	ori $2, $0, 1
	or $4, $0, $16
	syscall			# Affiche le reste (4) sur la console
	
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche '\n'

	mult $17, $19		# Multiplication quotien (de $18 * $19 -> 8) et l'entier $19 (10)
	mflo $23		# $23 <- LOW (32 bit) (80)
	
	add $22, $23, $16	# Addition (80 + 4)
	
	ori $2, $0, 1 
	or $4, $0, $22
	syscall			# Affichage resultat 
	
	
	ori $2, $0, 10
	syscall			# Fin de program
	
	 