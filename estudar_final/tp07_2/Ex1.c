#include <detpic.h>
int main(void){
    U2MODEbits.BRGH =0;
    U2BRG = 115200;

    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON =1;

}