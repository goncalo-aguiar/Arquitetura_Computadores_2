#include <detpic32.h>
void putc(char carater){
    while(U2STAbits.UTXBF ==1);
    U2TXREG = carater ;
}

void delay(int ms){
    int i =0;
    for ( i = 0; i < ms; i++)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000){

        }
    }
    
}
int main(void){
    U2MODEbits.BRGH =0;
    U2BRG = ((115200*8 + PBCLK) / (16*115200)) -1  ; 

    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON =1;

    while(1){
        putc('+');
        delay(1000);
    }
}