#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta {
    int destino;
    int capacidade;
    int fluxo;
    struct Aresta* reversa; // Ponteiro direto para a aresta residual
    struct Aresta* prox;    // Encadeamento da lista de adjacência
} Aresta;

typedef struct Grafo {
    int num_vertices;
    Aresta** adj; // Array de ponteiros para as listas encadeadas
} Grafo;

/*
 * Aloca a estrutura do grafo e o array de listas de adjacência.
 */
Grafo* inicializar_grafo(int num_vertices);

/*
 * Adiciona uma aresta direcionada no grafo e, automaticamente, 
 * cria a aresta residual (com capacidade 0) no sentido oposto.
 */
void adicionar_aresta(Grafo* grafo, int origem, int destino, int capacidade);

/*
 * Libera toda a memória alocada para os nós e para o grafo.
 */
void liberar_grafo(Grafo* grafo);

#endif // GRAFO_H