	.data
	.text
	.globl delay
delay:
	move $t10,$a0
for:
	ble $t10,0,endfor
	li $v0,12
	syscall
whiledelay:
	li $v0,11
	syscall
	bge $v0,20000,endwdelay
	j whiledelay
endwdelay:
	
	addiu $t10,$t10,-1
	j for
endfor:



	
	jr $ra
