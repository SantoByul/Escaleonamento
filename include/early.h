#ifndef EARLY_H
#define EARLY_H

typedef struct infoE{
    int cap,per,dead;
} infoE;

typedef struct {
    char name[10];
    int period, burst, remaining, next_release, deadline, current_absolute_deadline, lost, complete, killed;
} TaskEDF;

void early(FILE *input, infoE inf);

#endif