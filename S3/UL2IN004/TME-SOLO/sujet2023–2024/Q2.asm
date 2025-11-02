.data
	str: .asciiz "abcde"		# @ <- 0x10010000
	str_res: .space 20		# @ + 5

.text
	lui $16, 0x1001			# $16 <- @
	
	# prologue
	# 0($29)=c, 4($29)=n
	addiu $29, $29, -8		# alloue 2 int
	
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
	
	# printf("%s", str_res);
	ori $2, $0, 4
	or $4, $0, $16
	addiu $4, $4, 5
	syscall
	
	
	
	# Epilogue
	addiu $29, $29, 8
	
	#exit
	ori $2, $0, 10
	syscall
	