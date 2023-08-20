
#include <detpic32.h> 

volatile unsigned char voltage = 0;   // Global variable  
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



// Interrupt Handler    
void _int_(27) isr_adc(void)// Replace VECTOR by the A/D vector                                     
                                // number - see "PIC32 family data                                      
                                // sheet" (pages 74-76)    
    {            
                              
                      
        int *p = (int *)(&ADC1BUF0); 
        int i;
        int media = 0;
        for(  i = 0; i < 8; i++ ) {
           media = media + p[i*4];
        }
        media =  (media/8)*33/1023;
        voltage = media;
        
        IFS1bits.AD1IF = 0;                 // Reset AD1IF flag    
         
    }

  
int main(void)    {  
unsigned int cnt = 0;       // Configure all (digital I/O, analog input, A/D module, interrupts)       

TRISB = TRISB & 0x80FF;
TRISDbits.TRISD5 = 0;
TRISDbits.TRISD6 = 0;

TRISBbits.TRISB4 = 1;     // RBx digital output disconnected    
AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)    
AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this                              
                          //  mode an internal counter ends sampling and                              
                          //  starts conversion    
AD1CON1bits.CLRASAM = 1;  
                          // Stop conversions when the 1st A/D converter                              
                          //  interrupt is generated. At the same time,                              
                          //  hardware clears the ASAM bit    
AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)    
AD1CON2bits.SMPI = 7;     // Interrupt is generated after XX samples                              
                          //  (replace XX by the desired number of                              
                          //  consecutive samples)    
AD1CHSbits.CH0SA = 4;     // replace x by the desired input                               
                          //  analog channel (0 to 15)    
AD1CON1bits.ON = 1;       // Enable A/D converter                              
                          //  This must the last command of the A/D                             
                          //  configuration sequence

                         // Configure interrupt system    
IPC6bits.AD1IP = 2;      // configure priority of A/D interrupts 
IFS1bits.AD1IF = 0;      // clear A/D interrupt flag 
IEC1bits.AD1IE = 1;      // enable A/D interrupts       
EnableInterrupts();       // Global Interrupt Enable       
while(1)        {          
        if(cnt % 25 == 0)   // 250 ms (4 samples/second)
        {                   
            AD1CON1bits.ASAM = 1;               // Start conversion 
            printInt(voltage, 10); 
            putChar('\n');

        }  
        
        send2displays(toBcd(voltage));                 // Send "voltage" variable to displays          
    
    cnt++;                  
    delay(10);// Wait 10 ms
}       
return 0;    
}    
    