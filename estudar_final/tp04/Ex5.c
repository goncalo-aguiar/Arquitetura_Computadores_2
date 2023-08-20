#include <detpic32.h>   

void delay(int ms){
    int i =0;
    for ( i = 0; i < ms; i++)
    {
        resetCoreTimer();
        while(readCoreTimer() < 20000){

        }
    }
    
}


void send2displays(unsigned char value){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static int displayFlag = 0;
    char dh = display7Scodes[value >> 4];
    char dl = display7Scodes[value & 0x000F];
    if(displayFlag==0){
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

unsigned char toBcd(unsigned char value)       {    
   
   
  
    return ((value / 10) << 4) + (value % 10);
}

int main(void){
    TRISB = TRISB & 0x80ff;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    TRISBbits.TRISB4 = 1;     // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this 
                            //  mode an internal counter ends sampling and  
                            //  starts conversion 
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter  
                             //  interrupt is generated. At the same time,  
                             //  hardware clears the ASAM bit 
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 16-1;  // Interrupt is generated after XX samples
                                //  (replace XX by the desired number of                              
                                 //  consecutive samples)
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input   
                                            //  analog channel (0 to 15) 
    AD1CON1bits.ON = 1;       // Enable A/D converter 
                            //  This must the last command of the A/D 
                        //  configuration sequence 

    while (1)
    {
       AD1CON1bits.ASAM = 1;     // Start conversion
       while( IFS1bits.AD1IF == 0 );   // Wait while conversion not done
       int *p = (int*)(&ADC1BUF0);
       int i=0;
       int media =0;
        for (i=0; i < 16; i++)
        {
            media = media + p[i*4];  
        }  
        int amplitude = ((media/16)*33)/1023;
        
        send2displays(toBcd(amplitude));
        IFS1bits.AD1IF = 0;
    }
    return 0;


}