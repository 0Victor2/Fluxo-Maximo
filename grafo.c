#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo* inicializar_grafo(int num_vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o grafo.\n");
        exit(EXIT_FAILURE);
    }
    
    grafo->num_vertices = num_vertices;
    grafo->adj = (Aresta**)malloc(num_vertices * sizeof(Aresta*));
    if (grafo->adj == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para as listas de adjacencia.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < num_vertices; i++) {
        grafo->adj[i] = NULL;
    }
    
    return grafo;
}

// Função auxiliar interna para instanciar uma nova aresta
static Aresta* criar_aresta(int destino, int capacidade) {
    Aresta* nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    if (nova_aresta == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para aresta.\n");
        exit(EXIT_FAILURE);
    }
    nova_aresta->destino = destino;
    nova_aresta->capacidade = capacidade;
    nova_aresta->fluxo = 0;
    nova_aresta->reversa = NULL;
    nova_aresta->prox = NULL;
    return nova_aresta;
}

void adicionar_aresta(Grafo* grafo, int origem, int destino, int capacidade) {
    // 1. Cria a aresta no sentido origem -> destino
    Aresta* aresta_direta = criar_aresta(destino, capacidade);
    
    // 2. Cria a aresta residual no sentido destino -> origem (capacidade inicial 0)
    Aresta* aresta_reversa = criar_aresta(origem, 0);
    
    // 3. Amarra os ponteiros reversos entre si
    aresta_direta->reversa = aresta_reversa;
    aresta_reversa->reversa = aresta_direta;
    
    // 4. Insere a aresta direta na lista de adjacência da origem (inserção no início)
    aresta_direta->prox = grafo->adj[origem];
    grafo->adj[origem] = aresta_direta;
    
    // 5. Insere a aresta reversa na lista de adjacência do destino (inserção no início)
    aresta_reversa->prox = grafo->adj[destino];
    grafo->adj[destino] = aresta_reversa;
}

void liberar_grafo(Grafo* grafo) {
    if (grafo == NULL) return;
    
    for (int i = 0; i < grafo->num_vertices; i++) {
        Aresta* atual = grafo->adj[i];
        while (atual != NULL) {
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    
    free(grafo->adj);
    free(grafo);
}