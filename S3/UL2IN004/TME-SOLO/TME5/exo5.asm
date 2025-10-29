.data
	n: .word 0xFEDCBA98	 # 0x10010000
	
	# 123 -> 6
	# -1 -> 32
	# 0xFEDCBA98 -> 20 
.text 
	lui $16, 0x1001		# $16 <- @data
	
	lw $8, 0($16)		# $8 <- n
	xor $9, $9, $9		# $9 <- 0 (cpt)
	xor $10, $10, $10	# $10 <- 0 (i)
	ori $11, $0, 32		# $11 <- 32
	
	for:
		#fin de boucle: i==32
		beq $10, $11, end_for
		
		andi $12, $8, 0x1	# $12 <- n & 0x1
		#Else: $12=0
		beq $12, $0, else
		addiu $9, $9, 1		# $9 <- $9 + 1	| cpt++
		else:	
			addiu $10, $10, 1	# $10 <- $10 +1 | i++
			srl $8, $8, 1
			j for
	
end_for:
	
	# Affichage $9 (cpt)
	ori $2, $0, 1
	or $4, $0, $9
	syscall
	
	
	# Fin de programme
	ori $2, $0, 10
	syscall