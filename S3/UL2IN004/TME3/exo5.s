.data 

.text	
	# Met 0xAABBCCDD dans $3 
	ori $3, $0, 0xAABB
	sll $3, $3, 16			# Shift left pour apres mettre le reste des valeur dans les bit restant
	ori $3, $3, 0xCCDD
	
	# Affiche $3 a l'ecran
	or $4, $0, $3
	ori $2, $0, 34
	syscall

	# Affiche '\n'	
	ori $4, $0, 0x0A 		# code ASCII pour '\n' (LF)
	ori $2, $0, 11
	syscall
	
	# Partie 2
	ori $3, $0, 0xABCD 		# objectif $5=0xDBAC	

	ori $8, $0, 0xF000		# Masque pour le bit 3
	ori $9, $0, 0x0F00		# Masque pour le bit 2
	ori $10, $0, 0x00F0		# Masque pour le bit 1
	ori $11, $0, 0x000F		# Masque pour le bit 0
		
	and $16, $3, $8 		# Masque -> recupere le bit 3 dans $16
	and $17, $3, $9			# Masque -> recupere le bit 2 dans $17
	and $18, $3, $10		# Masque -> recupere le bit 1 dans $18
	and $19, $3, $11		# Masque -> recupere le bit 0 dans $19
	
	
	srl $16, $16, 8			# Shift R $16 de 8 bit pour obtenir 0x00bit(3)0
	srl $18, $18, 4			# Shift R $18 de 12 bit pour obtenir 0x000bit(1)
	sll $19, $19, 12		# Shift L $19 de 12 bit pour obtenir 0xbit(0)000
	
	or $5, $17, $16			# OR -> bit(2) OR bit(3)
	or $5, $5, $18			# OR -> $5 OR bit(1)
	or $5, $5, $19			# OR -> $5 OR bit(0)
	
	# Affiche $5 a l'ecran
	or $4, $0, $5
	ori $2, $0, 34
	syscall
	
	
	# Affiche '\n'	
	ori $4, $0, 0x0A 		# code ASCII pour '\n' (LF)
	ori $2, $0, 11
	syscall
	# Affiche '\n'	
	ori $4, $0, 0x0A 		# code ASCII pour '\n' (LF)
	ori $2, $0, 11
	syscall
	

	# Fin de program
	ori $2, $0, 10
	syscall