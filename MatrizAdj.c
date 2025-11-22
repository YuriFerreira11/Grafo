#include <stdio.h>
#include <stdlib.h>
#include "MatrizAdj.h"
struct grafo{
    int vertices;
    int arestas;
    int **matriz;
};
Grafo criaGrafo(int vertices) {
    Grafo g = (Grafo) malloc(sizeof(struct grafo));
    g->vertices = vertices;
    g->arestas = 0;
    g->matriz = (int**) malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        g->matriz[i] = (int*) calloc(vertices, sizeof(int));
    }

    return g;
}
void adicionaArestaPeso(Grafo g, int origem, int destino, int peso){

    if (g->matriz[origem][destino] == 0 && peso != 0) { 
        g->matriz[origem][destino] = peso;
        g->arestas++;
    }
}

void adicionaAresta(Grafo g, int origem, int destino) {
    adicionaArestaPeso(g, origem, destino, 1);
}
    

void imprimeGrafo(Grafo g) {
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++)
            printf("%3d ", g->matriz[i][j]);
        printf("\n");
    }
}
void liberarmemoria(Grafo g){
    for (int i = 0; i < g->vertices; i++){
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
    
}
int** getMatriz(Grafo g){
    return g->matriz;
}
int getNumVertices(Grafo g) {
    return g->vertices;
}