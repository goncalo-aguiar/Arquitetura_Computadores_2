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
void puts(char *str)    {
           // use putc() function to send each charater ('\0' should not           //  be sent)
    int i = 0;
    while(str[i] != '\0'){
        putc(str[i]);
        i++;
    }
    
}

int main(void)    {
           // Configure UART2 (115200, N, 8, 1)
    U2MODEbits.BRGH = 0;
    U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate
    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN=1;    // receiver e sender
	U2STAbits.URXEN=1;    //

    U2MODEbits.ON=1;    // ativar uart2
    while(1)       {
        puts("String de teste\n");          // wait 1 s
        delay(1000); 
    }
    
}