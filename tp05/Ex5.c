#include <detpic32.h> 

int main(void)    {       
                                // Configure all (digital I/O, analog input, A/D module)    
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
    AD1CON2bits.SMPI = 3;  // Interrupt is generated after XX samples                              
                            //  (replace XX by the desired number of                              
                            //  consecutive samples)    
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input                               
                            //  analog channel (0 to 15)    
    AD1CON1bits.ON = 1;       // Enable A/D converter                              
                            //  This must the last command of the A/D                             
                            //  configuration sequence
    LATDbits.LATD6 = 0; // display high inactive          
    LATDbits.LATD5 = 1; // display low active          
    TRISB = TRISB & 0x80FF;     // configure RB8-RB14 as outputs       
                                    
    TRISD = TRISD & 0xFF9F;     // configure RD5-RD6 as outputs        
    i = 0;       
    while(1){          
        if(i++ % 25 == 0) // 0, 250ms, 500ms, 750ms, ...         
        {             
         AD1CON1bits.ASAM = 1;               // Start conversion          
        while( IFS1bits.AD1IF == 0 );       // Wait while conversion not done (AD1IF == 0)          
        int *p = (int *)(&ADC1BUF0);        // Convert analog input (4 samples)  
        int i;
        int x[];
        int media=0;
        for(  i = 0; i < 4; i++ ) {
            media = media + p[i*4];           // Calculate buffer average 
        }                           
        int amplitude = (media/4)*33)/1023;   // Calculate voltage amplitude                    
        amplitude_mais_significativo  = ((amplitude/10) <<4 )+(amplitude%10 );               // Convert voltage amplitude to decimal     
                            
        }          
        int displayCodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
        int i;
        for( i=0;i<sizeof(displayCodes)/4;i++){
        int x = displayCodes[i];
        x = x << 8;
        LATB = (LATB & 0x80FF) | x;
        delay(2000); 
    }                   
                    // Wait 10 ms (using the core timer)       
    }       
    return 0;   
}