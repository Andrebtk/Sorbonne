.data
	tab: .byte 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x00
.text
	
	lui $16, 0x1001		# @data
	
	lbu $17, 3($16)		# $17 <- 3eme caractere de la chaine dec('3') = 51 
	
	addiu $18, $17, -48	# $18 <- $17 - 48 = (dec('0'))
	
	ori $2, $0, 1
	or $4, $0, $18
	syscall
	
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	
	# Affichage chaine de caractères (tab)
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	ori $2, $0, 10
	syscall