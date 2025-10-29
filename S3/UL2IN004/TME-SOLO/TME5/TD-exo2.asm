.data
	a: .word -5	# 0x10010000
	b: .word 3	# 0x10010004

.text
	lui $16, 0x1001		# $16 <- @data
	lw $8, 0($16)		# $8 <- a
	lw $9, 4($16)		# $9 <- b
	
	# else: a != 0
	bne $8, $0, else
	addu $8, $8, $9		# $8 <- a + b
	sw $8, 0($16)		# $8 -> a
	j end_if
	
	
else:	
	subu $8, $8, $9		# $8 <- a + b
	sw $8, 0($16)		# $8 -> a
	
	
end_if:
	ori $2, $0, 10
	syscall	