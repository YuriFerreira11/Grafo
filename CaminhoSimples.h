#ifndef CAMINHOSIMPLES_H
#define CAMINHOSIMPLES_H

#include "MatrizAdj.h"
#include <stddef.h>
#include <limits.h>

typedef struct {
    int *dist;
    int *pred;
    int *Q;
}Caminho;
typedef struct {
    int **dist; 
    int **pred;
    int tamanho;
}Caminho_Floyd;

// --- DIJKSTRA ---
Caminho DIJKSTRA(Grafo g, int origem);
void testarDijkstra(Grafo g, int origem_dijkstra, const char* nomeTeste);

// --- BELLMAN-FORD ---
Caminho bellman_ford(Grafo g, int origem);
void testarBellmanFord(Grafo g, int origem_bellmanford, const char* nomeTeste);

// --- FLOYD-WARSHALL ---
Caminho_Floyd floyd_warshall(Grafo g);
void testarFloydWarshall(Grafo g, const char* nomeTeste);

#endif
