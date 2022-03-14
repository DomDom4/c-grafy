#include "queue.h"

q_t initQueue( int value ) {
    q_t q = malloc( sizeof q );
    q->next = NULL;
    q->val = value;
    return q;
}

void addToQueue( q_t q, int value ) { //q - glowa kolejki
    if( q == NULL ) {
	printf( "Kolejka nie istnieje\n" );
	return;
    }
    q_t new = malloc( sizeof new );
    new->val = value;
    new->next = NULL;
    while( q->next != NULL )
	q = q->next;
    q->next = new;
}

int popFromQueue( q_t *q ) {
    if( *q == NULL ) {
	printf( "Kolejka pusta\n" );
	return -1;
    }
    int show = (*q)->val;
    *q = (*q)->next;
    return show;
}

