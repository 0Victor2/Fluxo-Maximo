# Fluxo Máximo em Grafos com Múltiplas Fontes e Escoadouros

Este projeto apresenta uma implementação do algoritmo de **Ford-Fulkerson** utilizando a estratégia de **Edmonds-Karp** (Busca em Largura - BFS) para computar o fluxo máximo em redes de transporte. O sistema foi projetado para lidar nativamente com múltiplas fontes e múltiplos escoadouros através da modelagem de uma super-fonte e um super-escoadouro com capacidades infinitas.

Trabalho desenvolvido como parte dos requisitos práticos da disciplina de **Algoritmos e Estrutura de Dados** do Programa de Pós-Graduação em Modelagem Computational (**PPGMC**) da Universidade Federal de Juiz de Fora (**UFJF**).

---

## 🚀 Estrutura do Projeto

O código-fonte é modular e está dividido nas seguintes estruturas:
* `main.c`: Ponto de entrada do programa, gerenciamento de argumentos e exibição dos resultados.
* `grafo.h` / `grafo.c`: Estrutura de dados para o grafo direcionado e lista de adjacências.
* `fila.h` / `fila.c`: Implementação de uma fila circular dinâmica para otimizar a BFS.
* `ff.h` / `ff.c`: Núcleo do algoritmo de Ford-Fulkerson.
* `leitura.h` / `leitura.c`: Leitura do arquivo de texto e montagem automática da topologia estendida.

---

## 🛠️ Como Compilar

Para compilar o projeto utilizando o `gcc`, execute o seguinte comando no seu terminal:

```bash
gcc main.c grafo.c fila.c ff.c leitura.c -o fluxo_maximo
```

## 💻 Como Rodar
O programa espera o caminho de um arquivo de texto de entrada contendo a descrição da rede de fluxo como parâmetro de linha de comando:

```bash
./fluxo_maximo testes/exemplo_entrada.txt
```

## 📝 Formato do Arquivo de Entrada:
O arquivo de texto que descreve o grafo deve seguir a seguinte especificação por linhas:

Número de nós originais da rede ($N$).

Número de arestas.

Número de fontes, seguido pelos índices de cada nó fonte.

Número de escoadouros, seguido pelos índices de cada nó escoadouro.

Arestas: Cada linha subsequente contém origem destino e capacidade.

Exemplo: 

```Plaintext
6
8
2 1 2
2 5 6
1 3 5
1 4 15
2 4 5
2 3 5
3 4 5
3 5 5
4 5 5
4 6 15
```

## ⚙️ Funcionamento Interno

Para resolver o problema com múltiplas fontes e escoadouros sem alterar o núcleo do algoritmo tradicional, a rotina de leitura mapeia o grafo original para uma topologia estendida contendo:

Super Fonte (Índice 0): Conectada a todas as fontes originais com capacidade infinita (INT_MAX).

Super Escoadouro (Índice $N + 1$): Conectada a todos os escoadouros originais com capacidade infinita (INT_MAX).

A busca em largura (BFS) garante uma complexidade de tempo de $O(V \cdot E^2)$, tornando o algoritmo independente dos valores das capacidades das arestas e imune a loops infinitos em caminhos residuais.
