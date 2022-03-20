#include "graph.h"

node_t makeNode( int width, int len, int current ) { //funkcja pomocnicza do funkcji generujacej
    node_t nd = malloc( sizeof nd );
    int ways;

    if( nd == NULL ) {
	printf( "NOT_ENOUGH_MEM\n" );
	exit( 11 );
    }

    //nadanie wlasnosci wezlowi
    nd->id = current;
    if( current == 0 || current == width*len-1 || current == width-1 || current == width*len-width ) { //rog
	ways = 2;
	nd->conn = malloc( ways * sizeof nd );
	nd->val = malloc( ways * sizeof nd->val );
    }
    else if( (current > 0 && current < width-1) || (current > width*len-width && current < width*len-1) || current % width == 0 || current % width == width-1 ) { //krawedz
	ways = 3;
	nd->conn = malloc( ways * sizeof nd );
	nd->val = malloc( ways * sizeof nd->val );
    }
    else { //srodek
	ways = 4;
	nd->conn = malloc( ways * sizeof nd );
	nd->val = malloc( ways * sizeof nd->val );
    }
    nd->ways = ways;
    if( nd->conn == NULL || nd->val == NULL ) {
	printf( "NOT_ENOUGH_MEM\n" );
	exit( 11 );
    }
    return nd;
}

node_t genFromParams( int width, int len, double a, double b ) { 
    srand( time ( NULL ));
    int i, high, low, last = width * len -1;
    node_t head, *nodes = malloc( last * sizeof nodes ); //tymczasowe przechowywanie adresow wezlow
    int *conns = malloc( last * sizeof conns ); //stan istniejacych polaczen dla kazdego wezla
    
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

    free( nodes );
    //free( conns );
    return head;
}

node_t readFromFile( FILE *in );

void printToFile( node_t graph, int width, int len, FILE *out ) {
    int i, j, nodown, noright, down, right;
    node_t temp;
    fprintf( out, "%d %d\n", width, len );
    while( 1 ) {
	nodown = 1;
	down = graph->id + width;
	temp = graph;
	for( i= 0; i < graph->ways; i++ ) { //sprawdzenie czy jestesmy w ostatnim rzedzie
	    if( graph->conn[i]->id == down ) {
		nodown = 0;
		break;
	    }
	}
	while( 1 ) {
	    noright = 1;
	    right = temp->id + 1;
	    fprintf( out, "%d:\t", temp->id ); //wypisanie obecnego wezla
	    for( j= 0; j < temp->ways; j++ ) //wypisanie polaczen obecnego wezla
		fprintf( out, "%d: %g ", temp->conn[j]->id, temp->val[j] );
	    fprintf( out, "\n" );
	    for( j= 0; j < temp->ways; j++ ) //sprawdzenie czy ostatnia kolumna
		if( temp->conn[j]->id == right ) {
		    noright = 0;
		    break;
		}
	    if( noright ) //jezeli ostatnia kolumna to caly rzad wypisany
		break;
	    temp = temp->conn[j]; //jezeli nie to przejdz w prawo i kontynuuj
	}
	if( nodown ) //jezeli ostatni rzad to wszystko juz wypisane - przerwij
	    break;
	graph = graph->conn[i]; //jezeli nie to przejdz w dol i kontynuuj
	
    }
}

void divideGraph( node_t *graph );

void freeGraph( node_t graph );
