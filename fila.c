#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criar_fila(int capacidade) {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para a estrutura da Fila.\n");
        exit(EXIT_FAILURE);
    }
    
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = capacidade - 1; // Inicializa no final para que o primeiro enfileirar caia no índice 0
    f->tamanho = 0;
    
    f->dados = (int*)malloc(f->capacidade * sizeof(int));
    if (f->dados == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para os dados da Fila.\n");
        free(f);
        exit(EXIT_FAILURE);
    }
    
    return f;
}

void enfileirar(Fila* f, int valor) {
    if (f->tamanho == f->capacidade) {
        // Como a BFS em Max Flow nunca enfileira o mesmo vértice duas vezes 
        // no mesmo ciclo, a fila teoricamente nunca deve encher.
        fprintf(stderr, "Erro: Tentativa de enfileirar em fila cheia.\n");
        return;
    }
    
    // Aritmética modular para buffer circular
    f->fim = (f->fim + 1) % f->capacidade;
    f->dados[f->fim] = valor;
    f->tamanho++;
}

int desenfileirar(Fila* f) {
    if (fila_vazia(f)) {
        fprintf(stderr, "Erro: Tentativa de desenfileirar de fila vazia.\n");
        exit(EXIT_FAILURE); 
    }
    
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    
    return valor;
}

bool fila_vazia(Fila* f) {
    return (f->tamanho == 0);
}

void liberar_fila(Fila* f) {
    if (f != NULL) {
        if (f->dados != NULL) {
            free(f->dados);
        }
        free(f);
    }
}