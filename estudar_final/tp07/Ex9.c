#include <detpic32.h>
void putc(char byte2send) {    // wait while UTXBF == 1    // Copy byte2send to the UxTXREG register
    while(U2STAbits.UTXBF==1);
    U2TXREG = byte2send;
}


char getc(void) {    // If OERR == 1 then reset OERR    // Wait while URXDA == 0    // Return U2RXREG
    if(U2STAbits.OERR ==1 )U2STAbits.OERR =0;
    while(U2STAbits.URXDA==0); 
    return U2RXREG;

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
        putc(getc());
    }
}

