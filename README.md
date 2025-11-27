# Projeto de Grafo


Projeto para aulas de Algoritmos e Estruturas de Dados III (CSI115) na Universidade Federal de Ouro Preto no curso Sistemas de Informação.

O Projeto foca na representação de grafos e seus algoritmos.

## Matriz de Adjacência
Usa-se o grafo para armazenar a conexão de vértices com as arestas, sendo usado Grafos direcionais (Por simplicidade nos algoritmos de caminho)

## Percursos 
Usa-se grafos para reconhecer se há, no codigo está transformando grafos direcionais em não-direcionais para simplicidade.

* Passeio: Sequencia para verificar se há uma aresta no vértice selecionado, pode ser:
    * __Aberto__: quando começa e termina com vértices diferentes
    * __Fechado__: quando começa e termina no mesmo vértice. 
* __Trilha__: Passeio aberto no qual não há repetição de arestas.
* __Circuito__: Passeio fechado que não há repetição de arestas.
* __Caminho__: Trilha no qual não há repetição de arestas e vértices.
* __Ciclo__: Trilha no qual não há repetição de arestas e vértices, porém, começa e termina no mesmo vértice.
## Caminho mínimo
Determinar através de algoritmos, qual o menor caminho para um grafo.
* __Dijkstra__: Encontra o caminho mínimo de uma única origem para todos os outros vértices, não funciona com grafos com pesos negativos.
* __Bellman-Ford__: Similar ao Dijkstra, porém funciona com pesos negativos.
* __Floyd-Warshall__: Calcula a distância através de todos os pares de vértices desse grafo.
