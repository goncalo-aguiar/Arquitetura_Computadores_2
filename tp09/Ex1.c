#define  DisableUart2RxInterrupt()    IEC1bits.U2RXIE = 0 
#define  EnableUart2RxInterrupt()     IEC1bits.U2RXIE = 1
#define  DisableUart2TxInterrupt()    IEC1bits.U2TXIE = 0   
#define  EnableUart2TxInterrupt()     IEC1bits.U2TXIE = 1