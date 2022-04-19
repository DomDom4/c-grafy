#include "queue.h"
#include "graph.h"

void addToQueue( q_t *q, node_t n ) { //q - glowa kolejki
    if( *q == NULL ) {
	*q = malloc( sizeof **q );
	(*q)->next = NULL;
	(*q)->node = n;
	return;
    }   
    q_t new = malloc( sizeof *new );
    q_t temp = *q;
    new->node = n;
    new->next = NULL;
    while( temp->next != NULL )
        temp = temp->next;
    temp->next = new;
}

node_t popFromQueue( q_t *q ) { 
    if( *q == NULL ) 
        return NULL;
	
    node_t show = (*q)->node;
    q_t temp = *q; 
    *q = (*q)->next;
    free( temp );
    return show;
}

int inQueue( q_t q, int value ) {
    if( q == NULL )
	return 0;
    while( q != NULL ) {
	if( q->node->id == value )
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

q_t priorityQueue( node_t n ) { 
    q_t temp = NULL, checked = NULL;
    node_t head = n;
    int i;
    addToQueue( &temp, head );
    while( temp != NULL ) { 
        for( i= 0; i < head->ways; i++ ) 
            if( !inQueue( temp, head->conn[i]->id ) && !inQueue( checked, head->conn[i]->id ) ) 
                addToQueue( &temp, head->conn[i] );
        addToQueue( &checked, popFromQueue( &temp ) );
        if( temp != NULL )
            head = temp->node;
    }   

    return checked; 
}

void writeQueue(q_t q, int n) {
        while(n>0){
                printf("%d -> ", q->node->id);
                q = q->next;
                n--;
        }
}
