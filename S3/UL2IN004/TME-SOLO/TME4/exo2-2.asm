.data
	v1: .word -1		# @ -> 0x10010000
	v2: .word 0xFF		# @ -> 0x10010004
.text
	lui $16, 0x1001		# @Data
	lw $8, 0($16)		# $8 <- v1
	lw $9, 4($16)		# $9 <- v2
	
	# Registre permanant
	or $17, $0, $8		# $17 <- v1
	or $18, $0, $9		# $18 <- v2
	
	addiu $17, $17, 1	# v1 +1
	addiu $18, $18, 1	# v2 +1
	sw $17, 0($16)		# $17 -> v1
	sw $18, 4($16)		# $18 -> v2
	
	# Affichage v1
	ori $2, $0, 1
	or $4, $0, $17
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# Affichage v2
	ori $2, $0, 1
	or $4, $0, $18
	syscall
	
	# exit
	ori $2, $0, 10
	syscall