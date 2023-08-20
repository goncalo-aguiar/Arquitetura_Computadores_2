#include <detpic32.h>

void setPWM(unsigned int dutycycle){
    OC1RS = ((50000+1)*dutycycle)/100;
    
}
void _int_(12) isr_t3(void)  {
    
    IFS0bits.T3IF =0;
} 
int main(void){
    TRISB = TRISB | 0x0003;

    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e Fout_presc = 625 KHz)    
    PR3 = 50000;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz    
    TMR3 = 0;            // Reset timer T2 count register    
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the                         
                         //  timer configuration sequence)
    OC1CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled    
    OC1CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation       
    OC1CONbits.ON = 1;   // Enable OC1 module
    
    IFS0bits.T3IF =0;
    IEC0bits.T3IE =1;
    IPC3bits.T3IP =2;
    
    printf("\n%d",OC1RS);
    EnableInterrupts();

    while(1){
        int x = (PORTB & 0x0003);

        printf("\n%d",OC1RS);
        switch (x)
        {
        case 0:
            setPWM(0);
            break;
        case 1:
            setPWM(30);
            break;
        
        case 2:
            setPWM(60);
            break;
        
        case 3:
            setPWM(100);
            break;
        
    
        }
    }

    return 0;
}