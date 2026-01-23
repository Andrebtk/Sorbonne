.data

.text
	ori $2, $0, 5
	syscall 		# $2 <- entier lu
	or $16, $0, $2		# $16 <- a
	
	ori $2, $0, 5
	syscall 		# $2 <- entier lu
	or $17, $0, $2		# $16 <- b
	
	or $8, $0, $16 		# $8(temp) <- a
	or $9, $0, $17		# $9(temp) <- b

loop:
	beq $8, $9, end_loop	# tmpA == tmpB, fin de boucle
	
 	# else -< tmpA <= tmpB
	slt $10, $9, $8		# $10 = 1 si  tmpB < tmpA
	beq $10, $0, else	# jump dans else
	
	subu $8, $8, $9		# tmpA = tmpA - tmpB
	j end_if 		# jump fin du if-else
else:
	subu $9, $9, $8		# tmpB = tmpB - tmpA
end_if:
	j loop			# jump debut de boucle
	

end_loop:

	ori $2, $0, 1		# $2 <- PGCD
	or $4, $0, $8
	syscall			# Affiche le PGCD
	
	ori $2, $0, 10
	syscall			# Fin de program