#include "queue.h"

q_t initQueue( int value ) {
    q_t q = malloc( sizeof q + sizeof q->next );
    q->next = NULL;
    q->val = value;
    return q;
}

void addToQueue( q_t q, int value ) { //q - glowa kolejki
    if( q == NULL ) {
	printf( "Queue does not exist\n" );
	return;
    }
    q_t new = malloc( sizeof new + sizeof new->next );
    new->val = value;
    new->next = NULL;
    while( q->next != NULL )
	q = q->next;
    q->next = new;
}

int popFromQueue( q_t *q ) {
    if( *q == NULL ) {
	printf( "Queue empty\n" );
	return -1;
    }
    int show = (*q)->val;
    q_t temp = *q;
    *q = (*q)->next;
    free( temp );
    return show;
}

int inQueue( q_t q, int value ) {
    if( q == NULL )
	return 0;
    while( q != NULL ) {
	if( q->val == value )
	    return 1;
	q = q->next;
    }
    return 0;
}

void freeQueue( q_t q ) {
    q_t temp;
    while( q != NULL ) {
	temp = q;
	q = q->next;
	free( temp );
    }
}

