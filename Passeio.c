#include "Passeio.h"
#include <stdio.h>
#include <stddef.h>
int ehpasseio(Grafo g, int tam, int vet[]){
    int** matriz = getMatriz(g);
    for (int i = 0; i < tam - 1; i++){
        int u = vet[i];
        int v = vet[i+1];
        // Isso para deixar o grafo direcionado e não atrapalhar os algoritmos de caminho minimo
        if(matriz[u][vet[v]] == 0 && matriz[v][u] == 0)
        return 0;
    }
    return 1;
    
}
int ehtrilha(Grafo g, int tam, int vet[]){
    if(!ehpasseio(g, tam, vet)) return 0;
    // Saber o maior número de vértice q passa no vetor
    int max_vertices = 0;
    for (int i = 0; i < tam; i++){
        if(vet[i] > max_vertices){
            max_vertices = vet[i];
        }
    }
    int arestas_visitadas[max_vertices + 1][max_vertices + 1];
    for (int i = 0; i <= max_vertices; i++){
        for (int j = 0; j <= max_vertices; j++){
            arestas_visitadas[i][j] = 0;
        }
    }
    for (int i = 0; i < tam - 1; i++){
        int u = vet[i];
        int v = vet[i + 1];
        if(arestas_visitadas[u][v] == 1) return 0;

    arestas_visitadas[u][v] = 1;
    arestas_visitadas[v][u] = 1;
    }
    return 1;
}
int ehcircuito(Grafo g, int tam, int vet[]){
    if(!ehtrilha(g, tam, vet)) return 0;
    // Descobrir se o último é igual o primeiro
    if(vet[0] != vet[tam - 1]) return 0;
    return 1;
}
int ehcaminho(Grafo g, int tam, int vet[]){

    if(!ehpasseio(g, tam, vet)) return 0;
    if(!ehtrilha(g, tam, vet)) return 0;
    int max = 0;
    for (int i = 0; i < tam; i++){
        if(vet[i] > max){
            max = vet[i];
        }
    }
    int vertices_visitados[max + 1];
    for (int i = 0; i <= max; i++){
        vertices_visitados[i] = 0;
    }
    
    for (int i = 0; i < tam; i++){
        if(vertices_visitados[vet[i]] == 1)
            return 0; // Achou vértice repetido
        
        vertices_visitados[vet[i]] = 1;

    }

    return 1;
}
int ehciclo(Grafo g, int tam, int vet[]){
    if (!ehpasseio(g, tam, vet)) return 0;
    if (!ehtrilha(g, tam, vet)) return 0; 
    if (tam < 3) return 0;
    // Descobrir se o último é igual o primeiro
    if (vet[0] != vet[tam - 1]) return 0;

    return 1;
}
void imprimeVetor(int tam, int vet[]) {
    printf("[");
    for (int i = 0; i < tam; i++) {
        printf("%d", vet[i]);
        if (i < tam - 1) {
            printf(", ");
        }
    }
    printf("]");
}
void testarPasseio(Grafo g, int tam, int vet[], const char* nomeTeste) {
    printf("\n--- Testando: %s ---", nomeTeste);
    printf("\nPasseio: ");
    imprimeVetor(tam, vet);
    printf("\n");

    // Teste 1: ehpasseio
    if (ehpasseio(g, tam, vet)) {
        printf("1. É um passeio?   (SIM)\n");
    } else {
        printf("1. É um passeio?   (NÃO)\n");
    }

    // Teste 2: ehtrilha
    if (ehtrilha(g, tam, vet)) {
        printf("2. É uma trilha?   (SIM) (Não repetiu arestas)\n");
    } else {
        printf("2. É uma trilha?   (NÃO) (Repetiu arestas)\n");
    }

    // Teste 3: ehcaminho
    if (ehcaminho(g, tam, vet)) {
        printf("3. É um caminho?   (SIM) (Não repetiu vértices)\n");
    } else {
        printf("3. É um caminho?   (NÃO) (Repetiu vértices)\n");
    }

    // Teste 4: ehciclo
    if (ehciclo(g, tam, vet)) {
        printf("4. É um ciclo?     (SIM) (Trilha fechada)\n");
    } else {
        printf("4. É um ciclo?     (NÃO)\n");
    }
}