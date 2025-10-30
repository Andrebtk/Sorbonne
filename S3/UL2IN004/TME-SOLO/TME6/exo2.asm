.data
	p1:	.asciiz "X"		# @p1.nom = 0x10010000 
		.word 2			# @p1.abs = 0x10010000 + 2 + align=2=0x10010004
		.word 6			# @p1.ord = 0x10010008
					# taille p1 -> 12 octets
		
	p2: 	.asciiz "Y"		# @p2.nom = 0x1001000c (+12)
		.word 4			# @p2.abs = (12 + 2) + align=2 = +16
		.word 4			# @p2.ord = +20
	
	p3: 	.align 2		
		.space 10		# @p3.nom[0] = +24
					# @p3.nom[1] = +25 
					# @p3.abs = (24 + 2 + 2) = +28
					# @p3.ord = +32
		.align 2		
	ptr:	.space 4		# @ + 36


.text
	ori $17, $0, 2		# $17 <- 2

	# ptr = &p3;
	lui $16, 0x1001		# $16 <- p1 | @
	addiu $8, $16, 24	# $8 <- &p3
	sw $8, 36($16)		# &p3 -> ptr
	
	
	# ptr->abs = (p1.abs + p2.abs) / 2;
	lw $9, 4($16)		# $9 <- p1.abs
	lw $10, 20($16)		# $10 <- p2.abs
	addu $9, $9, $10	# $9 <- p1.abs + p2.abs
	div $9, $17		# LO <- (p1.abs + p2.abs) / 2
	mflo $9			# $9 <- L0
	lw $8, 36($16)		# $8 <- ptr(&p3)
	sw $9, 4($8)		# $9 -> ptr->abs 
	
	
	# ptr->ord = (p1.ord + p2.ord) / 2;
	lw $9, 8($16)		# $9 <- p1.ord
	lw $10, 20($16)		# $10 <- p2.ord
	addu $9, $9, $10	# $9 <- p1.ord + p2.ord
	div $9, $17		# LO <- (p1.ord + p2.ord) / 2
	mflo $9			# $9 <- L0
	sw $9, 8($8)		# $8 -> ptr->ord
	
	
	# ptr->nom[0] = ’Z’;ptr
	ori $9, $0, 0x5A	# $9 <- 'Z'
	sb $9, 0($8)		# $9 -> ptr->nom[0]
	
	# ptr->nom[1] = ’\0’	
	ori $9, $0, 0x00	# $9 <- '\0'
	sb $9, 1($8)		# $9 -> ptr->nom[1]
	
	
	addiu $17, $16, 24
	
	# printf("%s", p3.nom);
	ori $2, $0, 4
	or $4, $0, $17
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# printf("%d", p3.abs);
	ori $2, $0, 1
	lw $4, 4($17)
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# printf("%d", p3.ord);
	ori $2, $0, 1
	lw $4, 8($17)
	syscall
	
	# exit
	ori $2, $0, 10
	syscall