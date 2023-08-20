		.data
frase: 	.asciiz "\nIntroduza um numero (sinal e módulo): "
frase1: .asciiz "\nValor lido, em base 2: "
frase2:	.asciiz	"\nValor lido, em base 16: "
frase3:	.asciiz	"\nValor lido, em base 10 (unsigned): "
frase4:	.asciiz	"\nValor lido, em base 10 (signed): "
		.text
		.globl main
main:
while:
		li $v0,8
		la $a0,frase
		syscall
		li $v0,5
		syscall
		move $t0,$v0
		
		li $v0,8
		la $a0,frase1
		syscall
		li $v0,6
		move $a0,$t0
		li $a1,2
		syscall
		
		
		li $v0,8
		la $a0,frase2
		syscall
		li $v0,6
		move $a0,$t0
		li $a1,16
		syscall
		
		
		
		li $v0,8
		la $a0,frase3
		syscall
		li $v0,6
		move $a0,$t0
		li $a1,10
		syscall
		
		
		li $v0,8
		la $a0,frase1
		syscall
		li $v0,7
		move $a0,$t0
		syscall
	
	


		j while
endw:
		li $v0,0

		jr $ra


