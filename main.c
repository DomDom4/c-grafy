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
		    printf( "Nie udalo sie otworzyc pliku wyjsciowego\n" );
		    return 1;
		}
		break;
	    case 'i':
		in = fopen( optarg, "r" );
		if( in == NULL ) {
		    printf( "Nie udalo sie otworzyc pliku wejsciowego\n");
		    return 1;
		}
		break;
	    case '?':
		printf( "Bledna opcja: %c\n", optopt );
		instructionMsg( argv[0] );
		return 1;
		break;
	    case ':':
		printf( "Brak argumentu dla opcji: %c\n", optopt );
		instructionMsg( argv[0] );
		return 1;
		break;
	    case 1:
		printf( "Argument bez opcji: %s\n", optarg );
		instructionMsg( argv[0] );
		return 1;
		break;
	}
    }

    if( (in == NULL && out == NULL) || (in != NULL && out != NULL) ) { //sprawdzenie czy zostal wybrany sposob generowania grafu
	printf( "Nalezy podac plik wejsciowy lub wyjsciowy!\n" );
	instructionMsg( argv[0] );
	return 1;
    }

    if( szer < 0 || dlug < 0 || dolny < 0 || gorny < 0 || dolny > gorny ) { //sprawdzenie poprawnosci podanych danych
	printf( "Nieprawidlowa wartosc argumentu - liczba ujemna \n");
	return 1;
    }

    if( z < 0 || d < 0 || z >= szer*dlug || d >= szer*dlug ) { //sprawdzenie poprawnosci podanych wezlow
	printf( "Podany wezel nie nalezy do grafu!\n" );
	return 1;
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
