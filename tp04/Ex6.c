#include <detpic32.h>   

void delay(int ms);
int main(void)       { 
    LATDbits.LATD6 = 1; // display high active          
    LATDbits.LATD5 = 1; // display low active

    TRISB = TRISB & 0x80FF;     // configure RB8-RB14 as outputs 
    TRISD = TRISD & 0xFF9F;     // configure RD5-RD6 as outputs 
    

    int displayCodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    int i;
    for( i=0;i<sizeof(displayCodes)/4;i++){
        int x = displayCodes[i];
        x = x << 8;
        LATB = (LATB & 0x80FF) | x;
        delay(2000); 
    }
    return 0;

}


void delay(int ms){
    while(ms>0){
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
            ms--;

        
    }
}
