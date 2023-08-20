#include <detpic32.h> 

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

void putc(char byte2send)    {
                            // wait while UTXBF == 1
                            // Copy byte2send to the UxTXREG register

    while(U2STAbits.UTXBF==1);
	U2TXREG=byte2send;
}

void _int_(32) isr_uart2(void)    {
    putc(U2RXREG);       // Clear UART2 rx interrupt flag
    IFS1bits.U2RXIF = 0;
} 



int main(void)    {

    configUart(115200,'N',1);    // default "pterm" parameters
                                //  with RX interrupt enabled 
   
    IPC8bits.U2IP = 2;  // configure priority of A/D interrupts 
    IFS1bits.U2RXIF = 0;  // clear A/D interrupt flag 
    IEC1bits.U2RXIE = 1;  // enable A/D interrupts 

    EnableInterrupts();
    while(1);
}    



