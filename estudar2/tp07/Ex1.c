#include <detpic32.h> 


void delay(int ms){
  for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}

int main(void)    {
           // Configure Timer T3 (2 Hz with interrupts disabled)

    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 39063;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T2 count register
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                             //  timer configuration sequence)
    while(1)       { 
                    // Wait until T3IF = 1 
                    // Reset T3IF 
        while(IFS0bits.T3IF==0);
        putChar('.');
        IFS0bits.T3IF=0;

    } 
} 