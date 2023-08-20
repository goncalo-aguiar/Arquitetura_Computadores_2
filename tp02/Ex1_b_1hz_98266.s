	.equ READCORETIMER,11
	.equ RESETCORETIMER,2000000
	.equ PUTCHAR,'\r'
	.equ PRINTINT,3
	.data
	.text
	.globl main
main:
	li $t0,0
	li $t1,1
while:
	bne $t1,1,endw
while1:
	li $v0,11
	syscall
	move $t2,$v0
	bge $t2,20000000,endw1
	

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
	
	



	jr $ra
