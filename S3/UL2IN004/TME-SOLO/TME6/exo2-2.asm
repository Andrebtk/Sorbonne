.data
	N: .word 4		# @ = 0x10010000
.text
	lui $16, 0x1001		# $16 <- @
	lw, $17, ($16)		# $17 <- N	
	# Prologue
	# 0=i, 4=ch2[0], 24=ch2[19], 25=ch1[0], 29=ch1[4]
	addiu $29, $29, 32 	 # alloue (1 int(4) et 25 char et align )
	
	
	
	# char ch1[] = "Hello";	
	ori $8, $0, 0x48	# $8 <- 'H'
	sb $8, 25($29)		# ch1[0] = 'H'
	ori $8, $0, 0x65	# $8 <- 'e'
	sb $8, 26($29)		# ch1[1] = 'e'
	ori $8, $0, 0x6c	# $8 <- 'l'
	sb $8, 27($29)		# ch1[2] = 'l'
	ori $8, $0, 0x6c	# $8 <- 'l'
	sb $8, 28($29)		# ch1[3] = 'l'
	ori $8, $0, 0x6F	# $8 <- '0'
	sb $8, 29($29)		# ch1[4] = '0'
	
	# int i = 0;
	ori $8, $0, 0		# $8(i) <- 0
	
	loop:
		# Fin de boucle:  i >= N
		slt $10, $8, $17	# $10=1 si N < i, N >= i
		beq $10, $0, end_loop
		
		# ch2[i] = ch1[i];
		addu $10, $29, $8  	# $10 <- sp + i
		
		lb $11, 25($10)		# $11 <- ch1[i]
		sb $11, 4($10)		# $11 -> ch2[i]
		
		# i += 1
		addiu $8, $8, 1
		j loop	
		
end_loop:

	# printf("%s", ch2);
	ori $2, $0, 4
	addiu $4, $29, 4
	syscall
	
	
	# Epilogue
	addiu $29, $29, -32
	
	# exit
	ori $2, $0, 10
	syscall