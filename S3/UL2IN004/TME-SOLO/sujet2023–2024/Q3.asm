.data
	str: .asciiz "azerty"		# @ <- 0x10010000
	str_res: .space 20		# @ + 5

.text
	lui $16, 0x1001			# $16 <- @
	
	# prologue
	# 0($29)=c, 4($29)=n, 8($29)=idx_dst
	addiu $29, $29, -12		# alloue 3 int
	
	# corp
	
	#int c = 0;
	ori $8, $0, 0			# $8(c) <- 0
	
	loop:
		# fin de boucle: str[c] == ’\0’ (0x00)
		addu $17, $16, $8	# $17 <- &str[c]
		lbu $10, 0($17)		# $10 <- str[c]
		ori $11, $0, 0x00	# $11 <- '\0' = 0x00
		beq $10, $11, end_loop
		
		# c += 1;
		addiu $8, $8, 1
		
		j loop	
	
end_loop:

	#n = len(str);
	or $18, $0, $8			# $18(n) <- len(str)
	
	#miroir(str, str_res, n - 1);
	
	#int idx_dst = 0;
	ori $8, $0, 0			# $8(idx_dst) <- 0
	xor $9, $9, $9			# $9(idx_src) <- 0
	subiu $9, $18, 1		# $9(idx_src) <- n - 1
	
	loop2:
		# Fin de boucle: idx_src < 0
		bltz $9, end_loop2
		
		# str_res[idx_dst] = str[idx_src];
		or $10, $0, $16		# $10 <- @
		addu $10, $10, $9		# $10 <- &(str[idx_src])
		lbu $11, 0($10)			# $11 <- str[idx_src]
		or $10, $0, $16		# $10 <- @
		addiu $10, $10, 5		# $10 <- &(str_res)
		addu $10, $10, $8		# $10 <- &(str_res[idx_dst])
		sb $11, 0($10)			# $11 -> str_res[idx_dst]
			
		# idx_dst += 1;
		addiu $8, $8, 1
		
		# idx_src -= 1
		addiu $9, $9, -1
		
		j loop2		
	
end_loop2:

	
	# printf("%s", str_res);
	ori $2, $0, 4
	or $4, $0, $16
	addiu $4, $4, 5
	syscall
	
	
	
	# Epilogue
	addiu $29, $29, 12
	
	#exit
	ori $2, $0, 10
	syscall

# TESTS
# hello -> olleh
# azerty -> ytreza