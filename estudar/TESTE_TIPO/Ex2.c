#include <detpic32.h>    

void delay(int ms){
    for ( ; ms > 0; ms--)
    {
       resetCoreTimer();
       while (readCoreTimer()<20000);
       
       
    }
    
}

int main(void){

    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    char array[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};

    while(1){
        char numero = getChar();
        
        switch (numero)
        {
        case '0':
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 1;
            LATB = (LATB &  0x80FF) | (array[0] << 8);
            delay(10);
            break;
        
        case '1':

            
        
            
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
            LATB = (LATB &  0x80FF) | (array[1] << 8);
            delay(20);
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
            LATB = (LATB &  0x80FF) | (array[0] << 8);
            delay(10);
            
            break;
        

        case '2':
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
            LATB = (LATB &  0x80FF) | (array[2] << 8);
            delay(10);
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
            LATB = (LATB &  0x80FF) | (array[0] << 8);
            delay(10);
            break;

        case '3':
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
            LATB = (LATB &  0x80FF) | (array[3] << 8);
            delay(10);
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
            LATB = (LATB &  0x80FF) | (array[0] << 8);
            delay(10);
            break;
        
        default:
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 1;
            LATB = (LATB &  0x80FF) | (array[15] << 8);
            delay(1000);
            LATB = (LATB &  0x80FF);
            break;
        }
        delay(10);
    }


}