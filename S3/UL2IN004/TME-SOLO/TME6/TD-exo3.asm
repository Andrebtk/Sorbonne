.data
	ch: .asciiz "1234"		# 0x10010000

.text
	# prologue 
	# 0($29)=i, 4($26)=val, 8($26)=c
	addiu $29, $26, -12		# Alloue 12 octets | 
	  
	sw $0, 0($29)			#  i <- 0
	sw $0, 4($29)			# val <- 0
	
	# Corps
	loop:
		# Fin de boucle: ch[i] == 0
		lw $8, 0($29)		# $8 <- i
		lui $16, 0x1001		# $16 <- @data
		addu $25, $16, $8	# $25 <- @(data + i)
		lbu $10, 0($25)		# $10 <- ch[i]
		beq $10, $0, end_loop
		
		# c = ch[i];
		lui $16, 0x1001 	# $16 <- @data
		lw $8, 0($29)		# $8 <- i
		addu $25, $16, $8	# $25 <- @(data + i)
		lbu $10, 0($25)		# $10 <- ch[i]
		sb $10, 8($29)		# $10 -> c
		
		#c = c & 0x0F;
		lbu $9, 8($29)		# $9 <- c
		andi $10, $9, 0x0F	# $10 <- c & 0x0F
		sb $10, 8($29)		# $10 -> c
		
		#val = val * 10 + c;
		lw $10, 4($29)		# $10 <- val
		lbu $9, 8($29)		# $9 <- c
		ori $11, $0, 10		# $11 <- 10
		mult $10, $11		# LO <- val * 10
		mflo $11		# $11 <- LO
		addu $11, $11, $9	# $11 <- $11 + c
		sw $11, 4($29)		# $11 -> val
		
		#i += 1;
		lw $8, 0($29)		# $8 <- i
		addiu, $8, $8, 1	# $8 <- i+1
		sw $8, 0($29)
		j loop
	
	
end_loop:
	
	# printf("%d", val);
	ori $2, $0, 1
	lw $4, 4($29)
	syscall
	
	# Epilogue
	addiu $29, $26, 12
	

	# Exit
	ori $2, $0, 10
	syscall