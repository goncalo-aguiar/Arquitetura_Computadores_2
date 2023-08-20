    .data
str:.asciiz "AC2-Inicio"
    .text
    .globl main

main:
    li $v0,8
    la $a0,str
    syscall


    jr $ra
