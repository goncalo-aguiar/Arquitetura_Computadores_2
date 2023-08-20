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
    rxb.head =0;
    rxb.tail =0;
    rxb.count =0;
    int i = 0;
    for ( i = 0; i < BUF_SIZE; i++)
    {
        rxb.data[i]=0;
    }
    
}    
void comDrv_flushTx(void)    {       
    // Initialize variables of the transmission buffer    
    txb.head =0;
    txb.tail =0;
    txb.count =0;
    int i = 0;
    for ( i = 0; i < BUF_SIZE; i++)
    {
        txb.data[i]=0;
    }
}

void comDrv_putc(char c) {

    while(txb.count == BUF_SIZE);
    txb.data[txb.tail] = c;
    txb.tail = (txb.tail + 1) & INDEX_MASK;
    DisableUart2TxInterrupt();
    txb.count = txb.count +1; 
    EnableUart2TxInterrupt();

}

void comDrv_puts(char *s){
    int i =0;
    while(s[i] != '\0'){
        comDrv_putc(s[i]);
        i++;
    }
}

void _int_(32) isr_uart2(void)    { 

    if (IFS1bits.U2TXIF == 1)
    {
        if(txb.count > 0){
            U2TXREG = txb.data[txb.head];
            txb.head = (txb.head + 1) & INDEX_MASK;
            txb.count = txb.count -1;
        }
        
        if (txb.count ==0)
        {
           DisableUart2TxInterrupt();
        }
        IFS1bits.U2TXIF = 0;
    }
    if(IFS1bits.U2RXIF == 1){
        rxb.data[rxb.tail] = U2RXREG;
        rxb.tail = (rxb.tail +1) & INDEX_MASK;
        if (rxb.count == BUF_SIZE)
        {
            rxb.head = rxb.head +1;
        }
        else rxb.count = rxb.count +1;
        IFS1bits.U2RXIF = 0;
    }
    
    
}

char comDrv_getc(char *s){
    if(rxb.count == 0) return 0x30;
    *s = rxb.data[rxb.head];
    DisableUart2RxInterrupt();
    rxb.head = (rxb.head + 1) & INDEX_MASK;
    rxb.count= rxb.count -1;
    EnableUart2RxInterrupt();
    return 0x31;
}

int main(void){
    U2MODEbits.BRGH = 0;
    U2BRG = ((115200*8 + PBCLK) / (16*115200)) -1  ; 

    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON = 1;

    comDrv_flushRx();
    comDrv_flushTx();
    
    IFS1bits.U2TXIF =0;
    IEC1bits.U2TXIE =1;
    IFS1bits.U2RXIF =0;
    IEC1bits.U2RXIE =1;
    IPC8bits.U2IP = 2;


    EnableInterrupts();
    comDrv_puts("Teste do bloco de transmissao do device driver!..."); 
    char buf;
    while(1){
        if(comDrv_getc(&buf)== 0x31){
            comDrv_putc(buf);
        }
        
    }

}
