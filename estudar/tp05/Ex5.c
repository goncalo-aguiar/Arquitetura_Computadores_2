#include <detpic32.h>   

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
    
    //if(displayFlag == 0){
        //LATDbits.LATD5 = 0;
        //LATDbits.LATD6 = 1;
        //LATB = (LATB & 0x80FF) | (display7Scodes[digit_high]<<8);   
        //delay(10);
    //}
    //else{
        //LATDbits.LATD5 = 1;
        //LATDbits.LATD6 = 0;
        //LATB = (LATB & 0x80FF) | (display7Scodes[digit_low]<<8); 
        //delay(10);
    //}    
    //displayFlag = !displayFlag;
    
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    LATB = (LATB & 0x80FF) | (display7Scodes[digit_low]<<8); 
    delay(10);

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;
    
    LATB = (LATB & 0x80FF) | (display7Scodes[digit_high]<<8);   
    delay(10);
    
    
    

}

int main(void){

    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;


    TRISBbits.TRISB4 = 1;     // RBx digital output disconnected    
    AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)    
    AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this                              
                                //  mode an internal counter ends sampling and                              
                                //  starts conversion    
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter                              
                                //  interrupt is generated. At the same time,                              
                                    //  hardware clears the ASAM bit    
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)    
    AD1CON2bits.SMPI = 3;  // Interrupt is generated after XX samples                              
                                //  (replace XX by the desired number of                              
                                //  consecutive samples)    
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input                              
                                //  analog channel (0 to 15)    
    AD1CON1bits.ON = 1;       // Enable A/D converter                              
                            //  This must the last command of the A/D                             
                                //  configuration sequence 

    while(1){
        int k =0;
        int media =0;
        if(k++%25==0){
            AD1CON1bits.ASAM = 1;     // Start conversion
            while( IFS1bits.AD1IF == 0 );   // Wait while conversion not done
                int i;
                int *p = (int *)(&ADC1BUF0);
                for ( i = 0; i < 4; i++)
                    {
                    media = media + p[i*4];

                }
            media = media/5;
            media = (media*33)/1023;
            printInt(media,16 | 4 << 16);

            
            
            IFS1bits.AD1IF = 0;
            
        }
       
         
        send2displays(toBcd(media));


    }
}