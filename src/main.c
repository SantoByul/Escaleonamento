#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rate.h"
#include "early.h"

int main(){
    bool exec = false;
    FILE *input = fopen("input.txt","a");
    int time,cont;
    infoR r;
    infoE e;

    #if defined(RATE) || defined(EARLY)
        fscanf(input,"%d",&time);
    #endif
    
    #ifdef RATE
        rate(input,r);
        exec = true;
    #endif

    #ifdef EARLY
        FILE *output = fopen("edf_dsob.out","w");
        early(input,e);
        exec = true;
    #endif

    if(exec==true){
        fclose(input);
        printf("Foi Bonitin todo\n");
        return 0;
    }
    else{
        printf("Modo Invalido\n");
        return 1;
}   }