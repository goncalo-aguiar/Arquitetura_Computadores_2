#include <detpic32.h>

void putc(char byte2send) {    // wait while UTXBF == 1    // Copy byte2send to the UxTXREG register
    while(U2STAbits.UTXBF==1);
    U2TXREG = byte2send;
}
void _int_(32) isr_uart2(void)    {
    putc(U2RXREG);       // Clear UART2 rx interrupt flag
    IFS1bits.U2RXIF=0;
}

int main(void){
    U2MODEbits.BRGH = 0;
    U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate

    U2MODEbits.PDSEL = 0 ;
    U2MODEbits.STSEL = 0 ;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON =1;

    IFS1bits.U2RXIF=0;
    IEC1bits.U2RXIE =1;
    IPC8bits.U2IP =2;

    EnableInterrupts();

    while(1);

}