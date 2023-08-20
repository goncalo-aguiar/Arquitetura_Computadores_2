#include <detpic32.h>

int main(void){
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 39062;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T2 count register
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                         //  timer configuration sequence)

    while(1){
        while( IFS0bits.T3IF == 0 );   // Wait while conversion not done 
        putChar('.');
        IFS0bits.T3IF = 0;


    }
}