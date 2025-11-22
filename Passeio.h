#ifndef Passeio_h
#define Passeio_h
#include "MatrizAdj.h"

int ehpasseio(Grafo g, int tam, int vet[]);
int ehtrilha(Grafo g, int tam, int vet[]);
int ehcircuito(Grafo g, int tam, int vet[]);
int ehcaminho(Grafo g, int tam, int vet[]);
int ehciclo(Grafo g, int tam, int vet[]);
void imprimeVetor(int tam, int vet[]);;
void testarPasseio(Grafo g, int tam, int vet[], const char* nomeTeste);
#endif