#include <stdio.h>
#include <stdlib.h>
#include "teste.h"

int main(){
    int val;

    scanf("%d",&val);

    int pog = process(val);

    printf("%d ",pog);

    return 0;
}