.data
	ch: .asciiz "abc"
	
.text
	lui $16, 0x1001 	# @data -> $16
	lui $17, 0x1001 	# @data -> $17
	ori $9, $0, 0		# $9 <- 0
	ori $10, $0, 0x00	# $10 <- 0x00
	
loop:	
	lb $18, 0($17)		# $18 <- M($16 + $9 * 0x1)
	beq $18, $10 , end_loop	# $18 == $10 | pc <- end_loop
	addiu $9, $9, 1		# $9 = $9 + 1
	addiu $17, $17, 0x1	# $17 = $17 + 0x1 (taille d'un byte)
	j loop


end_loop:
	ori $2, $0, 1
	or $4, $0, $9		
	syscall			# Affiche $9
	
	ori $2, $0, 10
	syscall			# Fin de program