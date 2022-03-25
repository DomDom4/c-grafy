#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "error.h"
#include "graph.h"

int main( int argc, char *argv[] ) {
    int opt;
    int width = 10, len = 10, nof = 1, f, t;	//
    double down = 0, up = 10;		//domyslne wartosci
    FILE *in = NULL, *out = NULL;
    graph_t graph;
    while(( opt = getopt( argc, argv, "-:f:t:x:y:a:b:n:o:i:" )) != -1 ) { //wczytane opcji
	switch( opt ) {
	    case 'f':
		f = atoi( optarg );
		break;
	    case 't':
		t = atoi( optarg );
		break;
	    case 'x':
		width = atoi( optarg );
		break;
	    case 'y':
		len = atoi( optarg );
		break;
	    case 'a':
		down = atoi( optarg );
		break;
	    case 'b':
		up = atoi( optarg );
		break;
	    case 'n':
		nof = atoi( optarg );
		break;
	    case 'o':
		out = fopen( optarg, "w" );
		if( out == NULL ) {
		    printf( "INPUT_ERR: %s\n", optarg );
		    return 3;
		}
		break;
	    case 'i':
		in = fopen( optarg, "r" );
		if( in == NULL ) {
		    printf( "INPUT_ERR: %s\n", optarg );
		    return 3;
		}
		break;
	    case '?':
		printf( "UNKNOWN_FALG: %c\n", optopt );
		instructionMsg( argv[0] );
		return 2;
		break;
	    case ':':
		printf( "NO_ARG: %c\n", optopt );
		instructionMsg( argv[0] );
		return 8;
		break;
	    case 1:
		printf( "AMBIGUOUS_OUT: %s\n", optarg );
		instructionMsg( argv[0] );
		return 7;
		break;
	}
    }

    if( (in == NULL && out == NULL) || (in != NULL && out != NULL) ) { //sprawdzenie czy zostal wybrany sposob generowania grafu
	printf( "INCORRECT_NUMBER_OF_ARGS\n" );
	instructionMsg( argv[0] );
	return 1;
    }

    if( width < 0 || len < 0 || down < 0 || up < 0 ) { //sprawdzenie poprawnosci podanych danych
	printf( "NOT_POSITIVE_NB \n");
	return 5;
    }

    if( f < 0 || t < 0 || f >= width*len || t >= width*len ) { //sprawdzenie poprawnosci podanych wezlow
	printf( "NO_PATH!\n" );
	return 10;
    }

    if( in == NULL ) {
	graph = genFromParams( width, len, down, up );
	printToFile( graph, out );
    }
    if( out == NULL ) {
	//wczytaj graf z pliku
	;
    }
	checkIntegrity( graph );
	//znajdz droge
}
