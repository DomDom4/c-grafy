#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "error.h"
#include "graph.c"

int main( int argc, char *argv[] ) {
    int opt;
    int szer = 10, dlug = 10, ilosc = 1, z, d;	//
    double dolny = 0, gorny = 10;		//domyslne wartosci
    FILE *in = NULL, *out = NULL;
    while(( opt = getopt( argc, argv, "-:z:d:x:y:a:b:n:o:i:" )) != -1 ) { //wczytane opcji
	switch( opt ) {
	    case 'z':
		z = atoi( optarg );
		break;
	    case 'd':
		d = atoi( optarg );
		break;
	    case 'x':
		szer = atoi( optarg );
		break;
	    case 'y':
		dlug = atoi( optarg );
		break;
	    case 'a':
		dolny = atoi( optarg );
		break;
	    case 'b':
		gorny = atoi( optarg );
		break;
	    case 'n':
		ilosc = atoi( optarg );
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

    if( szer < 0 || dlug < 0 || dolny < 0 || gorny < 0 ) { //sprawdzenie poprawnosci podanych danych
	printf( "NOT_POSITIVE_NB \n");
	return 5;
    }

    if( z < 0 || d < 0 || z >= szer*dlug || d >= szer*dlug ) { //sprawdzenie poprawnosci podanych wezlow
	printf( "NO_PATH!\n" );
	return 10;
    }

    if( in == NULL ) {
	//generuj graf
	//zapisz go do pliku
	//sprawdz czy spojny
	//znajdz droge
	;
    }
    if( out == NULL ) {
	//wczytaj graf z pliku
	//spradz czy spojny
	//znajdz droge
	;
    }

    

}
