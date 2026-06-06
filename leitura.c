#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para usar INT_MAX nas capacidades infinitas

#include "leitura.h"
#include "grafo.h"

Grafo* ler_arquivo_grafo(const char* nome_arquivo, int* super_fonte, int* super_escoadouro) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo '%s'.\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }

    int num_nos, num_arestas;
    
    // 1ª linha: número de nós originais
    if (fscanf(arquivo, "%d", &num_nos) != 1) {
        fprintf(stderr, "Erro ao ler o numero de nos.\n");
        exit(EXIT_FAILURE);
    }

    // 2ª linha: número de arestas
    if (fscanf(arquivo, "%d", &num_arestas) != 1) {
        fprintf(stderr, "Erro ao ler o numero de arestas.\n");
        exit(EXIT_FAILURE);
    }

    // Definindo a topologia estendida
    *super_fonte = 0;
    *super_escoadouro = num_nos + 1;
    int total_vertices = num_nos + 2; 

    // Instancia o grafo (deve alocar o array de listas de adjacência de 0 até total_vertices - 1)
    Grafo* grafo = inicializar_grafo(total_vertices);

    // 3ª linha: número de fontes e seus respectivos nós
    int num_fontes;
    fscanf(arquivo, "%d", &num_fontes);
    for (int i = 0; i < num_fontes; i++) {
        int id_fonte;
        fscanf(arquivo, "%d", &id_fonte);
        // Liga a Super Fonte à fonte original com capacidade "infinita"
        adicionar_aresta(grafo, *super_fonte, id_fonte, INT_MAX);
    }

    // 4ª linha: número de escoadouros e seus respectivos nós
    int num_escoadouros;
    fscanf(arquivo, "%d", &num_escoadouros);
    for (int i = 0; i < num_escoadouros; i++) {
        int id_escoadouro;
        fscanf(arquivo, "%d", &id_escoadouro);
        // Liga o escoadouro original ao Super Escoadouro com capacidade "infinita"
        adicionar_aresta(grafo, id_escoadouro, *super_escoadouro, INT_MAX);
    }

    // A partir da 5ª linha: nós de origem, destino e capacidade
    for (int i = 0; i < num_arestas; i++) {
        int origem, destino, capacidade;
        if (fscanf(arquivo, "%d %d %d", &origem, &destino, &capacidade) == 3) {
            adicionar_aresta(grafo, origem, destino, capacidade);
        } else {
            fprintf(stderr, "Aviso: Falha ao ler a aresta na linha %d.\n", i + 5);
        }
    }

    fclose(arquivo);
    return grafo;
}