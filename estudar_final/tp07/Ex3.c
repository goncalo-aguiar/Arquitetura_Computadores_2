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
void putc(char byte2send) {    // wait while UTXBF == 1    // Copy byte2send to the UxTXREG register
    while(U2STAbits.UTXBF==1);
    U2TXREG = byte2send;
}



void puts(char *str)    {
           // use putc() function to send each charater ('\0' should not           //  be sent)
    int i =0;
    while(str[i] != '\0'){
	    putc(str[i]);
        i++;
    }
}
int main(void){
    U2MODEbits.BRGH = 0;
    U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate

    U2MODEbits.PDSEL = 0 ;
    U2MODEbits.STSEL = 0 ;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON =1;

    while(1){
        puts("olaaaaa2");
        delay(1000);
        
    }
}