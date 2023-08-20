
	.data
	.text
	.globl main
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)

	
	li $t0,0
	li $t1,1
while:
	bne $t1,1,endw
	
	li $a0,5000
	jal delay
while1:
	li $v0,11
	syscall
	move $t2,$v0
	bge $t2,200000,endw1
	

	j while1
endw1:
	li $v0,12
	syscall
	addi $t0,$t0,1
	li $t3,4
	sll $t3,$t3,16
	li $t4,10
	or $t3,$t3,$t4
	move $a0,$t0
	move $a1,$t3
	li $v0,6
	syscall
	li $v0,3
	li $a0,'\r'
	syscall
	j while
endw:
	li $v0,0
	
	
	lw $ra,0($sp)
	addiu $sp,$sp,4

	jr $ra
	
	
	.data
	.text
	
delay:
	move $t8,$a0
for:
	ble $t8,0,endfor
	li $v0,12
	syscall
whiledelay:
	li $v0,11
	syscall
	bge $v0,20000,endwdelay
	j whiledelay
endwdelay:
	
	addiu $t8,$t8,-1
	j for
endfor:



	
	jr $ra
