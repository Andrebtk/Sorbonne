.data
	ch: .asciiz "Bonjour toi"

.text
	lui $16, 0x1001		# $16 <- @data
	lui $17, 0x1001		# $17 <- @data
	xor $8, $8, $8		# $8 (taille chaine) <- 0
	ori $9, $0, 0x00	# $9 <- 0x00
	loop:
		lb $10, 0($17)		# $10 <- ch[i]
				
		# ch[i] = '\0', fin de boucle
		beq $10, $9, end_loop
		addiu $17, $17, 0x1	# $17 += 0x1 (taille d'un caractere)
		addiu $8, $8, 1		# $8 <- $8 + 1
		
		j loop 

end_loop:	
	ori $2, $0, 1
	or $4, $0, $8
	syscall
	
	# Fin de programme
	ori $2, $0, 10
	syscall