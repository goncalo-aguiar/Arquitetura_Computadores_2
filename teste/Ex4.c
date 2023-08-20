#include <detpic32.h>

void putc(char byte2send){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte2send;
}

void puts(char *s){
    while(s[i] != '\0'){
        putc(s[i]);
        i++;
    }
}

void _int_(32) isr_uart(void){
    char val = PORTB & 0x000f;
    if (U2RXREG == 'P')
    {
        puts("Display=");
        puts(val);
        putc('\n');
    }
    if (U2RXREG == 'L')
    {
       LATEbits.LATE4 = !LATEbits.LATE4; 
    }
    
    
} 


int main(void){
    U2BRG = ((20000000+ 8*9600)/(16*9600))-1;
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON = 1;

    IFS1bits.U2RXIF = 0;
    IEC1bits.U2RXIE = 1;
    IPC8bits.U2IP = 2;
    EnableInterrupts();
    TRISEbits.TRISE4 = 0;
    LATEbits.LATE4 = 1;
    TRISB = TRISB | 0x000F;

    while(1){

    }
}