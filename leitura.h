#ifndef LEITURA_H
#define LEITURA_H

#include "grafo.h" // Necessário para reconhecer a struct Grafo

/*
 * Lê o arquivo de texto formatado e constrói o grafo em memória.
 * Retorna o ponteiro para o Grafo instanciado.
 * Os ponteiros super_fonte e super_escoadouro são preenchidos com
 * os índices gerados dinamicamente.
 */
Grafo* ler_arquivo_grafo(const char* nome_arquivo, int* super_fonte, int* super_escoadouro);

#endif // LEITURA_H