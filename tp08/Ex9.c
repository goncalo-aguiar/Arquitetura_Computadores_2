#include <detpic32.h> 


void putc(char byte2send)    {
                            // wait while UTXBF == 1
                            // Copy byte2send to the UxTXREG register

    while(U2STAbits.UTXBF==1);
	U2TXREG=byte2send;
}



void delay(int ms){
  for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}

char getc(void) {       
    // If OERR == 1 then reset OERR
    // Wait while URXDA == 0
    // If FERR or PERR then 
    //   read UxRXREG (to discard the character) and return 0  
    // else       
    //Return U1RXREG

    if(U2STAbits.OERR == 1) U2STAbits.OERR = 0;
    while(U2STAbits.URXDA==0);
    char discard = 0;
    if (U2STAbits.FERR ==1|| U2STAbits.PERR ==1)
    {
        discard =  U2RXREG;
        return 0;
    }
    return U2RXREG;
} 

void configUart(unsigned int baud, char parity, unsigned int stopbits) {
       
    U2MODEbits.BRGH=0;  // Neste caso é 0 pq quero escolher 16
	
	if(baud<600 ||  baud>115200) baud = 115200;
    U2BRG=((PBCLK+8*baud)/(16*baud))-1;
	
    switch(parity){
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
    configUart(115200,'N',1);
        // default "pterm" parameters
     while(1)       {
        putc( getc() );
    } 
} 
