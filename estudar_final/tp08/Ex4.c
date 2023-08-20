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
    for (int i = 0; i < BUF_SIZE; i++)
    {
        rxb.data[i]= 0;
    }
    

}    
void comDrv_flushTx(void)    {       
    // Initialize variables of the transmission buffer    
    txb.head = 0;
    txb.tail = 0;
    txb.count = 0;
    for (int i = 0; i < BUF_SIZE; i++)
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


comDrv_puts(char *s) {
    int i = 0;
    while (s[i]!= '\0')
    {
        comDrv_putc(s[i]);
    }
    
}