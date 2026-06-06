#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "ff.h"
#include "fila.h"

// Funcao auxiliar para encontrar o minimo entre dois valores
static int min(int a, int b) {
    return (a < b) ? a : b;
}

/*
 * Busca em Largura (BFS) para encontrar um caminho aumentante no grafo residual.
 * O array 'parent' armazena ponteiros para as arestas, permitindo O(1) na atualizacao do fluxo.
 */
static bool bfs(Grafo* grafo, int fonte, int escoadouro, Aresta** parent) {
    int num_v = grafo->num_vertices;
    bool* visitado = (bool*)calloc(num_v, sizeof(bool));
    if (!visitado) {
        fprintf(stderr, "Erro de alocacao para o array de visitados.\n");
        exit(EXIT_FAILURE);
    }

    Fila* fila = criar_fila(num_v);
    
    enfileirar(fila, fonte);
    visitado[fonte] = true;
    parent[fonte] = NULL;

    bool alcancou_escoadouro = false;

    while (!fila_vazia(fila)) {
        int u = desenfileirar(fila);

        // Se chegamos no escoadouro, podemos parar a busca mais cedo
        if (u == escoadouro) {
            alcancou_escoadouro = true;
            break;
        }

        // Percorre a lista de adjacencia do vertice u
        Aresta* aresta_atual = grafo->adj[u];
        while (aresta_atual != NULL) {
            int v = aresta_atual->destino;
            int capacidade_residual = aresta_atual->capacidade - aresta_atual->fluxo;

            // Se o vizinho ainda nao foi visitado e a aresta tem capacidade residual
            if (!visitado[v] && capacidade_residual > 0) {
                enfileirar(fila, v);
                visitado[v] = true;
                parent[v] = aresta_atual; // Guarda a REFERENCIA da aresta
            }
            aresta_atual = aresta_atual->prox;
        }
    }

    // Libera as estruturas temporarias da BFS para evitar memory leaks
    free(visitado);
    liberar_fila(fila);

    return alcancou_escoadouro;
}

int ford_fulkerson(Grafo* grafo, int fonte, int escoadouro) {
    if (!grafo) return 0;

    int fluxo_maximo = 0;
    
    // Vetor de ponteiros de arestas para reconstruir o caminho
    Aresta** parent = (Aresta**)malloc(grafo->num_vertices * sizeof(Aresta*));
    if (!parent) {
        fprintf(stderr, "Erro de alocacao para o vetor parent.\n");
        exit(EXIT_FAILURE);
    }

    // Enquanto existir um caminho aumentante da fonte ao escoadouro
    while (bfs(grafo, fonte, escoadouro, parent)) {
        
        // 1. Encontrar a capacidade residual minima das arestas no caminho preenchido pela BFS (o gargalo)
        int gargalo = INT_MAX;
        int atual = escoadouro;
        
        while (atual != fonte) {
            Aresta* aresta_caminho = parent[atual];
            int capacidade_residual = aresta_caminho->capacidade - aresta_caminho->fluxo;
            gargalo = min(gargalo, capacidade_residual);
            
            // O vertice anterior no caminho eh a origem desta aresta reversa
            atual = aresta_caminho->reversa->destino; 
        }

        // 2. Atualizar as capacidades residuais das arestas e arestas reversas ao longo do caminho
        atual = escoadouro;
        while (atual != fonte) {
            Aresta* aresta_caminho = parent[atual];
            
            aresta_caminho->fluxo += gargalo;               // Aumenta o fluxo na direcao do caminho
            aresta_caminho->reversa->fluxo -= gargalo;      // Diminui o fluxo na direcao reversa (residual)
            
            atual = aresta_caminho->reversa->destino;
        }

        fluxo_maximo += gargalo;
    }

    free(parent);
    return fluxo_maximo;
}