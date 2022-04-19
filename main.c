#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"
#include "graph.h"

#define DEFAULT_FROM 0
#define DEFAULT_TO 1
#define DEFAULT_WIDTH 10
#define DEFAULT_LENGHT 10
#define DEFAULT_DOWN 0
#define DEFAULT_UP 10
#define DEFAULT_NB_OF_GRAPHS 1

#define FROM_NODE 'f'
#define TO_NODE 't'
#define WIDTH 'x'
#define LENGHT 'y'
#define DOWN 'a'
#define UP 'b'
#define NB_GRAPHS 'n'
#define OUT_FILE 'o'
#define IN_FILE 'i'

int main( int argc, char *argv[] ) {
    int opt;
    int from = DEFAULT_FROM;
    int to = DEFAULT_TO;
    int width = DEFAULT_WIDTH;
    int len = DEFAULT_LENGHT;
    int n = DEFAULT_NB_OF_GRAPHS;
    double down = DEFAULT_DOWN;
    double up = DEFAULT_UP;	
    FILE *in = NULL, *out = NULL;
    char decision;
    graph_t graph;
    while(( opt = getopt( argc, argv, "-:f:t:x:y:a:b:n:o:i:" )) != -1 ) {
	switch( opt ) {
	    case FROM_NODE:
		from = atoi( optarg );
		break;
	    case TO_NODE:
		to = atoi( optarg );
		break;
	    case WIDTH:
		width = atoi( optarg );
		break;
	    case LENGHT:
		len = atoi( optarg );
		break;
	    case DOWN:
		down = atoi( optarg );
		break;
	    case UP:
		up = atoi( optarg );
		break;
	    case NB_GRAPHS:
                n = atoi( optarg );
		break;
	    case OUT_FILE:
		if( !access( optarg, F_OK ) ) {
		    printf( "FILENAME_TAKEN: %s\n", optarg );
		    while( decision != 'y' && decision != 'n' ) {
			printf( "Override? (y/n): ");
			scanf( " %c", &decision );
		    }
		    if( decision == 'n' )
			return FILENAME_TAKEN;
		}

		out = fopen( optarg, "w" );
		if( out == NULL ) {
		    fprintf( stderr, "INPUT_ERR: %s\n", optarg );
		    return INPUT_ERR;
		}
		break;
	    case IN_FILE:
		in = fopen( optarg, "r" );
		if( in == NULL ) {
		    fprintf( stderr, "INPUT_ERR: %s\n", optarg );
		    return INPUT_ERR;
		}
		break;
	    case '?':
		fprintf( stderr, "UNKNOWN_FALG: %c\n", optopt );
		instructionMsg( argv[0] );
		return UNKNOWN_FLAG;
		break;
	    case ':':
		fprintf( stderr, "NO_ARG: %c\n", optopt );
		instructionMsg( argv[0] );
		return NO_ARG;
		break;
	    case 1:
		fprintf( stderr, "AMBIGUOUS_OUT: %s\n", optarg );
		instructionMsg( argv[0] );
		return AMBIGOUS_OUT;
		break;
	}
    }

    if( (in == NULL && out == NULL) || (in != NULL && out != NULL) ) { 
	fprintf( stderr, "INCORRECT_NUMBER_OF_ARGS\n" );
	instructionMsg( argv[0] );
	return INCORRECT_NUMBER_OF_ARGS;
    }

    if( out == NULL ) {
	up = readFromFile(&graph, in);//wczytaj graf z pliku
	width = graph.width[0];
	len = graph.len[0];
    }
	
    if( width < 0 || len < 0 || down < 0 || up < 0 ) { //sprawdzenie poprawnosci podanych danych
	fprintf( stderr, "NOT_POSITIVE_NB \n");
	return NOT_POSITIVE_NB;
    }

    if( from < 0 || to < 0 || from >= width*len || to >= width*len ) { //sprawdzenie poprawnosci podanych wezlow
	fprintf( stderr, "NO_PATH!\n" );
	return NO_PATH;
    }

    if( in == NULL ) {
	graph = genFromParams( width, len, down, up );
    }

    printf("\nStarting graph:\n");

    writeGraph(&graph, stdout, 0);
        printf("\n");
	
    int i;

    if(n < 0 || n > width){
        printf("INCORRECT_NB_OF_GRAPHS\n");
        exit( INCORRECT_NB_OF_GRAPHS );
    } else {
            if(n > 1){
                divideGraph(&graph, n);
                for(i=0; i<graph.n; i++){
                        printf("Graph %d:\n", i+1);
                        writeGraph(&graph, stdout, i);
                        printf("\n");
                }
        }
    }

    printToFile( graph, out );
    fclose( out );

    if( checkIntegrity( graph ) )
	printf( "Graf is connected\n" );
    else 
	printf("Graf is not connected\n");

    printf("\nPath: ");

    if(from != to){
    	path p = findPath(&graph, from, to, up);//znajdz droge

    	for(i=0; i<p->n_nb-1; i++)
            printf("%d -> ", p->nodes[i]->id);
    	printf("%d", p->nodes[p->n_nb-1]->id);

    	printf("\nLenght: %lf\n", p->val_s);
    } else {
	printf("%d", from);
    	printf("\nLenght: 0\n");
    }

    for(i=0; i<graph.n; i++)
	freeGraph( graph, i );

}
