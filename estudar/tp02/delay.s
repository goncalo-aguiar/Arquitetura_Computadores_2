

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
endfor:



    jr $ra