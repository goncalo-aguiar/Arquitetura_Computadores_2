#include <detpic32.h>    


void delay(int ms){
  for (;ms>0;ms--)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000);
        
    }
}


int main(void)    {      
    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 =0;
    
    while(1){
        putChar('\r');
        
        delay(100);
        printInt(++cnt10,0x0005000A);

        
        putChar(' ');
        printInt(cnt5,0x0005000A);
        
        putChar(' ');
        printInt(cnt1,0x0005000A);
        
        

    }

}

