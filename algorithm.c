#include "graph.h"
#include "queue.h"
#include "error.h"

int checkIntegrity( graph_t graph ) { //BFS
    q_t temp, working = NULL, checked = NULL;
    node_t head = graph.head;
    int i, count = 0, nodes = graph.width*graph.len;
    addToQueue( &working, head );
    while( working != NULL ) { 
        for( i= 0; i < head->ways; i++ ) 
            if( !inQueue( working, head->conn[i]->id ) && !inQueue( checked, head->conn[i]->id ) ) 
                addToQueue( &working, head->conn[i] );
        addToQueue( &checked, popFromQueue( &working ) );
        if( working != NULL )
	    head = working->node;
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


path findPath( graph_t *graph, int start, int end, double maxval ) { //Dijsktra
	int gsize = graph->width * graph->len, i, k = 0;

        q_t Q = malloc(gsize *sizeof(node_t));

        int Qd = gsize;

        double *d = malloc(gsize *sizeof(double));
        node_t *p = malloc(gsize *sizeof(node_t));
        node_t *temp = malloc(gsize *sizeof(node_t));

        node_t c = findNode(graph, start);
        path dp = malloc(sizeof(path));

	if((Q == NULL) || (d == NULL) || (p == NULL) || (temp == NULL) || (dp == NULL)){
                printf("NOT_ENOUGH_MEMORY\n");
                exit( NOT_ENOUGH_MEMORY );
        }
	
        Q = priorityQueue(graph, c); 
        //writeQueue(Q, gsize);

        infinity(d, gsize, maxval);
        null(p, gsize);

        d[start] = 0;
    
        while(Qd > 0){ 
                if((c = popFromQueue(&Q)) == NULL){
                        break;
                }
                //printf("%d -> ", c->id);
                for(i=0; i<c->ways; i++){
                        if(d[c->conn[i]->id] > d[c->id]+c->val[i]){
                                d[c->conn[i]->id] = d[c->id] + c->val[i];
                                p[c->conn[i]->id] = c;
                        }
                }
                Qd--;
        }
    
/*        -- Sprawdzenie przejść --

        int tmp = end;
        printf("\nPrzejscia od ostatniego: ");
        while(tmp != start){
                printf("%d <- ", tmp);
                tmp = p[tmp]->id;
        }
        printf("%d; ", tmp);

	printf("Suma wag przejsc: %lf\n", d[end]);
*/

        dp->val_s = d[end];

        temp[k] = findNode(graph, end);
        k++;

        while( end != start ){
                temp[k] = p[end];
                end = p[end]->id;
                k++;
        }

        dp->nodes = malloc(k*sizeof(node_t));

	if(dp->nodes == NULL){
        printf("NOT_ENOUGH_MEMORY\n");
                exit( NOT_ENOUGH_MEMORY );
        }
	
        for(i=0; i<k; i++)
                dp->nodes[i] = temp[k-i-1];

        dp->n_nb = k;


        free(p);
        free(temp);
        free(d);

        return dp;
}

void infinity(double *d, int s, double n)
{
        int i;

        for(i=0; i<s; i++)
                d[i]=2*s*n;
}

void null(node_t *t, int n)
{
        int i;

        for(i=0; i<n; i++)
                t[i]=NULL;
}	
