.data
	ch: .asciiz "coucou"

.text
	lui $16, 0x1001		# @ data
	lbu $8, 0($16)		# $8 <- "c"
	lbu $9, 1($16)		# $9 <- "o"
	
	# on inverse 'c' et 'o' dans ch
	sb $8, 1($16)		
	sb $9, 0($16)	
	
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	
	ori $2, $0, 10
	syscall