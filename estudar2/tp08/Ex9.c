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

char getc(void)    {
        // If OERR == 1 then reset OERR
       // Wait while URXDA == 0
       // If FERR or PERR then
       //   read UxRXREG (to discard the character) and return 0 
       // else
       //   Return U1RXREG
    char discard;
    if(U2STAbits.OERR == 1){
        U2STAbits.OERR == 0;
        if(U2STAbits.FERR == 1 || U2STAbits.PERR == 1 ){
            discard = U2RXREG;
            return 0;
        }
        return U2RXREG;
    }
} 

#include <detpic32.h> 
void configUart(unsigned int baud, char parity, unsigned int stopbits) {}
       // Configure UART2:       
           // 1 - Configure BaudRate Generator
           
           // 2 – Configure number of data bits, parity and number of stop bits       
           //     (see U1MODE register)
           
           // 3 – Enable the trasmitter and receiver modules (see register U1STA)       
           // 4 – Enable UART2 (see register U1MODE)
    U2MODEbits.BRGH=0;  // Neste caso é 0 pq quero escolher 16
	U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate
	
    switch(parity)
        case 'N':
            U2MODEbits.PDSEL=00; // neste caso é 00 pq 
        break;
        case 'E':
            U2MODEbits.PDSEL=01; // neste caso é 00 pq 
        break;
        case 'O':
            U2MODEbits.PDSEL=10; // neste caso é 00 pq 
        break;
        default:
            U2MODEbits.PDSEL=00; // neste caso é 00 pq 
        break;

    }
    
	U2MODEbits.STSEL=stopbits-1;  // numero de stop bits

	U2STAbits.UTXEN=1;    // receiver e sender
	U2STAbits.URXEN=1;    //

	U2MODEbits.ON=1;    // ativar uart2
}





int main(void)    {
    configUart(115200,'N',1);    // default "pterm" parameters
        while(1)       {
            putc( getc() );
        }
    return 0;
}
