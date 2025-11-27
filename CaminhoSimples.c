#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "CaminhoSimples.h"
#include "MatrizAdj.h"

Caminho DIJKSTRA(Grafo g, int origem){
    int **matriz = getMatriz(g);
    int V = getNumVertices(g);
    Caminho c;

    int menor_dist = INT_MAX;
    c.dist = (int*)malloc(V * sizeof(int));
    c.pred = (int*)malloc(V * sizeof(int));

    c.Q = (int*)malloc(V * sizeof(int));
    for (int v = 0; v < V; v++){
        c.dist[v] = INT_MAX;
        c.pred[v] = -1;
        c.Q[v] = 0;
    }

    c.dist[origem] = 0;

    while(1){
        int u = -1; 
        menor_dist = INT_MAX;
        for (int i = 0; i < V; i++){
        if(c.dist[i] < menor_dist && c.Q[i] == 0){
            menor_dist = c.dist[i];
            u = i;
        }
    }
    if(u == -1 || menor_dist == INT_MAX) break;
    c.Q[u] = 1;
    

    for (int v = 0; v < V; v++) { 
        if (matriz[u][v] > 0) { 
            if(c.dist[v] > c.dist[u] + matriz[u][v]){
            c.dist[v] = c.dist[u] + matriz[u][v];
            c.pred[v] = u;
        }
        }
    }

}
    return c;
}
void testarDijkstra(Grafo g, int origem, const char* nomeTeste) {
    Caminho c = DIJKSTRA(g, origem);
    int V = getNumVertices(g);

    printf("\n--- DIJKSTRA: %s (Origem: %d) ---\n", nomeTeste, origem);
    for (int i = 0; i < V; i++) {
        if (c.dist[i] == INT_MAX)
            printf("dist[%d] = INF, pred[%d] = %d\n", i, i, c.pred[i]);
        else
            printf("dist[%d] = %d, pred[%d] = %d\n", i, c.dist[i], i, c.pred[i]);
    }

    free(c.dist);
    free(c.pred);
    free(c.Q); // ainda libera memória, mas não imprime
}





Caminho bellman_ford(Grafo g, int origem){
    int V = getNumVertices(g);
    int **matriz = getMatriz(g);
    Caminho c;
    c.dist = malloc(V * sizeof(int));
    c.pred = malloc(V * sizeof(int));
    c.Q    = malloc(V * sizeof(int)); // manter consistência

    for (int v = 0; v < V; v++){
        c.dist[v] = INT_MAX;
        c.pred[v] = -1;
        c.Q[v]    = 0;
    }
    c.dist[origem] = 0;
    
    for (int i = 0; i < V - 1; i++){ 
        bool trocou = false;
        for (int u = 0; u < V; u++){
            for (int v = 0; v < V; v++){
                int peso = matriz[u][v];
                if(peso > 0 && c.dist[u] != INT_MAX){
                    if(c.dist[v] > c.dist[u] + peso){
                        c.dist[v] = c.dist[u] + peso;
                        c.pred[v] = u;
                        trocou = true;
                    }
                }  
            }
        }
        if(!trocou) break;
    }

    // Verificação ciclo negativo
    for (int u = 0; u < V; u++){
        for (int v = 0; v < V; v++){
            int peso = matriz[u][v];
            if(peso != 0 && c.dist[u] != INT_MAX && c.dist[u] + peso < c.dist[v]){
                // apenas sinaliza erro
                free(c.dist);
                free(c.pred);
                free(c.Q);
                c.dist = NULL;
                c.pred = NULL;
                c.Q    = NULL;
                return c;
            }
        }
    }
    return c;
}
void testarBellmanFord(Grafo g, int origem, const char* nomeTeste) {
    Caminho c = bellman_ford(g, origem);
    int V = getNumVertices(g);

    if (c.dist == NULL) {
        printf("\n--- BELLMAN-FORD: %s ---\n", nomeTeste);
        printf("Erro: ciclo negativo detectado.\n");
        return;
    }

    printf("\n--- BELLMAN-FORD: %s (Origem: %d) ---\n", nomeTeste, origem);
    for (int i = 0; i < V; i++) {
        if (c.dist[i] == INT_MAX)
            printf("dist[%d] = INF, pred[%d] = %d\n", i, i, c.pred[i]);
        else
            printf("dist[%d] = %d, pred[%d] = %d\n", i, c.dist[i], i, c.pred[i]);
    }

    free(c.dist);
    free(c.pred);
    free(c.Q);
}




Caminho_Floyd floyd_warshall(Grafo g){
    int V = getNumVertices(g);
    int **matriz = getMatriz(g);
    Caminho_Floyd c;
    c.tamanho = V;

    c.dist = (int**)malloc(V * sizeof(int*));
    c.pred = (int**)malloc(V * sizeof(int*));

    for (int i = 0; i < V; i++){
        c.pred[i] = (int*)malloc(V * sizeof(int));
        c.dist[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++){
            
            int peso = matriz[i][j];
            if(i == j){
                c.dist[i][j] = 0;
                c.pred[i][j] = -1;
            }
            else if(peso != 0){
                c.dist[i][j] = peso;
                c.pred[i][j] = i;
            }
            else{
                c.dist[i][j] = INT_MAX;
                c.pred[i][j] = -1;
            }
        }
    }
    for (int k = 0; k < V; k++){
        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
        
                    if (c.dist[i][k] != INT_MAX && c.dist[k][j] != INT_MAX && c.dist[i][k] + c.dist[k][j] < c.dist[i][j]) {
                        c.dist[i][j] = c.dist[i][k] + c.dist[k][j];
                        c.pred[i][j] = c.pred[k][j];
                    }
                }
            }
        }
        return c;
    }

void testarFloydWarshall(Grafo g, const char* nomeTeste) {
    Caminho_Floyd t = floyd_warshall(g);
    int V = t.tamanho;

    printf("\n--- FLOYD-WARSHALL: %s (Todos os Pares) ---\n", nomeTeste);

    printf("\nMatriz de Distâncias:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (t.dist[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%3d ", t.dist[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz de Predecessores:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (t.pred[i][j] == -1)
                printf(" -  ");
            else
                printf("%3d ", t.pred[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < V; i++) {
        free(t.dist[i]);
        free(t.pred[i]);
    }
    free(t.dist);
    free(t.pred);
}