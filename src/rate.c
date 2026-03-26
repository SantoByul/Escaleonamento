#include <stdio.h>
#include "rate.h"

void rate(FILE *input, infoR inf){
    if (input==NULL){
        return;
    }
    FILE *output = fopen("rate_dsob.out","w");
    printf("No rate\n");
    fprintf(output,"EXECUTION BY RATE\n");
    fprintf(output,"\n");
    fclose(output);
}