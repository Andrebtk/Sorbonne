.data
	str: .asciiz "abcde"		# @ <- 0x10010000
	str_res: .space 20		# @ + 5

.text
	lui $16, 0x1001			# $16 <- @
	
	# prologue
	addiu $29, $29, -4		# alloue 1 int
	
	# corp
	
	
	
	
	
	# printf("%s", str_res);
	ori $2, $0, 4
	or $4, $0, $16
	addiu $4, $4, 5
	syscall
	
	
	
	# Epilogue
	addiu $29, $29, 4
	
	#exit
	ori $2, $0, 10
	syscall
	