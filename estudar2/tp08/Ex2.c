#include <detpic32.h> 

void delay(int ms){
  for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}

void putc(char byte2send)    {
           // wait while UTXBF == 1       // Copy byte2send to the UxTXREG register
           while(U2STAbits.UTXBF==1);
           U2TXREG = byte2send;
}
int main(void)    {
           // Configure UART2:
           // 1 - Configure BaudRate Generator
           // 2 – Configure number of data bits, parity and number of stop bits
           //     (see U1MODE register)
           // 3 – Enable the trasmitter and receiver modules (see register U1STA)
           // 4 – Enable UART2 (see register U1MODE)
    
    U2MODEbits.BRGH = 0;
    U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate
    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN=1;    // receiver e sender
	U2STAbits.URXEN=1;    //

    U2MODEbits.ON=1;    // ativar uart2

    while(1)       {
        putc('+');          // wait 1 s 
        delay(1000);
    }

} 
