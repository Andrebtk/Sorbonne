.data
	tab: .word 10, 15, 8, 79, 45, 76, 0
	
.text
	lui $16, 0x1001		# $16 <- tab
	lui $17, 0x1001		# $17 <- tab
	xor $8, $8, $8 		# $8 <- 0 (val_max)
	
	loop:
		lw $9, 0($17)		# $9 <- tab[i]
		# fin de boucle: $9 = 0
		beq $9, $0, end_loop
		
		# else: $9(tab[i]) <= $8(val_max)
		slt $10, $8, $9		# $10=1 si val_max < tab[i], sinon val_max >= tab[i]
		beq $10, $0, else
		or $8, $0, $9
		 
		else:
			addiu $17, $17, 0x4
			j loop	
	
	
	
end_loop:
	# Affichage $8 (val_max)
	ori $2, $0, 1
	or $4, $0, $8
	syscall
	
	
	
	# Fin de programme
	ori $2, $0, 10
	syscall