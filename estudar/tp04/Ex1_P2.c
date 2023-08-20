#include <detpic32.h>    


void delay(int ms){
    for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}

void send2displays(unsigned char value){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    

    int digit_low = value & 0x0F;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    LATB = (LATB & 0x80FF) | (display7Scodes[digit_low]<<8); 
    delay(10);

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;
    int digit_high = value >> 4; 
    LATB = (LATB & 0x80FF) | (display7Scodes[digit_high]<<8);   
    delay(10);

}
    

int main(void){ 

    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;
    int i =0;
    int contador =0;
    for(i=0;i<512;i++){
        send2displays(contador);
        contador++;
        delay(200);
    }

    return 0;




}


