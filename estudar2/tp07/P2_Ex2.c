    


#include <detpic32.h>    
void setPWM(unsigned int dutyCycle)    {
    // duty_cycle must be in the range [0, 100]
    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 50000;         // Fout = 20MHz / (32 * (62499 + 1)) = 2 Hz
    TMR3 = 0;            // Reset timer T1 count register
    T3CONbits.TON = 1;   // Enable timer T1 (must be the last command of the
                         //  timer configuration sequence)

    OC1CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation
    OC1RS = (PR3*dutyCycle)/100;   // Evaluate OC1RS as a function of "dutyCycle"
    OC1CONbits.ON = 1;   // Enable OC1 module
    
}



 void _int_(12) isr_T3(void)       {                                                                                      
        
         putChar('.');       // Reset T3 interrupt flag
         IFS0bits.T3IF=0;          // Reset T1IF flag 
    }

int main(void)    {   
    setPWM(10);
    
    IPC3bits.T3IP = 2;  // configure priority of A/D interrupts 
    IFS0bits.T3IF = 0;  // clear A/D interrupt flag 
    IEC0bits.T3IE = 1;  // enable A/D interrupts 
    EnableInterrupts();

    while(1){

    }

   


}



