#include<stdio.h>
#include <math.h>

static int mult = 0;
int func_ex1(double a[],int n);
int main(void){

    double arrays[][10] = {{1,2,3,4,5,6,7,8,9,10},
                        {1,2,4,4,5,6,7,8,9,10},
                        {1,2,4,8,5,6,7,8,9,10},
                        {1,2,4,8,16,6,7,8,9,10},
                        {1,2,4,8,16,32,7,8,9,10},
                        {1,2,4,8,16,32,64,8,9,10},
                        {1,2,4,8,16,32,64,128,9,10},
                        {1,2,4,8,16,32,64,128,256,10},
                        {1,2,4,8,16,32,64,128,256,512}};

    for(int i =0;i<9;i++){
        mult = 0;
        printf("\nResultado: %d",func_ex1(arrays[i],sizeof(arrays[0])/8));   
        printf("\tNum.Op: %d",mult);     
    }
    printf("\nAnalise do Caso Médio Experimentalmente:");  
    double array0[]={1,1,1,1,1,0,0,0,0,0}; 
    double array1[]={1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0}; 
    double array2[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
    mult = 0;
    printf("\nResultado: %d",func_ex1(array0,sizeof(array0)/8));   
    printf("\tNum.Op: %d",mult);  
    mult = 0;
    printf("\nResultado: %d",func_ex1(array1,sizeof(array1)/8));   
    printf("\tNum.Op: %d",mult); 
    mult = 0;
    printf("\nResultado: %d",func_ex1(array2,sizeof(array2)/8));   
    printf("\tNum.Op: %d",mult);  
    
    
        
                        
}

int func_ex1(double a[],int n){
    if(n>2){
        double r = a[1]/a[0];
        mult++;
        for(int i = 2;i<n;i++){
            mult++;
            if(a[i]/a[i-1]!=r){
            
                return 0;
            }
            
        }
        return 1;
    }
    else{
         printf("\nTamanho do array insuficiente");
         return 0;
    }
}