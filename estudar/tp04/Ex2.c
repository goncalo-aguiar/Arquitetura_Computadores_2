#include <detpic32.h>    


void delay(int ms){
    for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}
    

int main(void){ 

    TRISE = TRISE & 0xFFF0;
    int contador =0;

    LATE = LATE & 0xFFF0;
    while(1){
        if(contador>15){
            contador =0;
            
        }
        LATE = (LATE & 0xFFF0) | contador;
        


        contador++;
        delay(250);
    }



}