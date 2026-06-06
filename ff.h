#ifndef FF_H
#define FF_H

#include "grafo.h"

/*
 * Executa o algoritmo de Ford-Fulkerson (utilizando a estrategia de Edmonds-Karp via BFS)
 * para encontrar o fluxo maximo entre o no fonte e o no escoadouro.
 * * Retorna o valor inteiro do fluxo maximo computado.
 */
int ford_fulkerson(Grafo* grafo, int fonte, int escoadouro);

#endif // FF_H