#include <detpic32.h> 
#define BUF_SIZE     8
#define INDEX_MASK   (BUF_SIZE – 1) 

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
    txb.count++:                               // Increment "count" variable
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