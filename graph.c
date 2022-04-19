#include "graph.h"
#include "queue.h"
#include "error.h"

void makeGraph(graph_t *graph, node_t head, int w, int l){ 
        graph->head = malloc(sizeof(node_t));
        graph->width = malloc(sizeof(int));
        graph->len = malloc(sizeof(int));

        if(graph->head == NULL || graph->width == NULL || graph->len == NULL){
                printf("NOT_ENOUGH_MEMORY\n");
                exit( NOT_ENOUGH_MEMORY );
        }

        graph->n=1;
        graph->head[0] = head;
        graph->width[0] = w;
        graph->len[0] = l;
}


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
	
    makeGraph(&graph, nodes[0], width, len);
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
	int gsize, width, len, x, i, j, k, maxw=4;
        double y, max = 0;
	char c;

	commaToDott(in);

        fclose(in);

        in = fopen("5zuk4j2022_tmpfile", "r");
	
        if(fscanf(in, "%d %d", &len, &width) != 2){
                printf("FILE_FORMAT_ERR\n");
		remove( "5zuk4j2022_tmpfile" );
                exit( FILE_FORMAT_ERR );
        }

        while(fgetc(in)!='\n'){}

        gsize = width*len;
 
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
	
        makeGraph(graph, nodes_tmp[0], width, len);

        for(i=0; i<gsize; i++){
                for(j=0; j<nodes_tmp[i]->ways; j++)
                        nodes_tmp[i]->conn[j] = nodes_tmp[conn_tmp[i][j]];
        }


        free(conn_tmp);
        free(val_tmp);
        free(nodes_tmp);
    
        return max;
}

node_t findNode(graph_t *graph, int n, int nn) {
        q_t head=NULL, temp=NULL;
        int i, gsize = graph->width[nn]*graph->len[nn];

        addToQueue(&head, graph->head[nn]);
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
    int i, j, width = 0, len = graph.len[0], currGraph = 0, down, isdown, right, isright;
    node_t *nodes, head, tempdown, tempright;
    for( i= 0; i < graph.n; i++ ) {
	width+= graph.width[i];
    }
    nodes = malloc( len * width * sizeof *nodes );
    fprintf( out, "%d %d\n", width, len );
    while( currGraph < graph.n ) {
	head = graph.head[currGraph];
	while( head != NULL ) {
	    down = head->id + graph.width[currGraph];
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
		nodes[head->id] = head;
		if( graph.width[currGraph] > 1 && isright ) 
		    head = head->conn[j]; 
		else 
		    head = NULL; 
	    }
	    head = tempdown;     
	}
	currGraph++;
    }
    for( i= 0; i < len * width; i++ ) {
	for( j= 0; j < nodes[i]->ways; j++ )
	    fprintf( out, "\t%d: %lf", nodes[i]->conn[j]->id, nodes[i]->val[j] );
	fprintf( out, "\n" );
    }
}

void divideGraph(graph_t *graph, int n) {
        srand(time(NULL));

        int i, j, a, r, tmpi, gwidth = graph->width[0], glen = graph->len[0];
        node_t tmpn, node;

        int *ww = malloc((n *sizeof(int))); //tablica węzłów początkowych (width), których ścieżki mają być usunięte

        node_t **nodes = (node_t**)malloc(graph->width[0] *sizeof(node_t*));

        for(i=0; i<graph->width[0]; i++){
                nodes[i] = (node_t*)malloc(graph->len[0] *sizeof(node_t));
        }

        node = graph->head[0];
//Zapisywanie węzłów do tablicy dwuwymiarowej, aby móc po usunięciu ścieżek, dostać się do każdego węzła
        for(i=0; i<glen; i++){
                tmpn = node;
                for(j=0; j<gwidth; j++){
                        nodes[j][i] = node;
                        if((tmpi = findConnIndex(node, node->id+1)) != -1)
                                node = node->conn[tmpi];
                }
                if((tmpi = findConnIndex(tmpn, tmpn->id+gwidth)) != -1)
                        node = tmpn->conn[tmpi];
        }

//Wpisywanie do tablic indeksów początkowych węzłów do dzielenia
        for(i=0; i<n-1; i++){
                while(wasDrawn(ww, i,  r = rand() % (graph->width[0]-1)) == 1){} //losowanie dopóki nie będzie węzła, którego jeszcze nie było
                ww[i] = r;
        }

//Dzielenie grafu

        //Usuwanie połączeń węzłów
        for(i=0; i<n-1; i++){
                graphAdd(graph, nodes[ww[i]+1][0], findWidth(graph, ww[i], 1, gwidth), graph->len[0]);
                graphChangeSize(graph, ww[i], findWidth(graph, ww[i], -1, gwidth), graph->len[0], gwidth);
                for(j=0; j<graph->len[0]; j++){
                        deleteConn(nodes[ww[i]][j], 1);
                        deleteConn(nodes[ww[i]+1][j], -1);
                }

        }

        free(nodes);
        free(ww);
}

int wasDrawn(int *tab, int n, int a){
        int i;

        for(i=0; i<n; i++){
                if(tab[i] == a)
                        return 1;
        }

        return 0;
}

void deleteConn(node_t node, int n){
        int i, k = 0, a = findConnIndex(node, node->id+n);

        for(i=0; i<node->ways; i++){
                if(node->conn[i]->id != node->id+n){
                        node->conn[k] = node->conn[i];
                        node->val[k] = node->val[i];
                        k++;
                }
        }

        node->ways--;
        node->conn = realloc(node->conn, node->ways *sizeof(node_t));
        node->val = realloc(node->val, node->ways *sizeof(double));
}

int findWidth(graph_t *graph, int n, int a, int gwidth){
        int min, i;

        if(a == -1){
                min = gwidth;
                for(i=0; i<graph->n; i++){
                        if(graph->head[i]->id < n+1){
                                if(min > ((n+1)-graph->head[i]->id))
                                        min = (n+1)-graph->head[i]->id;
                        }
                }
                return min;
        }

        if(a == 1){
                min = gwidth-n-1;
                for(i=0; i<graph->n; i++){
                        if(graph->head[i]->id > n+1){
                                if(min > (n-graph->head[i]->id))
                                        min = graph->head[i]->id-(n+1);
                        }
                }
                return min;
        }
}

void graphAdd(graph_t *graph, node_t node, int w, int l){
        graph->n++;
        graph->head = realloc(graph->head, (graph->n) *sizeof(node_t));
        graph->width = realloc(graph->width, (graph->n) *sizeof(int));
        graph->len = realloc(graph->len, (graph->n) *sizeof(int));

        graph->head[graph->n-1] = node;
        graph->width[graph->n-1] = w;
        graph->len[graph->n-1] = l;
}

void graphChangeSize(graph_t *graph, int n, int w, int l, int gpw){
        int min = gpw, mini, i;

        for(i=0; i<graph->n; i++){
                if((graph->head[i]->id <= n) && ((n-graph->head[i]->id) < min)){
                        min = n-graph->head[i]->id;
                        mini = i;
                }
        }
        graph->width[mini] = w;
        graph->len[mini] = l;
}

void writeGraph(graph_t *graph, FILE *out, int nn){
	 int i, j, a, ti=0,  gsize = graph->width[nn]*graph->len[nn], g, s, ts, gpw = 0;
        node_t n, tmp = NULL, tmp2, tmp3;

        if(nn < graph->n)
                n = graph->head[nn];
        else
                printf("NO_GRAPH\n");

        for(i=0; i<graph->n; i++)
                gpw += graph->width[i];

        g = gpw*graph->len[0]-1 == 0 ? 1 : gpw*graph->len[0]-1;

        while(g > 0){
                ti++;
                g /= 10;
        }

        for(i=0; i<graph->len[nn]; i++){
                if(tmp != NULL){
                        tmp2 = tmp;
                        tmp3 = n ;
                        for(j=0; j<graph->width[nn]; j++){
                                if(findConnIndex(tmp3, tmp3->id-gpw) != -1)
                                        fprintf(out, "^         ");
                                else
                                        fprintf(out, "          ");
                                if(tmp3->id+1 < (i)*gpw+graph->width[nn]+graph->head[nn]->id)
                                        tmp3 = findNode(graph, tmp3->id+1, nn);

                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");
                        }
                        fprintf(out, "\n");

                        tmp2 = tmp;
                        for(j=0; j<graph->width[nn]; j++){
                                tmp3 = findNode(graph, tmp2->id+gpw, nn);
                                if(findConnIndex(tmp3, tmp3->id-gpw) != -1)
                                        fprintf(out, "|");
                                else
                                        fprintf(out, " ");

                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");

                                if(findConnIndex(tmp2, tmp2->id+gpw) != -1)
                                        fprintf(out, "|        ");
                                else
                                        fprintf(out, "         ");

                                if(tmp2->id+1 < (i-1)*gpw+graph->width[nn]+graph->head[nn]->id)
                                        tmp2 = findNode(graph, tmp2->id+1, nn);
                        }

                        fprintf(out,"\n");
                        tmp2 = tmp;
                        for(j=0; j<graph->width[nn]; j++) {
                                tmp3 = findNode(graph, tmp2->id+gpw, nn);
                                if((a = findConnIndex(tmp3, tmp3->id-gpw)) != -1)
                                        fprintf(out, "%.2lf ", tmp3->val[a]);
                                else
                                        fprintf(out, "    ");

                                if((a = findConnIndex(tmp2, tmp2->id+gpw)) != -1)
                                        fprintf(out, "%.2lf ", tmp2->val[a]);
                                else
                                        fprintf(out, "    ");

                                if(tmp2->id+1 < (i-1)*gpw+graph->width[nn]+graph->head[nn]->id)
                                        tmp2 = findNode(graph, tmp2->id+1, nn);
                        }
                        fprintf(out,"\n");

                        tmp2 = tmp;
                        for(j=0; j<graph->width[nn]; j++){
                                tmp3 = findNode(graph, tmp2->id+gpw, nn);
                                if(findConnIndex(tmp3, tmp3->id-gpw) != -1)
                                        fprintf(out, "|");
                                else
                                        fprintf(out, " ");

                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");

                                if(findConnIndex(tmp2, tmp2->id+gpw) != -1)
                                        fprintf(out, "|        ");
                                else
                                        fprintf(out, "         ");

                                if(tmp2->id+1 < (i-1)*gpw+graph->width[nn]+graph->head[nn]->id)
                                        tmp2 = findNode(graph, tmp2->id+1, nn);
                        }

                        fprintf(out,"\n");
                        tmp2 = tmp;
                        for(j=0; j<graph->width[nn]; j++){
                                for(s=0; s<ti; s++)
                                        fprintf(out, " ");

                                if(findConnIndex(tmp2, tmp2->id+gpw) != -1)
                                        fprintf(out, " v        ");
                                else
                                        fprintf(out, "          ");
                                if(tmp2->id+1 < (i-1)*gpw+graph->width[nn]+graph->head[nn]->id)
                                        tmp2 = findNode(graph, tmp2->id+1, nn);
                        }
                        fprintf(out,"\n");
                }

                tmp = n;

                for(j=0; j<graph->width[nn]; j++){
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
                        if((n->id+1) % gpw != 0){
                                if((a = findConnIndex(n, n->id+1)) != -1){
                                        fprintf(out, " -");
                                        fprintf(out, "%.2lf", n->val[a]);
                                        fprintf(out, "->");
                                }
                                else
                                        fprintf(out, "        ");
                        }
                        if(n->id+1<i*gpw+graph->width[nn]+graph->head[nn]->id)
                                n = findNode(graph, n->id+1, nn);
                }

                fprintf(out,"\n");
                if(tmp->id+1<(i)*gpw+graph->width[nn]+graph->head[nn]->id)
                        n = findNode(graph, tmp->id+1, nn);

                for(j=0; j<graph->width[nn]-1; j++){
                        fprintf(out, "\\");
                        for(s=0; s<ti; s++)
                                fprintf(out, " ");
                        fprintf(out, "/");
                        if((n->id) % gpw != 0){
                                if((a = findConnIndex(n, n->id-1)) != -1){
                                        fprintf(out, "<-");
                                        fprintf(out, "%.2lf", n->val[a]);
                                        fprintf(out, "- ");
                                }
                                else
                                        fprintf(out, "        ");
                        }
                        if(n->id+1<(i)*gpw+graph->width[nn]+graph->head[nn]->id)
                                n = findNode(graph, n->id+1, nn);
                }

                fprintf(out, "\\");
                for(s=0; s<ti; s++)
                        fprintf(out, " ");
               fprintf(out, "/\n");

                if(n->id+gpw < gpw*graph->len[nn])
                        n = findNode(graph, tmp->id+gpw, nn);
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


void freeGraph( graph_t graph, int nn ) {
    node_t tempdown, head = graph.head[nn];
    node_t *nodes = malloc( graph.width[nn]*graph.len[nn] * sizeof *nodes );
    int i, j, isdown, isright, down, right, nodecount = 0;
    graph.head[nn] = NULL;
    while( head != NULL ) {

	down = head->id + graph.width[nn];
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

	    if( graph.width[nn] > 1 && isright ) 
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

void freePath( path p ) {
    free( p->nodes );
    free( p );
}
