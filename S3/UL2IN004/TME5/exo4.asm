.data
	val: .word 10
	tab: .word 78, 9, 45, 4, -1
	
.text
	lui $16, 0x1001		# @pc -> $16
	xor $9, $9, $9		# $9 <- 0
	ori $10, $0, -1
	
loop:
	lw $17, 4($16)		# $17 <- 78
	 
	#beq $10, 


	j loop
end_loop:

	ori $2, $0, 10
	syscall