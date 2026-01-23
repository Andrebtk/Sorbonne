.data
	q3: .byte 0xFF

.text
	lui $16, 0x1001
	
	lb $9, 0($16)
	lbu $10, 0($16)
	
	or $17, $0, $9
	or $18, $0, $10
	
	ori $2, $0, 1
	or $4, $0, $17
	syscall			# Affiche la valeur de $17
		
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche la valeur de '\n'	
	
	ori $2, $0, 1
	or $4, $0, $18
	syscall			# Affiche la valeur de $18