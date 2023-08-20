#include <detpic32.h>    


void delay(int ms){
    for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}
    

int main(void){ 

    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1){
        LATDbits.LATD5 = !LATDbits.LATD5;
        LATDbits.LATD6 = !LATDbits.LATD6;

        int segment =1;
        int i=0;
        for ( i = 0; i < 7; i++)
        {
            LATB = (LATB & 0x80FF) | (segment <<8);
            segment = segment << 1;
            delay(500);
        }
        
    }



}