.data

.text
	# Lecture entier 
	ori $2, $0, 5
	syscall
	or $16, $0, $2			# $16(a) <- $2(input)
	
	# Lecture entier 
	ori $2, $0, 5
	syscall
	or $17, $0, $2			# $17(b) <- $2(input)
	
	# tmpa = a
	or $8, $0, $16			# $8(tmpa) <- $16(a)
	
	# tmpb = b
	or $9, $0, $17			# $9(tmpb) <- $17(b)
	
	loop:
		# Fin de boule: tmpa == tmpb
		beq $8, $9, end_loop
		
		# else:  tmpa <= tmpb
		slt $10, $9, $8		 # $10=1 si tmpb<tmpa, tmpb >= tmpa
		beq $10, $0, else
		
		# tmpa = tmpa - tmpb
		subu $8, $8, $9
		j end_if_else 
		
	else:
		# tmpb = tmpb - tmpa
		subu $9, $9, $8	
		
	end_if_else:
		
		j loop
		
end_loop:
	
	# Affichage tmpa
	ori $2, $0, 1
	or $4, $0, $8
	syscall
	
	# Exit
	ori $2, $0, 10
	syscall