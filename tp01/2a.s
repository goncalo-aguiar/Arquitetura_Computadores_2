	.data
	.text
	.globl main
	
main:

do:
	li $v0,2
	syscall
	move $t0,$v0
if:	beq $t0,'\n',endif
	li $v0,3
	move $a0,$t0
	syscall
endif:


while:
	bne $t0,'\n',do
	li $v0,0
	


	jr $ra
