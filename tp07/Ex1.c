#include <detpic32.h> 

int main(void)    {  
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 39063;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T3 count register
    T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the
                         //  timer configuration sequence)     
                         // Configure Timer T3 (2 Hz with interrupts disabled)      
    
    while(1)       {
        while(IFS0bits.T3IF == 0);     // Wait until T3IF = 1
                                      // Reset T3IF 
        IFS0bits.T3IF = 0;         
        putChar('.');      
    }   
                         
    return 0;                  
} 