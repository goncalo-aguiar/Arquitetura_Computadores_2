#include <detpic32.h>    


void delay(int ms){
    for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}
    

int main(void){ 

    char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};

    TRISB = TRISB | 0x000F;
    TRISB = TRISB & 0x80FF;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 =1;
    LATDbits.LATD6 =0;
    int escolha;
    while(1){
        escolha = PORTB & 0x000F;
        LATB = (LATB & 0x80FF) | (display7Scodes[escolha]<< 8) ;

    }


}