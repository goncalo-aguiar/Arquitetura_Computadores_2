#include <detpic32.h>

volatile int voltage = 0;   // Global variable 

void setPWM(unsigned int dutyCycle)    {       // duty_cycle must be in the range [0, 100]       
       
    OC1CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation    
    OC1RS = (dutyCycle*50000)/100;       // Ton constant    
    OC1CONbits.ON = 1;   // Enable OC1 module   
} 

unsigned char toBcd(unsigned char value)       {    
   
   
  
    return ((value / 10) << 4) + (value % 10);
}
void send2displays(unsigned char x){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static int displayFlag = 0;
    char dh = display7Scodes[x >>4];
    char dl = display7Scodes[x  & 0x0F];
    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (dl << 8) ;
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (dh << 8) ;
    }
    
    displayFlag = !displayFlag;
}

void _int_(4) isr_t1(void)  {
    AD1CON1bits.ASAM = 1;     // Start conversion
    IFS0bits.T1IF =0;
}                                   

void _int_(12) isr_t3(void)  {
    send2displays(toBcd(voltage));
    IFS0bits.T3IF =0;
}   

void _int_(27) isr_adc(void)  {
    int *p = (int*)(&ADC1BUF0);
    int media = 0;
    int i;
    for ( i = 0; i < 8; i++)
    {
        media = media + p[i*4];
    }
    voltage = (media/8)*33/1023;
    IFS1bits.AD1IF =0;
} 

int main(void){

    TRISB = TRISB & 0x80FF;
    TRISB = TRISB | 0x0003;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD0 = 0;


    TRISBbits.TRISB4 = 1;     // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)    
    AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this                              
                                //  mode an internal counter ends sampling and                              
                                //  starts conversion    
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter                              
                                //  interrupt is generated. At the same time,                              
                                //  hardware clears the ASAM bit    
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)    
    AD1CON2bits.SMPI = 8-1;  // Interrupt is generated after XX samples                              
                                //  (replace XX by the desired number of                              
                                //  consecutive samples)    
    AD1CHSbits.CH0SA = 4;     
                                // replace x by the desired input                               
                                //  analog channel (0 to 15)    
    AD1CON1bits.ON = 1;       
                                // Enable A/D converter                              
                                 //  This must the last command of the A/D                             
                                    //  configuration sequence 
    IFS1bits.AD1IF =0;
    IEC1bits.AD1IE =1;
    IPC6bits.AD1IP =2;

    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR1 = 19531;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0;            // Reset timer T2 count register
    T1CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                         //  timer configuration sequence)
    
    IFS0bits.T1IF =0;
    IEC0bits.T1IE =1;
    IPC1bits.T1IP =2;
    
    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 50000;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;            // Reset timer T2 count register
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the
                         //  timer configuration sequence)

    IFS0bits.T3IF =0;
    IEC0bits.T3IE =1;
    IPC3bits.T3IP =2;
    
    
    EnableInterrupts();

    while(1){
        int x = PORTB & 0x0003;
        switch (x)
        {
        case 0:
            IEC0bits.T1IE =1;
            setPWM(0);
            break;
        
        case 1:
            IEC0bits.T1IE =0;
            setPWM(100); 
            break;
        
        default:
            IEC0bits.T1IE =1;
            int dutyCycle = voltage * 3;             
            setPWM(dutyCycle); 
            break;
        }

    }
}