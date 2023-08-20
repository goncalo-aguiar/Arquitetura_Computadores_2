#include <detpic32.h>

void ConfigUart(unsigned int baud,char parity,int stopbits){

    U2MODEbits.BRGH = 0;
    U2BRG = (20000000 + 8 * baud) / (16 *baud)) – 1 ;

    switch (parity)
    {
    case 'N':
        U2MODEbits.PDSEL = 0; 
        break;
    case 'E':
        U2MODEbits.PDSEL = 1; 
        break;
    case 'O':
        U2MODEbits.PDSEL = 2; 
        break;
    }
    
    U2MODEbits.STSEL = stopbits-1;

    U2STAbits.UTXEN =1;  //receiver e transmiter ON
    U2STAbits.URXEN =1;

    U2MODEbits.ON=1;    // ativar uart2
}