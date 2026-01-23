.data
.text
	# Operations logiques
	ori $8, $0, 0x00FF 	# $8 = 0x000000FF
	ori $9, $0, 0xFFF0 	# $9 = 0x0000FFF0
	and $10, $9, $8 	# $10 = 0x000000F0
	xor $11, $9, $8 	# $11 = 0x0000FF0F
	xor $11, $11, $11 	# $11 = 0x00000000

	# Decalages
	ori $9, $0, 25 # $9 = 0x00000019
	sll $10, $9, 1 # $10 = 0x00000032
	sll $11, $9, 2 # $11 = 0x00000064
	sll $12, $9, 3 # $12 = 0x000000c8
	srl $10, $9, 1 # $10 = 0x0000000c
	srl $10, $9, 2 # $10 = 0x00000006
	srl $10, $9, 3 # $10 = 0x00000003
	addi $9, $0, -25  #9 = 0xffffffe7
	srl $10, $9, 1 # $10 = 0x7ffffff3
	srl $11, $9, 2 # $11 = 0x3ffffff9
	sra $12, $9, 1 # $12 = 0xfffffff3
	sra $13, $9, 2 # $13 = 0xfffffff9
	sra $14, $9, 3 # $14 = 0xfffffffc

	# Comparaisons
	ori $9, $0, 2
	ori $8, $0, 4
	slt $11, $8, $9 # $11 = 0x00000000
	slt $12, $9, $8 # $12 = 0x00000001

	ori $2, $0, 10
	syscall