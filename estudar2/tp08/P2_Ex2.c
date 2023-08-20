
#include <detpic32.h> 
volatile unsigned char voltage = 0;
   // Global variable


void delay(int ms){
  for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}


unsigned char toBcd(int value){         
     return ((value / 10) << 4) + (value % 10);     
} 

void send2displays(unsigned char value){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;
    
    int digit_low = value & 0x0F;
    int digit_high = value >> 4; 
    
    if(displayFlag == 0){
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (display7Scodes[digit_high]<<8);   
        
    }
    else{
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (display7Scodes[digit_low]<<8); 
        
    }    
    displayFlag = !displayFlag;
    
  
    
    
    
    

}

void _int_(4) isr_T1(void)       {
              // Start A/D conversion
    
    AD1CON1bits.ASAM = 1;     // Start conversion
    

    IFS0bits.T1IF=0;          // Reset T1IF flag 
}

void _int_(12) isr_T3(void)       {
    
    
    
    send2displays(toBcd(voltage));                        // Send "voltage" variable to displays
    
                                                                                                  
    IFS0bits.T3IF=0;          // Reset T1IF flag 
}

void _int_(27) isr_adc(void)    { 
    
    
    int media = 0;
    int *p = (int *)(&ADC1BUF0); 
    int i =0;
    for ( i = 0; i < 8; i++)
    {
        media = media + p[i*4];  // Calculate buffer average (8 samples)
    }
    media = media/8;
    voltage=(media*33)/1023;// Calculate voltage amplitude
   
    
        
    IFS1bits.AD1IF = 0;    // Reset AD1IF flag
}
int main(void)    {
    unsigned int cnt = 0;     // Configure all (digital I/O, analog input, A/D module, interrupts)
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
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input
                              //  analog channel (0 to 15)
    AD1CON1bits.ON = 1;       // Enable A/D converter 
                              //  This must the last command of the A/D
                              //  configuration sequence 

    IPC6bits.AD1IP = 2;  // configure priority of A/D interrupts 
    IFS1bits.AD1IF = 0;  // clear A/D interrupt flag 
    IEC1bits.AD1IE = 1;  // enable A/D interrupts 

    IPC1bits.T1IP = 2;  // configure priority of A/D interrupts 
    IFS0bits.T1IF = 0;  // clear A/D interrupt flag 
    IEC0bits.T1IE = 1;  // enable A/D interrupts 

    IPC3bits.T3IP = 2;  // configure priority of A/D interrupts 
    IFS0bits.T3IF = 0;  // clear A/D interrupt flag 
    IEC0bits.T3IE = 1;  // enable A/D interrupts 

    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 50000;         // Fout = 20MHz / (32 * (62499 + 1)) = 2 Hz
    TMR3 = 0;            // Reset timer T1 count register
    T3CONbits.TON = 1;   // Enable timer T1 (must be the last command of the
                         //  timer configuration sequence)    

    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 19532;         // Fout = 20MHz / (32 * (62499 + 1)) = 2 Hz
    TMR1 = 0;            // Reset timer T1 count register
    T1CONbits.TON = 1;   // Enable timer T1 (must be the last command of the
                         //  timer configuration sequence)  




    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    EnableInterrupts();
                                // Global Interrupt Enable 
    while(1)       { 
        

    } 
return 0; 
} 