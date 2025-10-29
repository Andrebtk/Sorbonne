.data

.text
	
	ori $2, $0, 5
	syscall
	or $16, $0, $2		# $16 <- entier (input)

	ori $2, $0, 5
	syscall
	or $17, $0, $2		# $17 <- entier (input)	
	

	div $16, $17		# (entier1) / (entier2)
	mflo $18		# $18 <- ((entier1) / (entier2))
	mfhi $19		# $19 <- ((entier1) % (entier2))

	
	# Affichage quotient
	ori $2, $0, 1
	or $4, $0, $18  
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	
	# Affichage reste
	ori $2, $0, 1
	or $4, $0, $19  
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	mult $18, $17		#  $18 * $17
	mflo $13		# $13 <- ($18 * $17)
	addu $13, $13, $19	# $13 <- ($18 * $17) + $12 = $16
	
	# Affichage $13
	ori $2, $0, 1
	or $4, $0, $13
	syscall
	
	# exit
	ori $2, $0, 10
	syscall
	
	