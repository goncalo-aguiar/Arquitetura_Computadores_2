#include <detpic32.h> 
void configUart(unsigned int baud, char parity, unsigned int stopbits) {}
       // Configure UART2:       
           // 1 - Configure BaudRate Generator
           
           // 2 – Configure number of data bits, parity and number of stop bits       
           //     (see U1MODE register)
           
           // 3 – Enable the trasmitter and receiver modules (see register U1STA)       
           // 4 – Enable UART2 (see register U1MODE)
    U2MODEbits.BRGH=0;  // Neste caso é 0 pq quero escolher 16
	U2BRG=((115200*8 + PBCLK) / (16*115200)) -1  ;       // contas para o baudarate
	
    switch(parity)
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
