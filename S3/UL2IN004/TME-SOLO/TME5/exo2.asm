.data
	
.text
	
	ori $2, $0, 5
	syscall
	or $17, $0, $2		# $17 <- a
	
	ori $2, $0, 5
	syscall
	or $18, $0, $2		# $18 <- b
	
	
	or $8, $0, $17		# $8 <- tmpa 
	or $9, $0, $18		# $9 <- tmpb 	
	
	loop:
		# tmpa == tmpb, fin de boucle
		beq $8, $9, end_loop
		
		# tmpa <= tmpb, saut else
		slt $10, $9, $8		# $10=1 si tmpb < tmpa
		beq $10, $0, else
		
		subu $8, $8, $9 
		j loop
		
		else:
			subu $9, $9, $8
			j loop
end_loop:
	
	# Affichage resultat
	ori $2, $0, 1
	or $4, $0, $8
	syscall
	
	# Exit
	ori $2, $0, 10
	syscall
