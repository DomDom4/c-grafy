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

typedef struct graph {
    node_t head;
    int width;
    int len;
} graph_t;

typedef struct{
        node_t *nodes;
        int n_nb;
        double val_s;
} *path;

graph_t genFromParams( int x, int y, double a, double b ); //Generowanie grafu - szerokosc, wysokos, dolna waga, gorna waga

node_t makeNode( int width, int len, int current );

node_t fileMakeNode( int ways);

graph_t readFromFile( FILE *in ); //Czytanie z pliku

void printToFile( graph_t graph, FILE *out ); //Zapisanie do pliku

void divideGraph( graph_t *graph ); //Rozdzielanie na graf niespojny

node_t findNode(graph_t *graph, int n );

void freeGraph( graph_t graph );

int checkIntegrity( graph_t graph ); //BFS

path findPath( graph_t *graph, int start, int end, int maxval ); //Dijsktra

void writeGraph(graph_t *graph);

void infinity(double *d, int s, int n); 

void null(node_t *t, int n); 

#endif
