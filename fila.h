#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

typedef struct Fila {
    int* dados;      // Array dinâmico que armazenará os índices dos vértices
    int inicio;      // Índice do primeiro elemento
    int fim;         // Índice do último elemento
    int tamanho;     // Quantidade atual de elementos
    int capacidade;  // Capacidade máxima da fila (número total de vértices)
} Fila;

/*
 * Aloca a fila e o array interno de dados com a capacidade especificada.
 */
Fila* criar_fila(int capacidade);

/*
 * Adiciona um vértice no final da fila.
 */
void enfileirar(Fila* f, int valor);

/*
 * Remove e retorna o vértice do início da fila.
 */
int desenfileirar(Fila* f);

/*
 * Retorna true se a fila estiver vazia, false caso contrário.
 */
bool fila_vazia(Fila* f);

/*
 * Libera a memória do array interno e da estrutura da fila.
 */
void liberar_fila(Fila* f);

#endif // FILA_H