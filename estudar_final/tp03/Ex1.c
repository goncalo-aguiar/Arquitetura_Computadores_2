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
int main(void){
    TRISCbits.TRISC14 = 0;

    while(1){
        delay(1000);
        LATCbits.LATC14 =  !LATCbits.LATC14;
    }
    return 0;
}