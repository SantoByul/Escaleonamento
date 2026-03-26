#ifndef EARLY_H
#define EARLY_H

typedef struct infoE{
    int cap,per,dead;
} infoE;

void early(FILE *input, infoE inf);

#endif