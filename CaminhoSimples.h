#ifndef CAMINHOSIMPLES_H
#define CAMINHOSIMPLES_H

#include "MatrizAdj.h"
#include <stddef.h>

// DIJKSTRA
void DIJKSTRA(Grafo g, int origem, int** dist_saida, int** pred_saida);
void testarDijkstra(Grafo g, int origem_dijkstra, const char* nomeTeste);

//Bellman_ford
void testarBellmanFord(Grafo g, int origem_bellmanford, const char* nomeTeste);
void bellman_ford(Grafo g, int origem, int** dist_saida, int** pred_saida);


//FloydWarshall
void floyd_warshal(Grafo g, int*** dist_saida, int*** pred_saida);
void testarFloydWarshall(Grafo g, const char* nomeTeste);
#endif