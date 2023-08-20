#include <detpic.h>

void delay(int us){
    int i = 0;
    for ( i = 0; i < ms; i++)
    {
        resetCoreTimer();
        while (readCoreTimer() < 20);   
    }
    
}
void setPWM(unsigned int dutycicle){
    OC2RS = (PR3*dutycicle)/100;
}
int main(void){
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB0 = 1;


    T3CONbits.TCKPS = 1; // 1:32 prescaler (i.e Fout_presc = 625 KHz)    
    PR3 = 35712;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz    
    TMR3 = 0;            // Reset timer T2 count register    
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the                         
                         //  timer configuration sequence)
    OC2CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled    
    OC2CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation       
    OC2CONbits.ON = 1;   // Enable OC1 module

    while(1){
        int val = PORTB & 0x0009;
        switch (val)
        {
        case 1:
            setPWM(25);
            break;
        
        case 8:
            setPWM(70);
            break;
        
        }
        
        delay(250);
    }

}