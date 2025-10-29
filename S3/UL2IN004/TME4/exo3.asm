.data

	ch: .asciiz "coucou"

.text
	lui $16, 0x1001
	
	
	lb $17, 0($16)
	lb $18, 1($16)
	
	addi $17, $17, 5
	addi $18, $18, 5
	
	sb $17, 0($16)
	sb $18, 1($16)	

	
	ori $2, $0, 4
	or $4, $0, $16
	syscall