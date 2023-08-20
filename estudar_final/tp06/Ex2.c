#include <detpic32.h>

// Interrupt Handler    
void _int_(12) isr_adc(void)     {   
    putChar('.');    
    IFS0bits.T3IF = 0;           
}

int main(void){
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 39062;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T2 count register
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                         //  timer configuration sequence)

    IFS0bits.T3IF =0;
    IEC0bits.T3IE =1;
    IPC3bits.T3IP =2;
    
    EnableInterrupts();
    while(1){

    }
    return 0;
}