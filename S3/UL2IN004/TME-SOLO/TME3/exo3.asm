.data

.text
	ori $9, $0, 84		# $9 <- 84
	ori $10, $0, 10		# $10 <- 10
	div $9, $10		# 84 / 10
	mflo $11		# $11 <- (84 / 10) = 8 
	mfhi $12		# $12 <- (84 % 10) = 4
	
	# Registre persistant
	or $16, $0, $9		# $16 <- 84
	or $17, $0, $10		# $17 <-10
	or $18, $0, $11		# $18 <- (84 / 10) = 8
	or $19, $0, $12		# $19 <- (84 % 10) = 4
	
	# Affichage quotient
	ori $2, $0, 1
	or $4, $0, $11  
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	
	# Affichage reste
	ori $2, $0, 1
	or $4, $0, $19  
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	mult $18, $17		#  8 * 10
	mflo $13		# $13 <- 8*10
	addu $13, $13, $12	# $13 <- 8*10 + 4
	
	# Affichage $13
	ori $2, $0, 1
	or $4, $0, $13
	syscall
	
	# exit
	ori $2, $0, 10
	syscall
	
	