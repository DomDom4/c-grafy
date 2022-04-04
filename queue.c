#include "queue.h"
#include "graph.h"

q_t initQueue( node_t n ) {
    q_t q = malloc( sizeof q + sizeof q->next );
    q->next = NULL;
    q->node = n;
    return q;
}

void addToQueue( q_t q, node_t n ) { //q - glowa kolejki
    if( q == NULL ) { 
        printf( "Queue does not exist\n" );
        return;
    }   
    q_t new = malloc( sizeof new + sizeof new->next );
    new->node = n;
    new->next = NULL;
    while( q->next != NULL )
        q = q->next;
    q->next = new;
}

node_t popFromQueue( q_t *q ) { 
    if( *q == NULL ) { 
        printf( "Queue empty\n" );
        return NULL;
    }   
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

q_t priorityQueue( graph_t *graph, node_t n ) { 
        q_t head, temp;
        int i, gsize = graph->width*graph->len;

        head = initQueue(n);
        head->node = graph->head;
        temp = head;

        while(gsize>0){
                for(i=0; i<temp->node->ways; i++){
                        if(!inQueue(head, temp->node->conn[i]->id))
                                addToQueue(head, temp->node->conn[i]);
                }
                temp = temp->next;
                gsize--;
        }

        freeQueue( temp );

        return head;

}

void writeQueue(q_t q, int n) {
        while(n>0){
                printf("%d -> ", q->node->id);
                q = q->next;
                n--;
        }
}
