.data
	ch2: .space 20			# @ = 0x10010000
	N: .word 4			# @ + 20
	ch1: .ascii "Hello"		# @ + 24
	
.text
	# Prologue 
	addiu $29, $29, -4		# Alloue 4 octetq 
	
	# corp
	lui $16, 0x1001			# $16 <- @ | @ch2
	ori $8, $0, 0			# $8 <- 0 <- i
	lw $9, 20($16)			# $9 <- N
	addiu $11, $16, 24		# $11 <- @ch1
	loop:
		# Fin de boucle: i >= N
		slt  $10, $8, $9		# $10=0 si i>=N
		beq $10, $0, end_loop
		
		# ch2[i] = ch1[i]
		addu $12, $11, $8		# @(ch1[i])
		addu $14, $16, $8		# @(ch2[i])
		lbu $13, 0($12)			# $13 <- ch1[i]
		sb $13, 0($14)			# ch1[i] -> ch2[i]  
		
		
		addiu $8, $8, 1			# i += 1
		j loop
	
end_loop:
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	
	# Epilogue 
	addiu $29, $29, 4
	
	#exit
	ori $2, $0, 10
	syscall
	
