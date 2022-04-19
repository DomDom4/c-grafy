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
    node_t *head;
    int *width;
    int *len;
    int n;
} graph_t;

typedef struct{
        node_t *nodes;
        int n_nb;
        double val_s;
} *path;

void makeGraph(graph_t *graph, node_t head, int w, int l);

graph_t genFromParams( int x, int y, double a, double b ); //Generowanie grafu - szerokosc, wysokos, dolna waga, gorna waga

node_t makeNode( int width, int len, int current );

node_t fileMakeNode( int ways);

double readFromFile( graph_t *graph, FILE *in ); //Czytanie z pliku

void printToFile( graph_t graph, FILE *out ); //Zapisanie do pliku

node_t findNode(graph_t *graph, int n, int nn );

void freeGraph( graph_t graph, int nn );

int checkIntegrity( graph_t graph, int nn ); //BFS

path findPath( graph_t *graph, int start, int end, double maxval ); //Dijsktra

void divideGraph(graph_t *graph, int n); 

int wasDrawn(int *tab, int n, int a); 

void deleteConn(node_t node, int n); 

int findWidth(graph_t *graph, int n, int a, int gwidth);

void graphAdd(graph_t *graph, node_t node, int w, int l); 

void graphChangeSize(graph_t *graph, int n, int w, int l, int gpw);

void writeGraph(graph_t *graph, FILE *out, int nn);

int findConnIndex(node_t node, int a);

void infinity(double *d, int s, double n); 

void null(node_t *t, int n); 

#endif
