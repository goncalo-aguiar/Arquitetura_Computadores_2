#include <detpic32.h> 
static int contador =0;    
int main(void)    {       
    // Configure Timer T3 with interrupts enabled     
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 39062;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T3 count register
    T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the
                         //  timer configuration sequence)      
    
                    
                          // Configure interrupt system    
    IPC3bits.T3IP = 2;  // configure priority of A/D interrupts 
    IFS0bits.T3IF = 0;  // clear A/D interrupt flag 
    IEC0bits.T3IE = 1;  // enable A/D interrupts     
    EnableInterrupts(); 
      
    while(1){
        
    } 
    return 0;
}   
    
    
    void _int_(12) isr_T3(void)     { 
     // Replace VECTOR by the timer T3                                    
     //  vector number   
        contador++;
        if(contador%2==0){      
            putChar('.');  
        }     
        IFS0bits.T3IF =0; // Reset T3 interrupt flag
    } 