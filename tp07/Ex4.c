#include <detpic32.h> 
int main(void){
              // Configure Timers T1 and T3 with interrupts enabled)          
              // Reset T1IF and T3IF flags
    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 39062;         // Fout = 20MHz / (32 * (62499 + 1)) = 2 Hz
    TMR1 = 0;            // Reset timer T1 count register
    T1CONbits.TON = 1;   // Enable timer T1 (must be the last command of the
                         //  timer configuration sequence)  

    T3CONbits.TCKPS = 5; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 62500;         // Fout = 20MHz / (32 * (62499 + 1)) = 2 Hz
    TMR3 = 0;            // Reset timer T1 count register
    T3CONbits.TON = 1;   // Enable timer T1 (must be the last command of the
                         //  timer configuration sequence)    
    
                    
                          // Configure interrupt system    
    IPC3bits.T3IP = 2;  // configure priority of A/D interrupts 
    IFS0bits.T3IF = 0;  // clear A/D interrupt flag 
    IEC0bits.T3IE = 1;  // enable A/D interrupts   
    
    IPC1bits.T1IP = 2;  // configure priority of A/D interrupts 
    IFS0bits.T1IF = 0;  // clear A/D interrupt flag 
    IEC0bits.T1IE = 1;  // enable A/D interrupts    
    EnableInterrupts();          
                         
              // Global Interrupt Enable          
        while(1){

        }   
}


void _int_(4) isr_T1(void)       {          
    // print character '1'          
    // Reset T1IF flag 
    putChar('1');       
    IFS0bits.T1IF =0; // Reset T3 interrupt flag      
    }       
void _int_(12) isr_T3(void)       {          
    // print character '3'          
    // Reset T3IF flag
    putChar('3');       
    IFS0bits.T3IF =0; // Reset T3 interrupt flag          
    }