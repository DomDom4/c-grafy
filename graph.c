#include "graph.h"

node_t makeNode( int width, int len, int current ) { //funkcja pomocnicza do funkcji generujacej
    node_t nd;
    int ways;
    
    //nadanie wlasnosci wezlowi
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
    nd = malloc( sizeof nd + ways * sizeof nd->val + ways * sizeof nd->conn );
    nd->conn = malloc( ways * sizeof nd->conn );
    nd->val = malloc( ways * sizeof nd->val );
    nd->ways = ways;
    nd->id = current;
    if( nd->conn == NULL || nd->val == NULL || nd == NULL ) {
	printf( "NOT_ENOUGH_MEM\n" );
	exit( 11 );
    }
    return nd;
}

graph_t genFromParams( int width, int len, double a, double b ) { 
    srand( time ( NULL ));
    int i, high, low, last = width * len -1;
    node_t head, *nodes = malloc( (last+1) * sizeof nodes ); //tymczasowe przechowywanie adresow wezlow
    graph_t graph;
    int *conns = malloc( (last+1) * sizeof conns ); //stan istniejacych polaczen dla kazdego wezla
    
    if( conns == NULL || nodes == NULL ) {
	printf( "NOT_ENOUGH_MEM\n" );
	exit( 11 );
    }

    if( a > b ) { //wybor wiekszeconns[i] wartosci
	high = a;
	low = b;
    } else {
	high = b;
	low = a;
    }

    for( i= 0; i <= last; i++ ) { //zaalokowanie pamieci dla kazdego wezla
	nodes[i] = makeNode( width, len, i );
	conns[i] = 0;
    }
    head = nodes[0];
    
    for( i= 0; i <= last; i++ ) {
	int right = i+1, down = i+width, up = i - width, left = i -1;

	if( right % width != 0 && conns[i] < nodes[i]->ways ) { //zaznacz sciezke w prawo i z powrotem
	    double temp = ( (double)rand()*( high-low ) ) / RAND_MAX + low;
	    nodes[i]->conn[conns[i]] = nodes[right]; //w prawo
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[right]->conn[conns[right]] = nodes[i]; //z powrotem
	    nodes[right]->val[conns[right]] = temp;
	    conns[right]++;
	    }
	if( down <= last && conns[i] < nodes[i]->ways ) { //zaznacz sciezke w dol i z powrotem
	    double temp = ( (double)rand()*( high-low ) ) / RAND_MAX + low;
	    nodes[i]->conn[conns[i]] = nodes[down]; // w dol
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[down]->conn[conns[down]] = nodes[i]; //z powrotem
	    nodes[down]->val[conns[down]] = temp;
	    conns[down]++;
	}
	if( up >= 0 && conns[i] < nodes[i]->ways) { //zaznacz sciezke w gore i z powrotem
	    double temp = ( (double)rand()*( high-low ) ) / RAND_MAX + low;
	    nodes[i]->conn[conns[i]] = nodes[up]; //w gore
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[up]->conn[conns[up]] = nodes[i]; //z powrotem
	    nodes[up]->val[conns[up]] = temp;
	    conns[up]++;
	}
	if( left % width != width-1 && left > 0 && conns[i] < nodes[i]->ways ) { //zaznacz sciezke w lewo i z powrotem
	    double temp = ( (double)rand()*( high-low ) ) / RAND_MAX + low;
	    nodes[i]->conn[conns[i]] = nodes[left];//w lewo
	    nodes[i]->val[conns[i]] = temp;
	    conns[i]++;
	    nodes[left]->conn[conns[left]] = nodes[i];//z powrotem
	    nodes[left]->val[conns[left]] = temp;
	    conns[left]++;
	}
	
    }
    graph.width = width;
    graph.len = len;
    graph.head = head;
    free( nodes );
    free( conns );
    return graph;
}

graph_t readFromFile( FILE *in ) {
	int gsize, x, i, j, k, maxw=4;
        double y;

        graph_t graph;

        if(fscanf(in, "%d %d", &graph.len, &graph.width) != 2)
                printf("Blad wczytywania z pliku");

        while(fgetc(in)!='\n'){}

        gsize = graph.width*graph.len;
 
        node_t *nodes_tmp = malloc(gsize *sizeof(node_t));

        int **conn_tmp = (int**)malloc(gsize *sizeof(int*));
        for(i=0; i<gsize; i++){
                conn_tmp[i] = (int*)malloc(maxw *sizeof(int));
        }

        double *val_tmp = malloc(maxw*sizeof(double));

        for(i=0; i<gsize; i++){
                k = 0;
    
                while((fgetc(in) != '\n') && (k<maxw)){
                        if(fscanf(in, "%d :%lf", &x, &y) != 2)
                                printf("Blad wczytywania z pliku");
                        conn_tmp[i][k] = x;
                        val_tmp[k] = y;
                        k++;
                }

                nodes_tmp[i] = FileMakeNode(k);
    
                nodes_tmp[i]->id = i;
    
                for(j=0; j<k; j++)
                        nodes_tmp[i]->val[j] = val_tmp[j];
    
                nodes_tmp[i]->ways = k;
        }    

        graph.head = nodes_tmp[0];

        for(i=0; i<gsize; i++){
                for(j=0; j<nodes_tmp[i]->ways; j++)
                        nodes_tmp[i]->conn[j] = nodes_tmp[conn_tmp[i][j]];
        }


        free(conn_tmp);
        free(val_tmp);
        free(nodes_tmp);
    

        return graph;
}

node_t findNode(graph_t *graph, int n ) {
        int d = 0, p = n, i, j;
        node_t temp = graph->head;

        while(p >= graph->width){
                p -= graph->width;
                d++;
        }

        for(i=0; i<d; i++){
                for(j=0; j<temp->ways; j++){
                        if(temp->id+graph->width == temp->conn[j]->id){
                                temp = temp->conn[j];
                                j=temp->ways;
                        }
                }
        }

        for(i=0; i<p; i++){
                for(j=0; j<temp->ways; j++){
                        if(temp->id+1 == temp->conn[j]->id){
                                temp = temp->conn[j];
                                j=temp->ways;
                        }
                }
        }

        return temp;
}

void printToFile( graph_t graph, FILE *out ) {
    if( graph.width == 1 && graph.len == 1 )
	return;
    int i, j, nodown, noright, down, right;
    node_t temp, head = graph.head;
    fprintf( out, "%d %d\n", graph.width, graph.len );
    while( 1 ) {
	nodown = 1;
	down = head->id + graph.width;
	temp = head;
	for( i= 0; i < head->ways; i++ ) { //sprawdzenie czy jestesmy w ostatnim rzedzie
	    if( head->conn[i]->id == down ) {
		nodown = 0;
		break;
	    }
	}
	while( 1 ) {
	    noright = 1;
	    right = temp->id + 1;
	    for( j= 0; j < temp->ways; j++ ) //wypisanie polaczen obecnego wezla
		fprintf( out, "\t%d: %g ", temp->conn[j]->id, temp->val[j] );
	    fprintf( out, "\n" );
	    for( j= 0; j < temp->ways; j++ ) //sprawdzenie czy ostatnia kolumna
		if( temp->conn[j]->id == right ) {
		    noright = 0;
		    break;
		}
	    if( noright || right == down ) //jezeli ostatnia kolumna to caly rzad wypisany
		break;
	    temp = temp->conn[j]; //jezeli nie to przejdz w prawo i kontynuuj
	}
	if( nodown ) //jezeli ostatni rzad to wszystko juz wypisane - przerwij
	    break;
	head = head->conn[i]; //jezeli nie to przejdz w dol i kontynuuj	
    }
}

void writeGraph(graph_t *graph, FILE *out){
        int i, j;

        node_t n = graph->head, tmp = NULL;

        for(i=0; i<graph->len; i++){
                if(tmp != NULL){
                        for(j=0; j<graph->width; j++) fprintf(out, " ^         ");
                        fprintf(out, "\n");
                        for(j=0; j<graph->width; j++) fprintf(out, " |         ");
                        fprintf(out,"\n");
                        for(j=0; j<graph->width; j++) {
                                fprintf(out, "%.2lf       ", tmp->val[findConnIndex(tmp, tmp->id+graph->width)]);
                                tmp = findNode(graph, tmp->id+1);
                        }
                        fprintf(out,"\n");
                        for(j=0; j<graph->width; j++) fprintf(out, " |         ");
                        fprintf(out,"\n");
                        for(j=0; j<graph->width; j++) fprintf(out, " v         ");
                        fprintf(out,"\n");
                        }    

                tmp = n;
                for(j=0; j<graph->width; j++){
                        fprintf(out, "[%d]", n->id);
                        if((n->id+1) % graph->width != 0){ 
                                fprintf(out, "<-");
                                fprintf(out, "%.2lf", n->val[findConnIndex(n, n->id+1)]);
                                fprintf(out, "->");
                        }
                        n = findNode(graph, n->id+1);
                }
                fprintf(out,"\n");
        }
}

int findConnIndex(node_t node, int a) {
        int i;

        for(i=0; i<node->ways; i++){
                if(node->conn[i]->id == a)
                        return i;
        }
    
        return EXIT_FAILURE;
}


void divideGraph( graph_t *graph );

void freeGraph( graph_t graph ) {
    node_t tempd, tempr, head = graph.head;
    int i, j, nodown, noright, down, right;
    graph.head = NULL;
    while( head != NULL ) {

	down = head->id + graph.width;
	nodown = 1;
	for( i= 0; i < head->ways; i++ ) { //sprawdzenie czy jestesmy w ostatnim rzedzie
	    if( head->conn[i]->id == down ) {
		nodown = 0;
		break;
	    }
	}

	if( !nodown ) //jezeli nie ostatni rzad
	    tempd = head->conn[i]; //tymczasowo przechowujemy adres wezla nizej
	else //w przeciwnym przypadku
	    tempd = NULL; //ustawiamy kolejny wezel na null zeby petla sie zakonczyla

	while( head != NULL ) {
	    
	    right = head->id + 1;
	    noright = 1;
	    for( j= 0; j < head->ways; j++ ) //sprawdzenie czy ostatnia kolumna
		if( head->conn[j]->id == right ) {
		    noright = 0;
		    break;
		}

	    if( !noright ) //jezeli nie ostatnia kolumna
		tempr = head->conn[j]; //tymczasowo przechowujemy adres kolejnego wezla
	    else //jezeli ostania
		tempr = NULL; //ustawiamy kolejny wezel na null zeby petla sie zakonczyla
	    
	    free( head->val ); //zwalniamy zaalokowana pamiec
	    free( head->conn );
	    free( head );

	    head = tempr; //przechodzimy w prawo
	}
	head = tempd; //przechodzimy w dol
    }
}
