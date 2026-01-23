.data 
	v1: .word -1
	v2: .word 0xFF
	
	
.text
	lui $16, 0x1001		# $16 <- @ data
	lw $8, 0($16)		# $8 <- v1
	lw $9, 4($16)		# $9 <- v2
	
	or $17, $0, $8
	or $18, $0, $9		# Registre persistans
	
	addi $17, $17, 1
	addi $18, $18, 1
	
	sw $17, 0($16)		# v1 <- $17
	sw $18, 4($16)		# v2 <- $18
	
	
	ori $2, $0, 1
	or $4, $0, $17
	syscall			# Affiche la valeur de $17
		
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche la valeur de '\n'	
	
	ori $2, $0, 1
	or $4, $0, $18
	syscall			# Affiche la valeur de $18
	
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall			# Affiche la valeur de '\n'
	
	ori $2, $0, 10
	syscall			# Fin de program 