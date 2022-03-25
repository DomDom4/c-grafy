#include "graph.h"
#include "queue.h"

int checkIntegrity( graph_t graph ) { //BFS
    q_t temp, working, checked = NULL;
    node_t head = graph.head;
    working = initQueue( head->id );
    int i, count = 0, nodes = graph.width*graph.len;
    while( working != NULL ) {
	for( i= 0; i < head->ways; i++ ) 
	    if( !inQueue( working, head->conn[i]->id ) && !inQueue( checked, head->conn[i]->id ) ) //dodanie do kolejki wezlow ktore nie zostaly jeszcze odwiedzone
		addToQueue( working, head->conn[i]->id );
	if( checked == NULL ) 
	    checked = initQueue( popFromQueue( &working ) );
	else
	    addToQueue( checked, popFromQueue( &working ) );
	if( working != NULL )
	    for( i= 0; i < head->ways; i++ ) 
		if( head->conn[i]->id == working->val ) {
		    head = head->conn[i];
		    break;
		}
    }
    temp = checked;
    while( checked != NULL ) {
	count++;
	checked = checked->next;
    }
    freeQueue( temp );
    if( count == nodes )
	return 1;
    return 0;
}
void findPath( graph_t graph ); //Dijsktra
