#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "MatrizAdj.h"
#include "Passeio.h"
#include "CaminhoSimples.h"

int main() {
    int vertices;
    int arestas, origem, destino, peso;
    int operacao_aresta;
    int operacao_dijkstra, operacao_bellmanford;
    int origem_teste;
    int operacao_floydwarshall;
    int *testes;

    printf("Quantidade de vertices: ");
    if (scanf_s("%d", &vertices) != 1 || vertices <= 0) return 1;
    Grafo g = criaGrafo(vertices);

    printf("Quantas arestas incluir: ");
    if (scanf_s("%d", &arestas) != 1) return 1;

    printf("Quer aresta com ou sem peso? (1 para peso e 2 para sem): ");
    if (scanf_s("%d", &operacao_aresta) != 1) return 1;

    // --- CRIAÇÃO DE ARESTAS (Interativa) ---
    printf("\n--- Inserindo %d arestas ---\n", arestas);
    for (int i = 0; i < arestas; i++) {
        printf("[%d/%d] Digite origem, destino", i + 1, arestas);
        if (operacao_aresta == 1) {
            printf(" e peso: ");
            if (scanf_s("%d %d %d", &origem, &destino, &peso) != 3 || peso == 0) {
                printf("Erro na leitura ou peso invalido (deve ser != 0). Ignorando esta aresta.\n");
                while(getchar() != '\n');
                i--;
                continue;
            }
            if (origem >= vertices || destino >= vertices) {
                printf("Vertice fora do limite.\n");
                i--;
                continue;
            }
            adicionaArestaPeso(g, origem, destino, peso);
        } else {
            printf(": ");
            if (scanf_s("%d %d", &origem, &destino) != 2) {
                 printf("Erro na leitura.\n");
                 while(getchar() != '\n');
                 i--; 
                 continue;
            }
            if (origem >= vertices || destino >= vertices) {
                printf("Vertice fora do limite.\n");
                i--;
                continue;
            }
            adicionaAresta(g, origem, destino); 
        }
    }
    
    imprimeGrafo(g);

    // --- TESTE DE ALGORITMOS DE CAMINHO MINIMO ---
    printf("\n\n--- TESTE DE ALGORITMOS DE CAMINHO MINIMO ---\n");

    // Teste 1: DIJKSTRA
    printf("Deseja testar DIJKSTRA? (1 para Sim / 0 para Nao): ");
    if (scanf_s("%d", &operacao_dijkstra) == 1 && operacao_dijkstra == 1) {
        printf("Digite o vertice de origem para Dijkstra: ");
        if (scanf_s("%d", &origem_teste) == 1 && origem_teste < vertices && origem_teste >= 0) {
             testarDijkstra(g, origem_teste, "Teste Dinamico");
        } else {
            printf("Origem invalida.\n");
        }
    }

    // Teste 2: BELLMAN-FORD
    printf("\nDeseja testar BELLMAN-FORD? (1 para Sim / 0 para Nao): ");
    if (scanf_s("%d", &operacao_bellmanford) == 1 && operacao_bellmanford == 1) {
        printf("Digite o vertice de origem para Bellman-Ford: ");
        if (scanf_s("%d", &origem_teste) == 1 && origem_teste < vertices && origem_teste >= 0) {
             testarBellmanFord(g, origem_teste, "Teste Dinamico");
        } else {
            printf("Origem invalida.\n");
        }
    }
    
    // Teste 3: FLOYD-WARSHALL (Todos os pares)
    printf("\nDeseja testar FLOYD-WARSHALL (Todos os Pares)? (1 para Sim / 0 para Nao): ");
    if (scanf_s("%d", &operacao_floydwarshall) == 1 && operacao_floydwarshall == 1) {
        testarFloydWarshall(g, "Todos os Pares");
    }

    // --- TESTE DE PASSEIOS ---
    int tamanho_teste, qnt_testes;
    int operacao_passeio;
    printf("\nQuer testar os passeios? (1 para sim e 0 para não) ");
    if (scanf_s("%d", &operacao_passeio) != 1) return 0;
    if (operacao_passeio == 1) {
        printf("Quantos testes querá testar? ");
        scanf_s("%d", &qnt_testes);
        for (int i = 0; i < qnt_testes; i++) {
            printf("Qual tamanho em vértices, do teste %d: ", i + 1);
            scanf_s("%d", &tamanho_teste);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            testes = malloc(tamanho_teste * sizeof(int));
            printf("Digite o passeio: ");
            for (int j = 0; j < tamanho_teste; j++) {
                scanf_s("%d", &testes[j]);
            }
            char nome_teste[50];
            sprintf_s(nome_teste, 50, "Teste %d", i + 1);
            testarPasseio(g, tamanho_teste, testes, nome_teste);
            free(testes);
        }
    }

    liberarmemoria(g);
    return 0;
}
