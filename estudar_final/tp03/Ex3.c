#include <detpic32.h>   


void delay(int ms){
    int i =0;
    for ( i = 0; i < ms; i++)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000){

        }
    }
    
}

int main(void){
    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5= 0;
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;

    char carater;
    while(1){
         carater = getChar();

        switch (carater)
        {
        case 'a':
            LATB = (LATB & 0x80FF) | (0x0001 << 8);
            break;
        case 'b':
            LATB = (LATB & 0x80FF) | 0x0002 << 8;
            break;
        case 'c':
            LATB = (LATB & 0x80FF) | 0x0004 << 8;
            break;
        case 'd':
            LATB = (LATB & 0x80FF) | 0x0008 << 8 ;
            break;
        case 'e':
            LATB = (LATB & 0x80FF) | 0x0010 << 8;
            break;
        case 'f':
            LATB = (LATB & 0x80FF) | 0x0020 << 8;
            break;
        case 'g':
            LATB = (LATB & 0x80FF) | 0x0040 << 8;
            break;
        }

    }
}