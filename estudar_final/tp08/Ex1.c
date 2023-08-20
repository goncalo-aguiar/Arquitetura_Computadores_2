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


