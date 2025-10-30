.data
	ch: .asciiz "1234"		# 0x10010000 | @

.text
	# prologue 
	# 0($29)=i, 4($26)=val, 8($26)=c
	addiu $29, $26, -12		# Alloue 12 octets 
	  
	ori $8, $0, 0			#  i <- 0
	ori $9, $0, 0			# val <- 0
	lui $16, 0x1001			# $16 <- @data
	
	# Corps
	loop:
		# Fin de boucle: ch[i] == 0
		addu $25, $16, $8	# $25 <- @(data + i)
		lbu $10, 0($25)		# $10 <- ch[i]
		beq $10, $0, end_loop
		
		# c = ch[i];
		or $11, $0, $10		# c <- ch[i]
		
		#c = c & 0x0F;
		andi $11, $11, 0x0F	# c <- c & 0x0F
		
		#val = val * 10 + c;
		ori $12, $0, 10		# $12 <- 10
		mult $9, $12		# LO <- val * 10
		mflo $9			# $9(val) <- LO
		addu $9, $9, $11	# $9(val) <- $9()val + c
		
		#i += 1;
		addiu, $8, $8, 1	# $8 <- i+1
		j loop
	
	
end_loop:
	
	# printf("%d", val);
	ori $2, $0, 1
	or $4, $0, $9
	syscall
	
	# Epilogue
	addiu $29, $26, 12
	

	# Exit
	ori $2, $0, 10
	syscall