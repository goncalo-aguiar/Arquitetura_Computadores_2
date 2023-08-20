
#include <detpic32.h>

void _int_(4) isr_t1(void)  {
    putChar('1');
    IFS0bits.T1IF =0;
}                                   

void _int_(12) isr_t3(void)  {
    putChar('3');
    IFS0bits.T3IF =0;
}   
int main(void){
    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR1 = 39062;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0;            // Reset timer T2 count register
    T1CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                         //  timer configuration sequence)
    
    IFS0bits.T1IF =0;
    IEC0bits.T1IE =1;
    IPC1bits.T1IP =2;
    
    T3CONbits.TCKPS = 5; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 62496;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T2 count register
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                         //  timer configuration sequence)

    IFS0bits.T3IF =0;
    IEC0bits.T3IE =1;
    IPC3bits.T3IP =2;
    
    
    EnableInterrupts();

    while(1){

    }
}