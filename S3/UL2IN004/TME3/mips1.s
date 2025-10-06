.data

.text
	ori $8, $0, 65537
	or $4, $0, $8
	ori $2, $0, 1
	syscall 		# Affichage decimale
	
	ori $2, $0, 10
	syscall  		# Fin de program