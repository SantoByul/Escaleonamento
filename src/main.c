#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rate.h"
#include "early.h"

int main(){
    bool exec = false;
    FILE *input = fopen("input.txt","w+");
    int c, p;

    #ifdef RATE
        rate(input);
        exec = true;
    #endif

    #ifdef EARLY
        printf("Eita q devia ser Early\n");
        exec = true;
    #endif

    if(exec==true){
        printf("Foi Bonitin todo\n");
        fclose(input);
    }
    else{
        printf("Modo Invalido\n");
        return 1;
}   }