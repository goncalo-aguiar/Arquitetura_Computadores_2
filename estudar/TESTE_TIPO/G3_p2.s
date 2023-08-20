    .data
    .equ SFR_BASE_HI,0xBF88
    
    .equ TRISE,0x6100
    .equ PORTE,0x6110
    .equ LATE,0x6120

    .equ TRISB,0x6040
    .equ PORTB,0x6050
    .equ LATB,0x6060
    .text
    .globl main

main:
    addiu $sp,$sp,-4
    sw $ra,0($sp)

    lui $t1,SFR_BASE_HI
    
    lw $t0,TRISE($t1)
    andi $t0,$t0,0xFFF0
    sw $t0,TRISE($t1)

    lw $t0,TRISB($t1)
    ori $t0,$t0,0x000F
    sw $t0,TRISB($t1)

    li $t4,0
while:
    lw $t0,LATE($t1)
    andi $t0,$t0,0xFFF0
    or $t0,$t0,$t4
    sw $t0,LATE($t1)
    li $a0,1000
    jal delay
    addi $t4,$t4,1
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
    ble $a0,0,endf
    li $v0,12
    syscall
while_delay:
    li $v0,11
    syscall
    bge $v0,20000,endw_delay


    j while_delay
endw_delay:

    addiu $a0,$a0,-1
    j for
endf:

    jr $ra
