#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "leitura.h"
#include "ff.h"

int main(int argc, char *argv[]) {
    // Verifica se o arquivo de entrada foi passado como parâmetro
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int super_fonte, super_escoadouro;
    
    // 1. Constrói o grafo a partir do arquivo texto
    Grafo* grafo = ler_arquivo_grafo(argv[1], &super_fonte, &super_escoadouro);

    // 2. Executa o algoritmo de Ford-Fulkerson (Edmonds-Karp)
    int fluxo_maximo = ford_fulkerson(grafo, super_fonte, super_escoadouro);

    // 3. Imprime o fluxo máximo na saída padrão 
    printf("Fluxo Maximo: %d\n", fluxo_maximo);
    printf("------------------------------------\n");
    printf("Fluxo passando por cada vertice:\n");

    // 4. Calcula e imprime o fluxo que passa por cada vértice original 
    // Os vértices originais vão de 1 até (num_vertices - 2), 
    // pois o índice 0 é a Super Fonte e o último é o Super Escoadouro.
    int num_vertices_originais = grafo->num_vertices - 2;
    
    for (int i = 1; i <= num_vertices_originais; i++) {
        int fluxo_no_vertice = 0;
        
        Aresta* atual = grafo->adj[i];
        while (atual != NULL) {
            // Conta apenas o fluxo positivo nas arestas de saída originais
            // (Ignora as arestas residuais que foram criadas com capacidade 0)
            if (atual->capacidade > 0 && atual->fluxo > 0) {
                fluxo_no_vertice += atual->fluxo;
            }
            atual = atual->prox;
        }
        
        printf("Vertice %d: %d\n", i, fluxo_no_vertice);
    }

    // 5. Libera a memória alocada
    liberar_grafo(grafo);

    return EXIT_SUCCESS;
}