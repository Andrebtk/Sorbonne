.data
	ch: .asciiz "monsecret"		# @ = 0x10010000
	ch2: .space 10			# @ + 10
	decalage: .byte 1		# @ + 20

.text
	# Prologue
	#0($29)=i, 4($29)=tmp
	addiu $29, $29, -5		# Alloue 5 octer (4-> int, 1 tmp)
	
	lui $16, 0x1001			# $16 <- @
	
	# printf("%s", ch);
	ori $2, $0, 4
	or $4, $0, $16
	syscall
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# cipher_cesar
	# int i = 0;
	ori $8, $0, 0			# $8(i) <- 0
	lb $10, 20($16)			# $10 <- decalage
	ori $18, $0, 26			# $18 <- 26
	
	loop:
		# Fin de boucle: ch[i] == 0
		addu $17, $16, $8	# $17 <- @(ch[i])
		lb $18, 0($17)		# $18 <- ch[i]
		beq $18, $0, end_loop
		
		# tmp = ch[i] - ’a’ + decal;
		or $9, $0, $18		# $9(tmp) <- ch[i]
		subiu $9, $9, 0x61	# $9(tmp) <- tmp - 'a'
		addu $9, $9, $10	# $9(tmp) <- ch[i] - ’a’ + decal
		
		# ch2[i] = ’a’ + (tmp % 26);
		div $9, $18		# HI <- tmp % 26
		mfhi $12		# $12 <- HI
		addiu $12, $12, 0x61	# $12 <- ’a’ + (tmp % 26)
		addiu $19, $16, 10	# $18 <- @ch2
		addu $19, $19, $8	# $18 <- @(ch2[i])
		sb $12, 0($19)		# $12 -> ch2[i]
		
		# i++;
		addiu $8, $8, 1
		j loop
		
	
end_loop:
	
	# printf("%s", ch2);
	ori $2, $0, 4
	addiu $4, $0, 10
	addu $4, $4, $16
	syscall
	
	# cipher_cesar2 
	
	# int i = 0;
	ori $8, $0, 1		# $8(i) <- 1
	
	loop2:
		# Fin de boucle: ch[i] == 0
		addu $17, $16, $8	# $17 <- @(ch[i])
		lb $18, 0($17)		# $18 <- ch[i]
		beq $18, $0, end_loop2
		
		# encode_char_cesar(src[i], decal);
		
		#tmp = (c - ’a’) + decal
		subu $9, $18, 0x61		# $9(tmp) <- ch[i] - 'a'
		addu $9, $9, $10		# $9(tmp) <- (c - ’a’) + decal
		
		# tmp = (’a’ + (tmp % 26));
		div $9, $18			# HI <- tmp % 26
		mfhi $12			# $12 <- HI
		addiu $9, $12, 0x61		# $9(tmp) <- (’a’ + (tmp % 26))
		
		# ch2[i] = tmp
		addiu $19, $16, 10	# $18 <- @ch2
		addu $19, $19, $8	# $18 <- @(ch2[i])
		sb $9, 0($19)		# $9 -> ch2[i]
		
		# i++
		addiu $8, $8, 1
		j loop2
		
end_loop2:
	
	# Affichage '\n'
	ori $2, $0, 11
	ori $4, $0, 0x0A
	syscall
	
	# printf("%s", ch2);
	ori $2, $0, 4
	addiu $4, $0, 10
	addu $4, $4, $16
	syscall
	
	
	# Epilogue
	addiu $29, $29, 5
	
	# Exit
	ori $2, $0, 10
	syscall
