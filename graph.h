#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct node {
    int id; //numer wezla
    struct node **conn; //tablica polaczen
    double *val; //tablica wag przejsc, indeksy koreluja z **node.
    int ways; //ile polaczen ma dany wezel
} *node_t;

node_t genFromParams( int x, int y, double a, double b ); //Generowanie grafu - szerokosc, wysokos, dolna waga, gorna waga

node_t readFromFile( FILE *in ); //Czytanie z pliku

void printToFile( node_t graph ); //Zapisanie do pliku

void divideGraph( node_t *graph ); //Rozdzielanie na graf niespojny

void freeGraph( node_t graph );

int checkIntegrity( node_t graph ); //BFS

void findPath( node_t graph ); //Dijsktra

#endif
