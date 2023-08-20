#include <detpic32.h>
volatile int voltage;
volatile int contador =0 ;
volatile int voltMax=0;
volatile int voltMin =33;
void putc(char byte2send){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte2send;
}
void send2displays(unsigned char c){
    static char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static int displayflag;
    char dl = display7Scodes[c & 0x0f];
    char dh = display7Scodes[c >> 4];

    if(displayflag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80ff) | (dl<<8);
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80ff) | (dh <<8);
    }
    displayflag = !displayflag;

}

char toBcd(unsigned char x){
    return (x /10 << 4) + x % 10;
}
void _int_(27) isr_adc(void){

    int *p = (int*)(&ADC1BUF0);
    int i = 0;
    int media  = 0;
    for ( i = 0; i < 8; i++)
    {
        media = media + p[i*4];
    }
    media = media /8;
    voltage = (media*33)/1023;
    if(voltage < voltMin){
        voltMin = voltage;
    }
    if(voltage > voltMax){
        voltMax = voltage;
    }
    
    
    IFS1bits.AD1IF = 0;
}

void _int_(4) isr_t1(void){
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}
void _int_(12) isr_t3(void){
    send2displays(toBcd(voltage));
    char aux = toBcd(voltage);
    if(contador==100){
        putc((aux>>4) + '0');
        putc((aux & 0x0f) +'0');
        contador =0;
        putc('\n');
    }
    contador++;
    IFS0bits.T3IF = 0;
}

void _int_(32) isr_uart(void){
    
    if(U2RXREG == 'L'){
        putc('\n');
        char volts = toBcd(voltMin);
        putc((volts >>4) + '0');
        putc((volts & 0x0f) + '0');
        volts = toBcd(voltMax);
        putc((volts >>4) + '0');
        putc((volts & 0x0f) + '0');

    }
    IFS1bits.U2RXIF = 0;
}


int main(void){
    TRISB = TRISB & 0x80FF;
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
    AD1CON2bits.SMPI = 8-1;  // Interrupt is generated after XX samples                              
                                        //  (replace XX by the desired number of                              //  consecutive samples)    
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input                               
                            //  analog channel (0 to 15)    
    AD1CON1bits.ON = 1;       // Enable A/D converter                              
                                        //  This must the last command of the A/D                             //  configuration sequence

    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;
    IPC6bits.AD1IP = 2;


    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e Fout_presc = 625 KHz)    
    PR1 = 19531;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz    
    TMR1 = 0;            // Reset timer T2 count register    
    T1CONbits.TON = 1;   // Enable timer T2 (must be the last command of the                         
                         //  timer configuration sequence)
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    IPC1bits.T1IP = 2;

    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e Fout_presc = 625 KHz)    
    PR3 = 50000;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz    
    TMR3 = 0;            // Reset timer T2 count register    
    T3CONbits.TON = 1;   // Enable timer T2 (must be the last command of the                         
                         //  timer configuration sequence)
    
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    IPC3bits.T3IP = 2;

    U2MODEbits.BRGH = 0;
    U2BRG = ((115200*8 + PBCLK) / (16*115200)) -1  ; 

    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN =1;
    U2STAbits.URXEN =1;

    U2MODEbits.ON = 1;

    IFS1bits.U2RXIF = 0;
    IEC1bits.U2RXIE = 1;
    IPC8bits.U2IP = 2;

    EnableInterrupts();

    while(1){
        
    }
    
}