    .equ SFR_BASE_HI, 0xBF88        
    
    .equ TRISE, 0x6100              
    .equ PORTE, 0x6110               
    .equ LATE,  0x6120    

    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB,  0x6060

    .data
    .text
    .globl main

main:
    addiu $sp,$sp,-4
    sw $ra,0($sp)
    li $t2,0
    
    lui $t0,SFR_BASE_HI
    
    lw $t1,TRISE($t0)
    andi $t1,$t1,0xFFFE
    sw $t1,TRISE($t0)

while:
    lw $t1,LATE($t0) 
    andi $t1,$t1,0xFFFE
    or $t1,$t1,$t2
    sw $t1,LATE($t0)
    
    li $a0,500
    jal delay

    xori $t2,$t2,1




    j while
endw:
    


    lw $ra,0($sp)
    addiu $sp,$sp,4
    jr $ra


    
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