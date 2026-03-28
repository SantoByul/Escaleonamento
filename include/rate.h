#ifndef RATE_H
#define RATE_H

typedef struct infoR{
    int cap,per;
} infoR;

typedef struct {
    char name[10];
    int period, burst, remaining, next_release, deadline, lost, complete, killed;
} Task;

void rate(FILE *input, infoR inf);

#endif