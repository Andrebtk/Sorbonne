.data
	chaine: .space 11		# @ = 0x10010000
.text
	# Prologue
	# i=0($29), nb=4($29), r=8($29), nbzero=12($29)
	addiu $29, $29, -16		# Alloue 4 int
	
	# scanf("%d", &nb);
	ori $2, $0, 5
	syscall
	or $9, $0, $2		# $9 -> nb
	
	
	lui $16, 0x1001		# $16 <- chaine	
	
	#chaine[10] = 0
	sb $0, 10($16)		# 0 -> @(chain[10])
	
	ori $8, $0, 9		# $8(i) <- 9
	ori $10, $0, 10		# $10 <- 10
	ori $11, $0, 0		# $11 (r) <- 0

	
	loop:
		# fin de boucle:  i < 0
		bltz $8, end_loop
		
		# r = nb % 10;
		div $9, $10		# HI <- nb % 10
		mfhi $11		# $11(r) <- nb % 10
		
		# nb = nb / 10
		mflo $9			# $10 <- nb / 10

		
		# chaine[i] = r + 0x30;
		addu $12, $16, $8	# $12 <- @(chaine[i])
		addiu $11, $11, 0x30	# r <- r + 0x30
		sb $11, 0($12)		# chaine[i] <- r
		
		
		#i -= 1
		addiu $8, $8, -1		# i -=  1	
		j loop
end_loop:

	# printf("%s", chaine);
	ori $2, $0, 4
	lui $4, 0x1001
	syscall
	
	ori $2, $0, 11
	or $4, $0, 0x0A
	syscall
	
	
	ori $12, $0, 0		# $12(nbzero) <- 0 
	ori $8, $0, 0		# $8(i) <- 0
	ori $13, $0, 9		# $13 <- 9
	ori $14, $0, 0x30	# $14 <- 0x30
	
	loop2:
		# fin de boucle: i >= 9 || chaine[i] != 0x30
		# i >= 9
		slt $10, $8,  $13		# $10=1 si 9 < i
		beq $10, $0, end_loop2
		
		# chaine[i] != 0x30
		addu $17, $16, $8		# $17 <- @(chain[i])
		lbu $15, 0($17)			# $15 <- chain[i]
		bne $15, $14, end_loop2
		
		
		addiu $12, $12, 1		# nbzero += 1;
		addiu $8, $8, 1			# i++
		j loop2
		
	
end_loop2:
	
	# printf("%d", nbzero);
	ori $2, $0, 1
	or $4, $0, $12
	syscall
	
	ori $2, $0, 11
	or $4, $0, 0x0A
	syscall
	
	ori $8, $0, 0		# $8(i) <- 0
	ori $13, $0, 10		# $13 <- 10
	subu $13, $13, $12	# $13 <- 10 - nbzero
	addiu $13, $13, 1	# $13 <- $13 + 1
	
	loop3:
		# fin de boucle: i >= (10 - nbzero + 1)
		slt $10, $8, $13		# $10=0 si i >= (10 - nbzero + 1)
		beq $10, $0, end_loop3
		
		# chaine[i] = chaine[i + nbzero]
		addu $14, $8, $12	# $14 <- i + nbzero
		addu $17, $16, $14	# $17 <- @(chaine[i+nbzero)
		lbu $10, 0($17)		# $10 <- chaine[i+nbzero]
		addu $17, $16, $8	# $17 <- @chaine[i]
		sb $10, 0($17)		# $10 -> chaine[i]
		
		# i += 1
		addiu $8, $8, 1
		j loop3
	
end_loop3:

	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	
	# Epilogue 
	addiu $29, $29, 16
	
	# Exit
	ori $2, $0, 10
	syscall