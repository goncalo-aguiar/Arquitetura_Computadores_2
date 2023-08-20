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
    lui $t1,SFR_BASE_HI

    lw $t0,TRISE($t1)   
    andi $t0,$t0,0xFFFE       # RE0 -> SAIDA
    sw $t0,TRISE($t1)

    lw $t0,TRISB($t1)
    ori $t0,$t0,0x0001      # RB0 -> Entrada
    sw $t0,TRISB($t1)

while:
    lw $t0,PORTB($t1)
    andi $t0,$t0,0x0001
   
    lw $t2,LATE($t1)
    andi $t2,$t2,0xFFFE

    or $t0,$t2,$t0
    xori $t0,$t0,0x0001

   
    sw $t0,LATE($t1)


    j while
endw:







    jr $ra