.data	
	.align 2
	p: .space 4	# @ 0x10010000
	
	.align 2
	q: .space 4	# @ + 4

.text
	lui $16, 0x1001	# @ data
	
	# Lire un entier 
	ori $2, $0, 5
	syscall 
	or $17, $0, $2		# $17 <- input(p)
	
	# Lire un entier 
	ori $2, $0, 5
	syscall
	or $18, $0, $2		# $18 <- input(q)
	
	
	sw $17, 0($16)		# $17 -> p
	sw $18, 4($16)		# $18 -> q
	ori $19, $0, 0		# $19 <- 0
	
	loop:	
		# fin de boucle p >= q
		slt $8, $17, $18	#$8=1 si p < q sinon $8=0
		beq $8, $0, end_loop
		
		add $19, $19, $17	# $19 <- $19 + p
		addiu $17, $17, 1	# p = p + 1
		j loop
end_loop:
	
	#Affichage $19 (la somme)
	ori $2, $0, 1
	or $4, $0, $19
	syscall	
	
	# Exit
	ori $2, $0, 10
	syscall