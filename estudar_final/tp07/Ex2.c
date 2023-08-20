#include <detpic32.h>

void delay(int ms){
    int i =0;
    for ( i = 0; i < ms; i++)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000){

        }
    }
    
}
void putc(char x){

    while(U2STAbits.UTXBF==1);
    U2TXREG = x;
}

int main(void){

    U2MODEbits.BRGH = 0;
    U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate

    U2MODEbits.PDSEL = 0; 
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN =1;  //receiver e transmiter ON
    U2STAbits.URXEN =1;

    U2MODEbits.ON=1;    // ativar uart2

    while(1){
        putc('+');
        delay(1000);
    }
}