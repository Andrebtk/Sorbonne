.data
		
	p1: 	.asciiz "X"			# &p1 = @ <- 0x10010000
		.word 2				# &p1.abs = @ + 2 + 2(align)
		.word 6				# &p1.ord = (@ + 4) + 4= @ + 8
		
		
	p2: 	.asciiz	"Y"			# &p1 = @ + 12
		.word 4				# &p1.abs = @ + 16
		.word 4				# &p1.ord = @ + 20
	
		.align 2
	p3: 	.space 12			# &p3 = @ + 24
						# &p3.abs = @ + 28
						# &p3.ord = @ + 32
		
		.align 2
	p4: 	.space 4			# &p4 = @ + 36
	
	
	
.text
	lui $16, 0x1001				# $16 <- @
	ori $17, $0, 2				# $17 <- 2
		
	# ptr = &p3;
	xor $8, $8, $8				# $8 <- 0
	addiu $8, $16, 24			# $8 <- &p3
	sw $8, 36($16)				# $8 -> p4
	
	
	
	# ptr->abs = (p1.abs + p2.abs) / 2;
	lw $9, 4($16)				# $9 <- p1-abs
	lw $10, 16($16)				# $10 <- p2.abs
	addu $11, $9, $10			# $11 <- p1.abs + p2.abs
	div $11, $17				# LO <- (p1.abs + p2.abs) / 2
	mflo $11				# $11 <- LO
	sw $11, 4($8)				# $11 -> ptr->abs
	
	# ptr->ord = (p1.ord + p2.ord) / 2;
	lw $9, 8($16)				# $9 <- p1.ord
	lw $10, 20($16)				# $10 <- p2.ord
	addu $11, $9, $10			# $11 <- p1.ord + p2.ord
	div $11, $17				# LO <- (p1.ord + p2.ord) / 2
	mflo $11				# $11 <- LO
	sw $11, 8($8)				# $11 -> ptr->ord
	
	# ptr->nom[0] = ’Z’;
	ori $12, $0, 0x5A			# $12 <- 'Z'
	sb $12, 0($8)				# $12 -> ptr->nom[0]
	
	# ptr->nom[1] = ’\0’;
	ori $12, $0, 0x00			# $12 <- '\0'
	sb $12, 1($8)				# $12 -> ptr->nom[1]
	
	
	# printf("%s", p3.nom);
	ori $2, $0, 4
	or $4, $0, $8
	syscall
	
	# printf("%d", p3.abs);
	ori $2, $0, 1
	lw $4, 4($8)
	syscall
	
	# printf("%d", p3.ord);
	ori $2, $0, 1
	lw $4, 8($8)
	syscall
	
	
	
	#exit
	ori $2, $0, 10
	syscall 