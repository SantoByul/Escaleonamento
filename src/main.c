#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rate.h"
#include "early.h"

int main(){
    bool exec = false;
    FILE *input = fopen("input.txt","w+");
    int time,cont = 1;
    infoR r;
    infoE e;

    #if defined(RATE) || defined(EARLY)
        scanf("%d",&time);
        fprintf(input,"%d\n",time);
    #endif
    
    #ifdef RATE
        while(1){
            if(scanf("%d %d",&r.cap,&r.per)!=2){
                break;
            }
            fprintf(input,"T%d %d %d\n",cont,r.cap,r.per);
            cont++;
        }
        rate(input,r);
        exec = true;
    #endif

    #ifdef EARLY
    while(1){
        if(scanf("%d %d %d",&e.cap,&e.per,&e.dead)!=3){
            break;
        }
        fprintf(input,"T%d %d %d %d\n",cont,e.cap,e.per,e.dead);
        cont++;
    }
        early(input,e);
        exec = true;
    #endif

    if(exec==true){
        fclose(input);
        return 0;
    }
    else{
        printf("Modo Invalido\n");
        return 1;
    }

}