.data
	p1:	.asciiz "X" 		# &p1.nom = @ 
		.word 2			# &p1.abs = @ +2 + 2align = @ + 4
		.word 6			# &p1.ord = @ + 8
		
	p2: 	.asciiz "Y"		# &p2.nom = @ + 12
		.word 4			# &p2.abs = (@ + 12) + 2 + 2align = @ + 16
		.word 4			# &p2.ord = @ + 20
		
		
		.align 2
	p3: 	.space 12 		# &p3.com = @ + 24
					# &p3.abs = @ + 28 (align + 2)
					# &p3.ord = @ + 32
		
		.align 2
	ptr: 	.space 4		# &ptr = @ + 36
	
.text
	ori $19, $0, 2			# $19 <- 2
	
	# ptr = &p3;
	lui $16, 0x1001			# $16 <- @
	addiu $17, $16, 24		# $17 <- &p3
	sw $17, 36($16)
	
	lw $20, 36($16)			# $20 <- *ptr = &p3
	
	# ptr->abs = (p1.abs + p2.abs) / 2;
	lw $8, 4($16)			# $8 <- p1.abs
	lw $9, 16($16)			# $9 <- p2.abs	
	addu $10, $8, $9		# $10 <- p1.abs + p2.abs
	div $10, $19			# LO <- (p1.abs + p2.abs) / 2
	mflo $8				# $8 <- LO
	sw $8, 4($20)			# $8 -> ptr->abs
	
	# ptr->ord = (p1.ord + p2.ord) / 2;
	lw $8, 8($16)			# $8 <- p1.ord
	lw $9, 20($16)			# $9 <- p2.ord	
	addu $10, $8, $9		# $10 <- p1.ord + p2.ord
	div $10, $19			# LO <- (p1.ord + p2.ord) / 2
	mflo $8				# $8 <- LO
	sw $8, 8($20)			# $8 -> ptr->ord
	
	# ptr->nom[0] = ’Z’
	ori $8, $0, 0x5A		# $8 <- 'Z'
	sb $8, 0($20)			# 'Z' -> ptr->nom[0]
	
	# ptr->nom[1] = ’\0’;
	ori $8, $0, 0x00		# $8 <- '\0'
	sb $8, 1($20)			# '\0' -> ptr->nom[1]
	
	# printf("%s", p3.nom);
	ori $2, $0, 4
	or $4, $0, $20
	syscall
	
	# affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# printf("%d", p3.abs);
	ori $2, $0, 1
	lw $4, 4($20)
	syscall
	
	# affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# printf("%d", p3.ord);
	ori $2, $0, 1
	lw $4, 8($20)
	syscall
	
	# Exit
	ori $2, $0, 10
	syscall