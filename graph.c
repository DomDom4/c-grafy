#include "graph.h"
#include "queue.h"
#include "error.h"

node_t makeNode( int width, int len, int current ) { 
    node_t nd;
    int ways;

    if( width == 1 && len == 1 )
	ways = 0;
    else if( current == 0 || current == width*len-1 || current == width-1 || current == width*len-width ) { //rog
	if( width == 1 || len == 1 ) 
	    ways = 1;
	else
	    ways = 2;
    }
    else if( (current > 0 && current < width-1) || (current > width*len-width && current < width*len-1) || current % width == 0 || current % width == width-1 ) { //krawedz
	if( width == 1 || len == 1 )
	    ways = 2;
	else
	    ways = 3;
    }
    else { //srodek
	ways = 4;
    }

    nd = malloc( sizeof *nd );
    nd->conn = malloc( ways * sizeof nd->conn );
    nd->val = malloc( ways * sizeof nd->val );
    nd->ways = ways;
    nd->id = current;

    if( nd->conn == NULL || nd->val == NULL || nd == NULL ) {
	printf( "NOT_ENOUGH_MEMORY\n" );
	exit( NOT_ENOUGH_MEMORY );
    }
    return nd;
}

double randomNumber( double high, double low ) {
    return ( (double)rand()*( high-low ) ) / RAND_MAX + low;
}


graph_t genFromParams( int width, int len, double a, double b ) { 
    srand( time ( NULL ));
    int i, high, low, last = width * len -1;
    node_t *nodes = malloc( (last+1) * sizeof *nodes ); 
    graph_t graph;
    int *conns = malloc( (last+1) * sizeof *conns ); 
    
    if( conns == NULL || nodes == NULL ) {
	printf( "NOT_ENOUGH_MEM\n" );
	exit( NOT_ENOUGH_MEMORY );
    }

    if( a > b ) { 
	high = a;
	low = b;
    } else {
	high = b;
	low = a;
    }

    for( i= 0; i <= last; i++ ) { 
	nodes[i] = makeNode( width, len, i );
	conns[i] = 0;
    }
    
    for( i= 0; i <= last; i++ ) {
	int right = i+1, down = i+width, up = i - width, left = i -1;
	
	if( right % width != 0 && conns[i] < nodes[i]->ways ) { 
	    double temp = randomNumber( high, low );
	    nodes[i]->conn[conns[i]] = nodes[right];
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[right]->conn[conns[right]] = nodes[i]; 
	    nodes[right]->val[conns[right]] = temp;
	    conns[right]++;
	    }
	if( down <= last && conns[i] < nodes[i]->ways ) { 
	    double temp = randomNumber( high, low );
	    nodes[i]->conn[conns[i]] = nodes[down]; 
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[down]->conn[conns[down]] = nodes[i]; 
	    nodes[down]->val[conns[down]] = temp;
	    conns[down]++;
	}
	if( up >= 0 && conns[i] < nodes[i]->ways) {
	    double temp = randomNumber( high, low );
	    nodes[i]->conn[conns[i]] = nodes[up]; 
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[up]->conn[conns[up]] = nodes[i]; 
	    nodes[up]->val[conns[up]] = temp;
	    conns[up]++;
	}
	if( left % width != width-1 && left > 0 && conns[i] < nodes[i]->ways ) { 
	    double temp = randomNumber( high, low );
	    nodes[i]->conn[conns[i]] = nodes[left];
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[left]->conn[conns[left]] = nodes[i];
	    nodes[left]->val[conns[left]] = temp;
	    conns[left]++;
	}
	
    }
    graph.width = width;
    graph.len = len;
    graph.head = nodes[0];
    free( nodes );
    free( conns );
    return graph;
}

node_t fileMakeNode( int ways ) { //funkcja pomocnicza do funkcji generujacej
    node_t nd = malloc( sizeof nd + ways * sizeof nd->val + ways * sizeof nd->conn );
    nd->conn = malloc( ways * sizeof nd->conn );
    nd->val = malloc( ways * sizeof nd->val );
    if( nd->conn == NULL || nd->val == NULL || nd == NULL ) {
        printf( "NOT_ENOUGH_MEMORY\n" );
        exit( NOT_ENOUGH_MEMORY );
    }
    return nd;
}

void commaToDott(FILE *in) {
        FILE *out = fopen("5zuk4j2022_tmpfile", "w");
        char c, rep=',';    

        while(1){
                c = fgetc(in);
    
                if(c == EOF)
                        break;

                if(c == rep) 
                        fprintf(out, "."); 
                else
                        fprintf(out, "%c", c); 
        }

        fclose(out);
}

double readFromFile( graph_t *graph, FILE *in ) {
	int gsize, x, i, j, k, maxw=4;
        double y, max = 0;
	char c;

	commaToDott(in);

        fclose(in);

        in = fopen("5zuk4j2022_tmpfile", "r");
	
        if(fscanf(in, "%d %d", &graph->len, &graph->width) != 2){
                printf("FILE_FORMAT_ERR\n");
		remove( "5zuk4j2022_tmpfile" );
                exit( FILE_FORMAT_ERR );
        }

        while(fgetc(in)!='\n'){}

        gsize = graph->width*graph->len;
 
        node_t *nodes_tmp = malloc(gsize *sizeof(node_t));

        int **conn_tmp = (int**)malloc(gsize *sizeof(int*));
        for(i=0; i<gsize; i++){
                conn_tmp[i] = (int*)malloc(maxw *sizeof(int));
        }

        double *val_tmp = malloc(maxw*sizeof(double));

	if((nodes_tmp == NULL) || (conn_tmp == NULL) || (val_tmp == NULL)){
                printf("NOT_ENOUGH_MEMORY\n");
		remove( "5zuk4j2022_tmpfile" );
                exit( NOT_ENOUGH_MEMORY );
        }
	
        for(i=0; i<gsize; i++){
                k = 0;
    
                while(((c = fgetc(in)) != '\n') && (k<maxw)){
			if(c == EOF){
				printf("INPUT_NODE\n");
				exit( INPUT_NODE );
			}
                        if(fscanf(in, "%d :%lg", &x, &y) != 2){
				printf("FILE_FORMAT_ERR\n");
				remove( "5zuk4j2022_tmpfile" );
				exit( FILE_FORMAT_ERR );
			}
			if(y > max)
				max = y;
			
                        conn_tmp[i][k] = x;
                        val_tmp[k] = y;
                        k++;
                }

                nodes_tmp[i] = fileMakeNode(k);
    
                nodes_tmp[i]->id = i;
    
                for(j=0; j<k; j++)
                        nodes_tmp[i]->val[j] = val_tmp[j];
    
                nodes_tmp[i]->ways = k;
        }    

	fclose(in);
        remove("5zuk4j2022_tmpfile");
	
        graph->head = nodes_tmp[0];

        for(i=0; i<gsize; i++){
                for(j=0; j<nodes_tmp[i]->ways; j++)
                        nodes_tmp[i]->conn[j] = nodes_tmp[conn_tmp[i][j]];
        }


        free(conn_tmp);
        free(val_tmp);
        free(nodes_tmp);
    
        return max;
}

node_t findNode(graph_t *graph, int n ) {
        q_t head=NULL, temp=NULL;
        int i, gsize = graph->width*graph->len;

        addToQueue(&head, graph->head);
        temp = head;

        while(gsize>0){
                for(i=0; i<temp->node->ways; i++){
                        if(temp->node->conn[i]->id == n){
                                return temp->node->conn[i];
                        }
                        if(!inQueue(head, temp->node->conn[i]->id))
                                addToQueue(&head, temp->node->conn[i]);
                }
                temp = temp->next;
                gsize--;
        }

        freeQueue( temp );
        freeQueue( head );

        printf("NO_NODE - %d\n", n);
        exit(NO_NODE);
}

void printToFile( graph_t graph, FILE *out ) {
    int i, j, nodown, noright, down, right;
    node_t temp, head = graph.head;
    fprintf( out, "%d %d\n", graph.width, graph.len );
    while( 1 ) {
	nodown = 1;
	down = head->id + graph.width;
	temp = head;
	for( i= 0; i < head->ways; i++ ) { 
	    if( head->conn[i]->id == down ) {
		nodown = 0;
		break;
	    }
	}
	while( 1 ) {
	    noright = 1;
	    right = temp->id + 1;
	    for( j= 0; j < temp->ways; j++ ) 
		fprintf( out, "\t%d :%lf ", temp->conn[j]->id, temp->val[j] );
	    fprintf( out, "\n" );
	    for( j= 0; j < temp->ways; j++ ) 
		if( temp->conn[j]->id == right ) {
		    noright = 0;
		    break;
		}
	    if( noright || right == down ) 
		break;
	    temp = temp->conn[j]; 
	}
	if( nodown ) 
	    break;
	head = head->conn[i]; 	
    }
}

void writeGraph(graph_t *graph, FILE *out){
	int i, j, a, ti=0,  gsize = graph->width*graph->len, g=gsize-1, s, ts; 

        node_t n = graph->head, tmp = NULL, tmp2, tmp3;

	g = gsize-1 == 0 ? 1 : gsize-1;
	
        while(g>0){
                ti++;
                g/=10;
        }

        for(i=0; i<graph->len; i++){
                if(tmp != NULL){
                        tmp2 = tmp;
                        tmp3 = findNode(graph, tmp->id+graph->width);
                        for(j=0; j<graph->width; j++){
                                if(findConnIndex(tmp3, tmp3->id-graph->width) != -1) 
                                        fprintf(out, "^         ");
                                else
                                        fprintf(out, "          ");
                                if(tmp3->id+1 < gsize)
                                        tmp3 = findNode(graph, tmp3->id+1);

                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");
                        }
                        fprintf(out, "\n");

                        tmp2 = tmp;
                        for(j=0; j<graph->width; j++){
                                tmp3 = findNode(graph, tmp2->id+graph->width);
                                if(findConnIndex(tmp3, tmp3->id-graph->width) != -1) 
                                        fprintf(out, "|");
                                else
                                        fprintf(out, " ");

                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");

                                if(findConnIndex(tmp2, tmp2->id+graph->width) != -1) 
                                        fprintf(out, "|        ");
                                else
                                        fprintf(out, "         ");

                                if(tmp2->id+1 < gsize)
                                        tmp2 = findNode(graph, tmp2->id+1);
                        }

                        fprintf(out,"\n");
                        tmp2 = tmp;
                        for(j=0; j<graph->width; j++) {
                                tmp3 = findNode(graph, tmp2->id+graph->width);
                                if((a = findConnIndex(tmp3, tmp3->id-graph->width)) != -1) 
                                        fprintf(out, "%.2lf ", tmp3->val[a]);
                                else
                                        fprintf(out, "    ");

                                if((a = findConnIndex(tmp2, tmp2->id+graph->width)) != -1) 
                                        fprintf(out, "%.2lf ", tmp2->val[a]);
                                else
                                        fprintf(out, "    ");

                                if(tmp2->id+1 < gsize)
                                        tmp2 = findNode(graph, tmp2->id+1);
                        }
                        fprintf(out,"\n");

                        tmp2 = tmp;
                        for(j=0; j<graph->width; j++){
                                tmp3 = findNode(graph, tmp2->id+graph->width);
                                if(findConnIndex(tmp3, tmp3->id-graph->width) != -1) 
                                        fprintf(out, "|");
                                else
                                        fprintf(out, " ");

                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");

                                if(findConnIndex(tmp2, tmp2->id+graph->width) != -1) 
                                        fprintf(out, "|        ");
                                else
                                        fprintf(out, "         ");
    
                                if(tmp2->id+1 < gsize)
                                        tmp2 = findNode(graph, tmp2->id+1);
                        }

                        fprintf(out,"\n");
                        tmp2 = tmp;
                        for(j=0; j<graph->width; j++){
                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");

                                if(findConnIndex(tmp2, tmp2->id+graph->width) != -1) 
                                        fprintf(out, " v        ");
                                else
                                        fprintf(out, "          ");
                                if(tmp2->id+1 < gsize)
                                        tmp2 = findNode(graph, tmp2->id+1);
                        }
                        fprintf(out,"\n");
                }

                tmp = n;

                for(j=0; j<graph->width; j++){
                        fprintf(out, "/");
                        ts = 0;
                        s = n->id == 0 ? 1 : n->id;
                        while(s>0){
                                ts++;
                                s/=10;
                        }
                        for(s=0; s<ti-ts; s++)
                                fprintf(out, " ");
                        fprintf(out, "%d\\", n->id);
                        if((n->id+1) % graph->width != 0){ 
                                if((a = findConnIndex(n, n->id+1)) != -1){
                                        fprintf(out, " -");
                                        fprintf(out, "%.2lf", n->val[a]);
                                        fprintf(out, "->");
                                }
                                else
                                        fprintf(out, "        ");
                        }
                        if(n->id+1<gsize)
                                n = findNode(graph, n->id+1);
                }

                fprintf(out,"\n");
                if(n->id+1<gsize)
                        n = findNode(graph, tmp->id+1);

                for(j=0; j<graph->width-1; j++){
                        fprintf(out, "\\");
                        for(s=0; s<ti; s++)
                                fprintf(out, " ");
                        fprintf(out, "/");
                        if((n->id) % graph->width != 0){ 
                                if((a = findConnIndex(n, n->id-1)) != -1){
                                        fprintf(out, "<-");
                                        fprintf(out, "%.2lf", n->val[a]);
                                        fprintf(out, "- ");
                                }
                                else
                                        fprintf(out, "        ");
                        }
                        if(n->id+1<gsize)
                                n = findNode(graph, n->id+1);
                }

                fprintf(out, "\\");
                for(s=0; s<ti; s++)
                        fprintf(out, " ");
               fprintf(out, "/\n");
        }
}

int findConnIndex(node_t node, int a) {
        int i;

        for(i=0; i<node->ways; i++){
                if(node->conn[i]->id == a)
                        return i;
        }
    
        return -1;
}


void freeGraph( graph_t graph ) {
    node_t tempdown, head = graph.head;
    node_t *nodes = malloc( graph.width*graph.len * sizeof *nodes );
    int i, j, isdown, isright, down, right, nodecount = 0;
    graph.head = NULL;
    while( head != NULL ) {

	down = head->id + graph.width;
	isdown = 0;
	for( i= 0; i < head->ways; i++ ) { 
	    if( head->conn[i]->id == down ) {
		isdown = 1;
		break;
	    }
	}
	
	if( isdown ) 
	    tempdown = head->conn[i]; 
	else 
	    tempdown = NULL; 

	while( head != NULL ) {
	    
	    right = head->id + 1;
	    isright = 0;
	    for( j= 0; j < head->ways; j++ ) 
		if( head->conn[j]->id == right ) {
		    isright = 1;
		    break;
		}

	    nodes[nodecount] = head;
	    nodecount++;

	    if( graph.width > 1 && isright ) 
		head = head->conn[j]; 
	    else 
		head = NULL; 
	}
	head = tempdown;     
    }
    for( i= 0; i < nodecount; i++ ) 
	free( nodes[i] );
   
    free( nodes );
}
