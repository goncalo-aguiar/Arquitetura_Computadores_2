    .data
    .text
    .globl main

main:
addiu $sp,$sp,-4
sw $ra,0($sp)
li $t0,0
while:



while1:
    li $v0,11
    syscall
    bge $v0,20000,endw1

    j while1
endw1:
    li $v0,12
    syscall
    addi $t0,$t0,1
    move $a0,$t0
    li $a1,0x0004000A
    li $v0,6
    syscall
    li $a0,1000
    jal delay
    li $v0,3
    li $a0,'\r'
    syscall
    j while
endw:

    lw $ra,0($sp)
    addiu $sp,$sp,4
    jr $ra


    .data
    .text
    .globl delay

delay:
move $t9,$a0
for:
    ble $t9,0,endfor
    li $v0,12
    syscall
while3:
    li $v0,11
    syscall
    bge $v0,20000,endw3

    j while3
endw3:

    addiu $t9,$t9,-1
    j for
endfor:



    jr $ra