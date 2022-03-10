#include "error.h"

#include <stdio.h>

void instructionMsg( char* progName ) {
    printf( "Prawidlowe uzycie programu:\n%s -z od_wezla -d do_wezla [-i plik_wejsciowy][[-x szerokosc][-y dlugosc][-a dolny_zakres][-b gorny_zakres][-n ilosc_grafow] -o plik_wyjsciowy] \n\t od - od ktorego wierzcholka szukamy drogi\n\t do - do ktorego wierzcholka szukamy drogi\n", progName );
}

