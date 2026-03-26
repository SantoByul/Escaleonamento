#ifndef RATE_H
#define RATE_H

typedef struct infoR{
    int cap,per;
} infoR;

char rate(FILE *input, infoR inf);

#endif