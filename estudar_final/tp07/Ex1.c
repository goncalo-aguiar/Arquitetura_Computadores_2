#include <detpic32.h>

int main(void){

    U2MODEbits.BRGH = 0;
    U2BRG = (20000000 + 8 * 115200) / (16 *115200)) – 1 ;

    U2MODEbits.PDSEL = 0; 
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN =1;  //receiver e transmiter ON
    U2STAbits.URXEN =1;

    U2MODEbits.ON=1;    // ativar uart2
}