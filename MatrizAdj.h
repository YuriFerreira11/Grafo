#ifndef GRAFO_INC_H
#define GRAFO_INC_H

struct grafo;
typedef struct grafo* Grafo;
Grafo criaGrafo(int vertices);
void adicionaAresta(Grafo g, int origem, int destino);
void adicionaArestaPeso(Grafo g, int origem, int destino, int peso);
void imprimeGrafo(Grafo g);
void liberarmemoria(Grafo g);
int** getMatriz(Grafo g);
int getNumVertices(Grafo g);
#endif