
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "CaminhoSimples.h"
#include "MatrizAdj.h"
typedef struct Caminho{
    int *dist;
    int *pred;
    int *Q;
}Caminho;

void DIJKSTRA(Grafo g, int origem, int** dist_saida, int** pred_saida){
    
    int V = getNumVertices(g);
    int u = -1; 
    int menor_dist = INT_MAX;
    *dist_saida = (int*)malloc(V * sizeof(int));
    *pred_saida = (int*)malloc(V * sizeof(int));
    int *dist = *dist_saida;
    int *pred = *pred_saida;
    int *Q = (int*)malloc(V * sizeof(int));
    for (int v = 0; v < V; v++){
        dist[v] = INT_MAX;
        pred[v] = -1;
    }

    
    
    for (int i = 0; i < V; i++){
        Q[i] = 0;
    }
    dist[origem] = 0;

    while(1){
        u = -1;
        menor_dist = INT_MAX;
        for (int i = 0; i < V; i++){
        if(dist[i] < menor_dist && Q[i] == 0){
            menor_dist = dist[i];
            u = i;
        }
    }
    if(u == -1 || menor_dist == INT_MAX) break;
    Q[u] = 1;
    int **matriz = getMatriz(g); // Acessa a matriz

    for (int v = 0; v < V; v++) { 
        if (matriz[u][v] > 0) { 
            if(dist[v] > dist[u] + matriz[u][v]){
            dist[v] = dist[u] + matriz[u][v];
            pred[v] = u;
        }
        }
    }

}
    free(Q);
}
void bellman_ford(Grafo g, int origem, int** dist_saida, int** pred_saida){
    int V = getNumVertices(g);
    int **matriz = getMatriz(g);

    *dist_saida = (int*)malloc(V * sizeof(int));
    *pred_saida = (int*)malloc(V * sizeof(int));
    int *dist = *dist_saida;
    int *pred = *pred_saida;

    for (int v = 0; v < V; v++){
        dist[v] = INT_MAX;
        pred[v] = -1;
    }
    dist[origem] = 0;
    
    for (int i = 0; i < V - 1; i++){ 
        bool trocou = false;
        for (int u = 0; u < V; u++){
            for (int v = 0; v < V; v++){
                int peso = matriz[u][v];
                if(peso > 0 && dist[u] != INT_MAX){
                if(dist[v] > dist[u] + peso){
                dist[v] = dist[u] + peso;
                pred[v] = u;
                trocou = true;
                }
            }  
        }
    }
        if(trocou == false){
            break;
        } 
    }
    for (int u = 0; u < V; u++){
        for (int v = 0; v < V; v++){
            
            int peso_uv = matriz[u][v];

            if (peso_uv != 0 && dist[u] != INT_MAX) {
                
                if (dist[v] > dist[u] + peso_uv) {
                    
                    // Ciclo negativo detectado! O caminho é indefinido.
                    printf("\n\nERRO DO BELLMAN-FORD: CICLO DE PESO NEGATIVO DETECTADO!\n");
                    
                    // Libera a memória alocada e retorna ponteiros NULL para sinalizar erro
                    free(*dist_saida);
                    free(*pred_saida);
                    *dist_saida = NULL;
                    *pred_saida = NULL;
                    return; 
                }
            }
        } 
    }
}

void floyd_warshal(Grafo g, int*** dist_saida, int*** pred_saida) {
    int V = getNumVertices(g);
    int **matriz = getMatriz(g);
    
    // Alocação inicial dos vetores de ponteiros
    *dist_saida = (int**)malloc(V * sizeof(int*));
    *pred_saida = (int**)malloc(V * sizeof(int*));

    if (*dist_saida == NULL || *pred_saida == NULL) {
        if (*dist_saida) free(*dist_saida);
        if (*pred_saida) free(*pred_saida);
        *dist_saida = NULL;
        *pred_saida = NULL;
        return; 
    }

    // Alocação das linhas da matriz (e tratamento de falha)
    for (int i = 0; i < V; i++) {
        (*dist_saida)[i] = (int*)malloc(V * sizeof(int));
        
        // Se a alocação de dist falhar, libera o que foi alocado e retorna NULL.
        if ((*dist_saida)[i] == NULL) { 
            for (int j = 0; j < i; j++) {
                free((*dist_saida)[j]);
                free((*pred_saida)[j]); // Libera pred alocado antes
            }
            free(*dist_saida);
            free(*pred_saida);
            *dist_saida = NULL;
            *pred_saida = NULL;
            return;
        }

        (*pred_saida)[i] = (int*)malloc(V * sizeof(int));
        
        // Se a alocação de pred falhar, libera tudo e retorna NULL.
        if ((*pred_saida)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*dist_saida)[j]);
                free((*pred_saida)[j]);
            }
            // Libera a última linha de dist que foi alocada com sucesso
            free((*dist_saida)[i]); 
            free(*dist_saida);
            free(*pred_saida);
            *dist_saida = NULL;
            *pred_saida = NULL;
            return;
        }
    }
    
    int **dist = *dist_saida;
    int **pred = *pred_saida;
    
    // 1. Inicialização das matrizes
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            int peso = matriz[i][j];
            if(i == j){
                dist[i][j] = 0;
                pred[i][j] = -1;
            }
            else if(peso != 0){
                dist[i][j] = peso;
                pred[i][j] = i;
            }
            else{
                dist[i][j] = INT_MAX;
                pred[i][j] = -1;
            }
        }
    }
    
    // 2. Lógica principal (três laços aninhados)
    for (int k = 0; k < V; k++){
        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
                    // Verifica se dist[i][k] e dist[k][j] são alcançáveis (evita overflow)
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }
void testarDijkstra(Grafo g, int origem_dijkstra, const char* nomeTeste) {
    int *dist_resultados = NULL;
    int *pred_resultados = NULL;
    int V = getNumVertices(g);

    printf("\n--- Testando DIJKSTRA: %s (Origem: %d) --- \n", nomeTeste, origem_dijkstra);

    // Chama o algoritmo (a função aloca a memória)
    DIJKSTRA(g, origem_dijkstra, &dist_resultados, &pred_resultados);

    if (dist_resultados != NULL) {
        printf("Distâncias (dist): ");
        for(int i = 0; i < V; i++) {
            if (dist_resultados[i] == INT_MAX) {
                printf("[%d]=INF ", i);
            } else {
                printf("[%d]=%d ", i, dist_resultados[i]);
            }
        }
        printf("\nPredecessores (pred): ");
        for(int i = 0; i < V; i++) {
            printf("[%d]=%d ", i, pred_resultados[i]);
        }
        printf("\n");
        
        // 🗑️ Limpeza de Memória (O testador é responsável pela memória alocada)
        free(dist_resultados);
        free(pred_resultados);
    } else {
        printf("Erro ao executar DIJKSTRA.\n");
    }
}
void testarBellmanFord(Grafo g, int origem_bellmanford, const char* nomeTeste) {
    int *dist_resultados = NULL;
    int *pred_resultados = NULL;
    int V = getNumVertices(g);

    printf("\n--- Testando BELLMAN-FORD: %s (Origem: %d) --- \n", nomeTeste, origem_bellmanford);

    // Chama o algoritmo (a função aloca a memória)
    bellman_ford(g, origem_bellmanford, &dist_resultados, &pred_resultados);

    if (dist_resultados != NULL) {
        printf("Distâncias (dist): ");
        for(int i = 0; i < V; i++) {
            if (dist_resultados[i] == INT_MAX) {
                printf("[%d]=INF ", i);
            } else {
                printf("[%d]=%d ", i, dist_resultados[i]);
            }
        }
        printf("\nPredecessores (pred): ");
        for(int i = 0; i < V; i++) {
            printf("[%d]=%d ", i, pred_resultados[i]);
        }
        printf("\n");
        
        // 🗑️ Limpeza de Memória (O testador é responsável pela memória alocada)
        free(dist_resultados);
        free(pred_resultados);
    } else {
        printf("Erro ao executar BELLMAN-FORD.\n");
    }
}
void testarFloydWarshall(Grafo g, const char* nomeTeste) {
    int V = getNumVertices(g);
    int **dist_resultados = NULL;
    int **pred_resultados = NULL;

    printf("\n--- Testando FLOYD-WARSHALL: %s (Todos os Pares) --- \n", nomeTeste);

    floyd_warshal(g, &dist_resultados, &pred_resultados);

    if (dist_resultados != NULL) {
        
        printf("Matriz de Distâncias (dist):\n");
        
        // Cabeçalho das colunas
        printf(" pos |");
        for(int j = 0; j < V; j++) {
            printf("%5d |", j);
        }
        printf("\n");
        
        // Separador
        printf("-----");
        for(int j = 0; j < V; j++) {
            printf("------");
        }
        printf("\n");

        for(int i = 0; i < V; i++) {
            printf("%4d |", i); // Cabeçalho da Linha
            for(int j = 0; j < V; j++) {
                if (dist_resultados[i][j] == INT_MAX) {
                    printf("  INF |");
                } else {
                    printf("%5d |", dist_resultados[i][j]);
                }
            }
            printf("\n");
        }
        
        // --- SAÍDA DA MATRIZ DE PREDECESSORES ---
        printf("\nMatriz de Predecessores (pred):\n");
        printf(" pos |");
        for(int j = 0; j < V; j++) {
            printf("%5d |", j);
        }
        printf("\n");
        
        // Separador
        printf("-----");
        for(int j = 0; j < V; j++) {
            printf("------");
        }
        printf("\n");

        for(int i = 0; i < V; i++) {
            printf("%4d |", i); // Cabeçalho da Linha
            for(int j = 0; j < V; j++) {
                if (pred_resultados[i][j] == -1) {
                    printf("    - |"); // Usa o hífen para -1
                } else {
                    printf("%5d |", pred_resultados[i][j]);
                }
            }
            printf("\n");
        }
        
        // Limpeza de Memória (Matrizes 2D)
        for(int i = 0; i < V; i++) {
            free(dist_resultados[i]);
            free(pred_resultados[i]);
        }
        free(dist_resultados);
        free(pred_resultados);
    } else {
        printf("Erro ao executar FLOYD-WARSHALL (Falha de alocação).\n");
    }
}