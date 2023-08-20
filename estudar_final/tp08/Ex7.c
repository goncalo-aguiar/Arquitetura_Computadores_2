#include <detpic32.h>


#define  DisableUart2RxInterrupt()    IEC1bits.U2RXIE = 0    
#define  EnableUart2RxInterrupt()     IEC1bits.U2RXIE = 1
#define  DisableUart2TxInterrupt()    IEC1bits.U2TXIE = 0
#define  EnableUart2TxInterrupt()     IEC1bits.U2TXIE = 1

#define BUF_SIZE     8   
#define INDEX_MASK   7

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
    rxb.head = 0;
    rxb.tail = 0;
    rxb.count= 0;
    int i=0;
    for ( i = 0; i < BUF_SIZE; i++)
    {
        rxb.data[i]= 0;
    }
    

}    
void comDrv_flushTx(void)    {       
    // Initialize variables of the transmission buffer    
    txb.head = 0;
    txb.tail = 0;
    txb.count = 0;
    int i=0;
    for ( i = 0; i < BUF_SIZE; i++)
    {
        txb.data[i]= 0;
    }
    
}

void comDrv_putc(char ch){
    while(txb.count == BUF_SIZE);

    txb.data[txb.tail] = ch;
    txb.tail = (txb.tail + 1) & INDEX_MASK;
    
    DisableUart2TxInterrupt();
    txb.count = txb.count + 1;
    EnableUart2TxInterrupt();
}


void comDrv_puts(char *s) {
    int i = 0;
    while (s[i]!= '\0')
    {
        comDrv_putc(s[i]);
        i++;
    }
    
}

void _int_(32) isr_UART(void)  {
    
    if(IFS1bits.U2TXIF ==1){
        if(txb.count > 0){
            U2TXREG = txb.data[txb.head];
            txb.head = (txb.head + 1) & INDEX_MASK;
            txb.count = txb.count -1;
        }
        if(txb.count == 0) DisableUart2TxInterrupt();
    }
    IFS1bits.U2TXIF =0;
}  
void ConfigUart(unsigned int baud,char parity,int stopbits){

    U2MODEbits.BRGH = 0;
    U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;

    switch (parity)
    {
    case 'N':
        U2MODEbits.PDSEL = 0; 
        break;
    case 'E':
        U2MODEbits.PDSEL = 1; 
        break;
    case 'O':
        U2MODEbits.PDSEL = 2; 
        break;
    }
    
    U2MODEbits.STSEL = stopbits-1;

    U2STAbits.UTXEN =1;  //receiver e transmiter ON
    U2STAbits.URXEN =1;
    U2MODEbits.ON=1;    // ativar uart2

    IPC8bits.U2IP = 2;  // configure priority of A/D interrupts 
    IFS1bits.U2TXIF = 0;  // clear A/D interrupt flag 
    IFS1bits.U2RXIF = 0;  // clear A/D interrupt flag 
    IEC1bits.U2TXIE = 1;  // enable A/D interrupts  
    IEC1bits.U2RXIE = 1;  // enable A/D interrupts  
}

int main(void){
    ConfigUart(115200,'N',1);
    comDrv_flushRx();       
    comDrv_flushTx();       
    EnableInterrupts();       
    while(1){
    comDrv_puts("Teste do bloco de transmissao do device driver!...");
    } 
    return 0;  
}