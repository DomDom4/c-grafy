#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct node {
    int id; //numer wezla
    struct **node; //tablica polaczen
    double *val; //tablica wag przejsc, indeksy koreluja z **node.
} *node_t;

node_t genFromParams( int x, int y, double a, double b ); //Generowanie grafu - szerokosc, wysokos, dolna waga, gorna waga

node_t readFromFile( FILE *in ); //Czytanie z pliku

void printToFile( node_t graph ); //Zapisanie do pliku

void divideGraph( node_t *graph ); //Rozdzielanie na graf niespojny

int checkIntegrity( node_t graph ); //BFS

void findPath( node_t graph ); //Dijsktra

#endif
