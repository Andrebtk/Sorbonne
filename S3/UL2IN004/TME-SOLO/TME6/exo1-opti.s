.data
	chaine: .space 11		# @ = 0x1001000
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
		div $9, $10		# LO <- nb / 10
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
	
	
	# Epilogue 
	addiu $29, $29, 16
	
	# Exit
	ori $2, $0, 10
	syscall