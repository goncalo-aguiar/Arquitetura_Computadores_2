	.data
	.text
	.globl main
	
main:
do:
while1:	
	li $v0,1
	syscall
	move $t0,$v0

	bne $t0,0,endw1
	j while1
endw1:

if:
	beq $t0,'\n',endif
	li $v0,3
	move $a0,$t0
	syscall

endif:
	



while:
	bne $t0,'\n',do


	jr $ra
