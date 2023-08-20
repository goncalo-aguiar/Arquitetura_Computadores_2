#include <detpic32.h>    


    

int main(void){ 

    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD5 = 0;

    LATDbits.LATD5 =1;
    LATDbits.LATD6 =0;

    char carater;
    while(1){
        carater = getChar();

        switch(carater){
            case 'a':
            case 'A':
                LATB = (LATB & 0x80FF) | (1<<8);
                break;
            case 'b':
            case 'B':
                LATB = (LATB & 0x80FF) | (2<<8);
                break;
            case 'c':
            case 'C':
                LATB = (LATB & 0x80FF) | (4<<8);
                break;
            case 'd':
            case 'D':
                LATB = (LATB & 0x80FF) | (8<<8);
                break;
            case 'e':
            case 'E':
                LATB = (LATB & 0x80FF) | (16<<8);
                break;
            case 'f':
            case 'F':
                LATB = (LATB & 0x80FF) | (32<<8);
                break;
            case 'g':
            case 'G':
                LATB = (LATB & 0x80FF) | (64<<8);
                break;
        }
    }


}