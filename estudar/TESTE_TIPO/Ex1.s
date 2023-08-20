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
    lui $t1,SFR_BASE_HI

    lw $t0,TRISE($t1)
    andi $t0,$t0,0xFFE0
    sw $t0,TRISE($t1)

while:
    li $v0,2
    syscall
    li $t4,0
if:
    bne $v0,'0',if2
    lw $t0,LATE($t1)
    ori $t0,$t0,0x0001
    sw $t0,LATE($t1)
    addi $t4,$t4,1
if2:
    bne $v0,'1',if3
    lw $t0,LATE($t1)
    ori $t0,$t0,0x0002
    sw $t0,LATE($t1)
    addi $t4,$t4,1
if3:
    bne $v0,'2',if4
    lw $t0,LATE($t1)
    ori $t0,$t0,0x0004
    sw $t0,LATE($t1)
    addi $t4,$t4,1
if4:
    bne $v0,'3',if5
    lw $t0,LATE($t1)
    ori $t0,$t0,0x0008
    sw $t0,LATE($t1)
    addi $t4,$t4,1
if5:
    bge $t4,1,endif
    lw $t0,LATE($t1)
    ori $t0,$t0,0x0010
    sw $t0,LATE($t1)
    li $v0,12
    syscall
while1:
    li $v0,11
    syscall
    bge $v0,40000000,endw1
    j while1
endw1:

    
    lw $t0,LATE($t1)
    andi $t0,$t0,0xFFE0
    sw $t0,LATE($t1)
endif:

    j while
endw:
    li $v0,0

    jr $ra