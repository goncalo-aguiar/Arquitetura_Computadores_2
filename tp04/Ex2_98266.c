#include <detpic32.h>   

void delay(int ms);

int main(void){ 

    LATEbits.LATE0 = 0;   
    LATEbits.LATE1 = 0; 
    LATEbits.LATE2 = 0; 
    LATEbits.LATE3 = 0; 
    TRISEbits.TRISE0 =0;
    TRISEbits.TRISE1 =0;
    TRISEbits.TRISE2 =0;
    TRISEbits.TRISE3 =0;

    int count =0x0000;
    while(1){
        delay(250);


        if(count==0x0010){
            count =0x0000;
        }

        LATE =  (LATE & 0xFFF0) | count;
        count++;


    }

   

    return 0;    
        
        
}


void delay(int ms){
    while(ms>0){
        resetCoreTimer();
        while(readCoreTimer()<20000)
            ms--;

        
    }
}