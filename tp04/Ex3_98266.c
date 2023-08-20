#include <detpic32.h>   

int main(void){ 

    TRISB = TRISB & 0x00FF;

    TRISD = TRISD & 0xFF9F;

    LATDbits.LATD6 = 0;         
    LATDbits.LATD5 = 1; 


    
    while(1){
        int c = getChar();

        switch(c){
            case 'a':
            case 'A':
                LATB = (LATB & 0x00FF) | 0x0100; 
                break;
            case 'b':
            case 'B':
                LATB = (LATB & 0x00FF) | 0x0200; 
                break;
            case 'c':
            case 'C':
                LATB = (LATB & 0x00FF) | 0x0400;
                break;
            case 'd':
            case 'D':
                LATB = (LATB & 0x00FF) | 0x0800;
                break;
            case 'e':
            case 'E':
                LATB = (LATB & 0x00FF) | 0x1000;
                break;
            case 'f':
            case 'F':
                LATB = (LATB & 0x00FF) | 0x2000;
                break;
            case 'g':
            case 'G':
                LATB = (LATB & 0x00FF) | 0x4000;
                break;
            default:
                LATB = (LATB & 0x00FF);
                break;

        }
    }

    return 0;



}


void delay(int ms){
    while(ms>0){
        resetCoreTimer();
        while(readCoreTimer()<20000)
            ms--;

        
    }
}