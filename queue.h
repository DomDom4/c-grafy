#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

typedef struct q { 
    node_t node;
    struct q *next;
} *q_t;

void addToQueue( q_t *q, node_t n );

node_t popFromQueue( q_t *q );

int inQueue( q_t q, int value );

q_t priorityQueue( node_t n );

void writeQueue(q_t q, int n); 

void freeQueue( q_t q );

#endif
