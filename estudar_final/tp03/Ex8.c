#include <detpic32.h>   


int main(void){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    TRISB = TRISB & 0x80FF;
    TRISB = TRISB | 0x000F;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1){
        int aux = PORTB & 0x000F;
        LATB = (LATB & 0x80FF) | (display7Scodes[aux] << 8);

    }

}