#include <detpic32.h> 

void putc(char byte2send)    {
                            // wait while UTXBF == 1
                            // Copy byte2send to the UxTXREG register

    while(U2STAbits.UTXBF==1);
	U2TXREG=byte2send;
}

void puts(char *str)    {
           // use putc() function to send each charater ('\0' should not           //  be sent)
    int i =0;
    while(str[i] != '\0'){
        
	    putc(str[i]);
        i++;
    
    }
}

void delay(int ms){
  for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
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
        // Configure UART2 (115200, N, 8, 1)   

    configUart(600,'N',1);
    while(1)       {          
        puts("String de teste\n");          // wait 1 s     
        delay(1000); 
    } 
}