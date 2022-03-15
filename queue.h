#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct q {
    int val;
    struct q *next;
} *q_t;

q_t initQueue( int value );

void addToQueue( q_t q, int value );

int popFromQueue( q_t *q );

void freeQueue( q_t q );

#endif
