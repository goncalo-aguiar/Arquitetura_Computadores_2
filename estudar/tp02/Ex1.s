    .data
    .text
    .globl main

main:

li $t0,0
while:

while1:
    li $v0,11
    syscall
    bge $v0,200000,endw1

    j while1
endw1:
    li $v0,12
    syscall
    addi $t0,$t0,1
    move $a0,$t0
    li $a1,0x0004000A
    li $v0,6
    syscall
    li $v0,3
    li $a0,'\r'
    syscall
    j while
endw:



    jr $ra


