#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rate.h"
#include "early.h"

int main(){

    #ifdef RATE
        printf("Eita q devia ser Rate\n");
        return 0;
    #endif

    #ifdef EARLY
        printf("Eita q devia ser Early\n");
        return 0;
    #endif

    printf("Modo Invalido\n");
    return 1;
}