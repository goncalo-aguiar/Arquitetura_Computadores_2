    .data 
    .equ SFR_BASE_HI, 0xBF88        
    
    .equ TRISE, 0x6100              
    .equ PORTE, 0x6110               
    .equ LATE,  0x6120    

    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB,  0x6060
    .text
    .globl main

main:
    addiu $sp,$sp,-4
    sw $ra,0($sp)

    lui $t1,SFR_BASE_HI

    lw $t0,TRISE($t1)
    andi $t0,$t0,0xFFFE
    sw $t0,TRISE($t1)

    
    li $t9,0

while:

    lw $t0,LATE($t1)
    andi $t0,$t0,0xFFFE
    or $t0,$t0,$t9
    sw $t0,LATE($t1)
    xori $t9,$t9,1

    li $a0,500
    jal delay


    j while
endw:


    lw $ra,0($sp)
    addiu $sp,$sp,4
    jr $ra

    .data
    .text
    .globl delay
delay:

for:
    ble $a0,0,endfor
    li $v0,12
    syscall
while3:
    li $v0,11
    syscall
    bge $v0,20000,endw3

    j while3
endw3:

    addiu $a0,$a0,-1
    j for
endfor:



    jr $ra