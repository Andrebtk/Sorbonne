.data
	chaine: .space 11		# @ = 0x1001000
.text
	# Prologue
	# i=0($29), nb=4($29), r=8($29), nbzero=12($29)
	addiu $29, $29, -16		# Alloue 4 int
	
	# scanf("%d", &nb);
	ori $2, $0, 5
	syscall
	sw $2, 4($29)		# $2 -> nb
	
	#chaine[10] = 0
	lui $16, 0x1001		# $16 <- chaine	
	sb $0, 10($16)		# 0 -> @(chain[10])
	
	ori $8, $0, 9		# $8 <- 9
	sw $8, 0($29)		# 9 -> i
	
	loop:
		# fin de boucle:  i < 0
		lw $8, 0($29)		# $8 <- i
		bltz $8, end_loop
		
		# r = nb % 10;
		lw $9, 4($29)		# $9 <- nb
		ori $10, $0, 10		# $10 <- 10
		div $9, $10		# HI <- nb % 10
		mfhi $10		# $10 <- nb % 10
		sw $10, 8($29)		# $10 -> r
		
		# nb = nb / 10
		lw $9, 4($29)		# $9 <- nb
		ori $10, $0, 10		# $10 <- 10
		div $9, $10		# LO <- nb / 10
		mflo $10		# $10 <- nb / 10
		sw $10, 4($29)		# $10 -> nb
		
		# chaine[i] = r + 0x30;
		lui $16, 0x1001		# $16 <- @
		lw $8, 0($29)		# $8 <- i
		addu $12, $16, $8	# $12 <- @(chaine[i])
		lw $10, 8($29)		# $10 <- r
		addiu $10, $10, 0x30	# r <- r + 0x30
		sb $10, 0($12)		# chaine[i] <- r
		
		
		# i -= 1
		lw $8, 0($29)		# $8 <- i
		addiu $8, $8, -1		# i -=  1
		sw $8, 0($29)		# $8 <- i		
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