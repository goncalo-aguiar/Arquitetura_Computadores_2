#include <detpic32.h> 

#define BUF_SIZE     8
#define INDEX_MASK   7 

#define  DisableUart2RxInterrupt()    IEC1bits.U2RXIE = 0 
#define  EnableUart2RxInterrupt()     IEC1bits.U2RXIE = 1
#define  DisableUart2TxInterrupt()    IEC1bits.U2TXIE = 0   
#define  EnableUart2TxInterrupt()     IEC1bits.U2TXIE = 1

typedef struct    { 
    unsigned char data[BUF_SIZE];
    unsigned int head; 
    unsigned int tail;  
    unsigned int count;
} circularBuffer;

volatile circularBuffer txb;    // Transmission buffer 
volatile circularBuffer rxb;    // Reception buffer 

void comDrv_flushRx(void)    {
    // Initialize variables of the reception buffer
    rxb.head =0 ;
    rxb.tail = 0;
    rxb.count = 0;
    int i;
    for ( i = 0; i < BUF_SIZE; i++)
    {
        rxb.data[i] = 0;
    }
    

}
void comDrv_flushTx(void)    { 
    // Initialize variables of the transmission buffer
    txb.head =0 ;
    txb.tail = 0;
    txb.count = 0;
    int i;
    for ( i = 0; i < BUF_SIZE; i++)
    {
        txb.data[i] = 0;
    }
    
}


void comDrv_putc(char ch)    {
    while(txb.count == BUF_SIZE){} // Wait while buffer is full 
    txb.data[txb.tail] = ch;       // Copy character to the transmission 
                                   //  buffer at position "tail" 
    txb.tail = (txb.tail + 1) & INDEX_MASK;// Increment "tail" index 
                                           //  (mod. BUF_SIZE)
    DisableUart2TxInterrupt();     // Begin of critical section
    txb.count++;                               // Increment "count" variable
    EnableUart2TxInterrupt();
                        // End of critical section
} 

void comDrv_puts(char *s)    {
    int i =0;
    while(s[i] != '\0'){
        comDrv_putc(s[i]);
        i++;
    }
}

char comDrv_getc(char *pchar)    {       // Test "count" variable (reception buffer) and return FALSE
    if (rxb.count == 0) return FALSE;    //  if it is zero 
    DisableUart2RxInterrupt();    // Begin of critical section  
    *pchar = rxb.data[head];// Copy character pointed by "head" to *pchar  
    rxb.count--;// Decrement "count" variable  
    rxb.head = (rxb.head - 1) & INDEX_MASK;// Increment "head" variable (mod BUF_SIZE)// Increment "head" variable (mod BUF_SIZE) 
    EnableUart2RxInterrupt();     //   End of critical section 
    return TRUE;
    
}



void _int_(32) isr_UART2(void)
{
    if(IFS1bits.U2TXIF == 1)// if U1TXIF is set
    {  
    if(txb.count > 0){ // if "count" variable (transmission buffer, txb) is greater than 0 
        U2TXREG = txb.data[txb.head];// Copy character pointed by "head" to U1TXREG register 
        txb.head = (txb.head + 1) & INDEX_MASK;// Increment "head" variable (mod BUF_SIZE)
        txb.count--;// Decrement "count" variable
        } 
    if(txb.count == 0) DisableUart2TxInterrupt(); // if "count" variable is 0 then 
    IFS1bits.U2TXIF = 0;// Reset UART2 TX interrupt flag 

    }
   
}  

void comDrv_config(unsigned int baud, char parity, unsigned int stopbits) {
       
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
    IPC8bits.U2IP = 2;  // configure priority of A/D interrupts 
    IFS1bits.U2TXIF = 0;  // clear A/D interrupt flag 
    IFS1bits.U2RXIF = 0;  // clear A/D interrupt flag 
    IEC1bits.U2TXIE = 1;  // enable A/D interrupts  
    IEC1bits.U2RXIE = 1;  // enable A/D interrupts  
    
    comDrv_config(115200,'N',1); // default "pterm" parameters
                                    //  with TX and RX interrupts disabled 
    comDrv_flushRx();
    comDrv_flushTx(); 
      
    EnableInterrupts();  
    while(1)  {
        comDrv_puts("\nTeste do bloco de transmissao do device driver!..."); 
    } 
    return 0;

}