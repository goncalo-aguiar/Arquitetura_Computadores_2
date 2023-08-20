
void setPWM(unsigned int dutyCycle)    {       // duty_cycle must be in the range [0, 100]       
       
    OC1CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation    
    OC1RS = (dutyCycle*PR3)/100;       // Ton constant    
    OC1CONbits.ON = 1;   // Enable OC1 module   
} 