.data
	val: .word 45		# 0x10010000 = @
	tab: .word 12, 		# @ + 4
		78, 		# (@ + 4) + 4
		98,  
		5, 
		9, 
		-1
	
.text	
	lui $16,0x1001			# $16 <- @data
	or $17, $16, 0x4		# $17 <- @ + 4
	lw $8, 0($16)			# $8 <- val
	ori $9, $0, -1			# $9 <- -1
	ori $10, $0, 0			# $10 <- 0 (cpt)
	loop:
		lw $11, 0($17)		# $11 <- tab[i]
		
		# fin de boucle: tab[i] == -1
		beq $11, $9, end_loop
		
		# else: tab[i] > val 
		slt $12, $8, $11	# $12=1 si tab[i]<val, 0 si tab[i]>=val
		bne $12, $0, else
		addiu $10, $10, 1	# cpt = cpt + 1
		
		else:
			addiu $17, $17, 0x4	# i + 1
			j loop
	
end_loop:
	# Affichage $10 (cpt)
	ori $2, $0, 1
	or $4, $0, $10
	syscall 

	# Fin de programme
	ori $2, $0, 10
	syscall