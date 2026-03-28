#ifndef RATE_H
#define RATE_H

typedef struct infoR{
    int cap,per;
} infoR;

typedef struct {
    char name[10];
    int period;
    int burst;
    int remaining;
    int next_release;
    int deadline;
    int lost;
    int complete;
    int killed;
} Task;

void rate(FILE *input, infoR inf);

#endif