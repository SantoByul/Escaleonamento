#include <stdio.h>

void early(FILE *input, inputE inf){
    if(input == NULL){
        return;
    }
    FILE *output = fopen("edf_dsob.out","w");
    printf("No rate\n");
    fprintf(output,"EXECUTION BY EDF\n");
    fprintf(output,"\n");
    fclose(output);
}