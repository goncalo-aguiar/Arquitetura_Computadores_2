#include<detpic32.h>

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0xFd,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    value = toBcd(value);
    int digit_high = value >> 4;
    int digit_low  = 0x0F & value;
    printf("high: %d, low: %d\n",digit_high,digit_low);
    static char displayFlag = 0;
    unsigned int seg;
    // send to display high
    if(displayFlag == 0){
        LATDbits.LATD6 = 1;                             // enable display high
        LATDbits.LATD5 = 0;                             // disable display low
        seg = display7Scodes[digit_high];               // convert to 7 segments code
        LATB = (LATB & 0x00FF) | (seg<<8);              // send to display                                     
    }                                    
    // send to display low
    else{
        LATDbits.LATD5 = 1;                             // enable display low
        LATDbits.LATD6 = 0;                             // disable display high 
        seg = display7Scodes[digit_low];      
        LATB = (LATB & 0x00FF) | seg<<8;                // send to display
    }
    displayFlag = !displayFlag;    
   
}


int main (void){
    TRISB = TRISB & 0x80FF;     // configure RB8 to RB14 and RD5 to RD6 as outputs
    TRISD = TRISD & 0xFF9F;

    TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0; // RB4 configured as analog input (AN4)
    AD1CON1bits.SSRC = 7; 

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = 3;    // 1 sample will be converted and stored
                            // in buffer location ADC1BUF0

    AD1CHSbits.CH0SA = 4;   // Selects AN4 as input for the A/D converter
 
    AD1CON1bits.ON = 1;     // Enable A/D converter 
    int amplitude =0;
    int k=0;

    while(1){
        if(k++ % 25 == 0){
            AD1CON1bits.ASAM = 1;  // Start conversion
            while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done (AD1IF == 0) 
            int *p = (int *)(&ADC1BUF0);
            int i;
            int sum = 0;
            for( i = 0; i < 4; i++ ){
                sum += p[i*4];
            }
            amplitude = ((sum/4)*33)/1023;
            printf("%d",amplitude);
        }    
        send2displays(toBcd(amplitude));
        delay(10);
        IFS1bits.AD1IF = 0;
    }
    return 0;
}