.data
	m: .byte 0xFF

.text
	lui $16, 0x1001		# @Data
	lb $9, 0($16)		# $9 <- m
	lbu $10, 0($16)		# $10 <- m (unsigned)
	
	ori $2, $0, 1
	or $4, $0, $9
	syscall
	
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	ori $2, $0, 1
	or $4, $0, $10
	syscall
	
	# exit
	ori $2, $0, 10
	syscall