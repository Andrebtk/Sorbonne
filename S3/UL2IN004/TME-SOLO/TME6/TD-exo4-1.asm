.data
	ch2: .space 20			# @ <- 0x10010000
	N: .word 4			# @ + 20
	ch1: .ascii "Hello" 		# @ + 24
	
.text
	# Prologue
	addiu $29, $29, -4		# Alloue  octets
	
	# int i = 0;
	sw $0, 0($29)
	
	loop:
		
		lw $8, 0($29)		# $8 <- i
		lui $16, 0x1001		# $16 <- @
		lw $9, 20($16)		# $9 <- N
		
		#fin de boucle: i >= N
		slt $10, $8, $9		# $10=1 si i < N
		beq $10, $0, end_loop
		
		# ch2[i] = ch1[i];
		lw $8, 0($29)		# $8 <- i
		lui $16, 0x1001		# $16 <- @
		addiu $17, $16, 24	# $17 <- @ch1
		addu $17, $17, $8	# $17 <-@(ch1[i])
		lbu $10, 0($17)		# $10 <- ch1[i]
		addu $16, $16, $8	# $16 <- @(ch2[i])
		sb $10, 0($16)		# ch1[i] -> ch2[i] 
		
		
		# i += 1
		lw $8, 0($29)		# $8 <- i
		addiu, $8, $8, 1	# i++
		sw $8, 0($29)		# $8 -> i
		
		j loop
	
end_loop:
	# ch2[i] = ’\0’;
	lui $16, 0x1001		# $16 <- @
	lw $8, 0($29)		# $8 <- i
	addu $16, $16, $8	# $16 <- @(ch2[i])
	ori $10, $0, 0x00
	sb $10, 0($16)		# $10 -> ch2[i]
	
	
	# printf("%s", ch2);
	ori $2, $0, 4
	lui $4, 0x1001		# $4 <- @
	syscall
	
	
	# Epilogue
	addiu $29, $29, 4
	
	# Exit
	ori $2, $0, 10
	syscall