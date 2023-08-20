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
void send2displays(unsigned char value){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static int displayFlag = 0;
    putChar(' ');
    printInt10(value);
    putChar('\n');
    char dh = display7Scodes[value >> 4];
    char dl = display7Scodes[value & 0x000F];
    if(displayFlag==0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (dl << 8) ;
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (dh << 8) ;
    }
    displayFlag = !displayFlag;


    

}

int main(void){
    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;
    int contador = 0;
    while(1){
        if(contador==255) contador =0;
        printInt10(contador);
        send2displays(contador);
        contador++;
        delay(50);
       
    }
}