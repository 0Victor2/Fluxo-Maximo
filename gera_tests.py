import random

def gerar_benchmark_fluxo_sem_repeticao(nome_arquivo, num_nos, num_arestas, num_fontes, num_escoadouros):
    # Garante que temos nós suficientes para fontes e escoadouros distintos
    if num_fontes + num_escoadouros > num_nos:
        raise ValueError("O número de fontes + escoadouros não pode superar o total de nós.")
    
    # Limite teórico de arestas direcionadas sem auto-loop: n * (n - 1)
    limite_max_arestas = num_nos * (num_nos - 1)
    if num_arestas > limite_max_arestas:
        raise ValueError(f"Impossível gerar {num_arestas} arestas únicas para {num_nos} nós. O limite máximo é {limite_max_arestas}.")
    
    # Sorteia quais nós serão fontes e quais serão escoadouros
    todos_nos = list(range(1, num_nos + 1))
    random.shuffle(todos_nos)
    
    fontes = todos_nos[:num_fontes]
    escoadouros = todos_nos[num_fontes:num_fontes + num_escoadouros]
    
    # Dicionário para mapear (u, v) -> capacidade
    arestas_unicas = {}
    
    while len(arestas_unicas) < num_arestas:
        u = random.randint(1, num_nos)
        v = random.randint(1, num_nos)
        
        # Condições: não pode ser auto-loop E não pode já existir a aresta u -> v
        if u != v and (u, v) not in arestas_unicas:
            # Sorteia uma capacidade entre 1 e 100
            cap = random.randint(1, 100)
            arestas_unicas[(u, v)] = cap

    # Grava no formato exato aceito pelo leitura.c
    with open(nome_arquivo, 'w') as f:
        f.write(f"{num_nos}\n")
        f.write(f"{num_arestas}\n")
        
        # Fontes
        f.write(f"{num_fontes} " + " ".join(map(str, fontes)) + "\n")
        
        # Escoadouros
        f.write(f"{num_escoadouros} " + " ".join(map(str, escoadouros)) + "\n")
        
        # Lista de arestas únicas
        for (u, v), cap in arestas_unicas.items():
            f.write(f"{u} {v} {cap}\n")

    print(f"Benchmark '{nome_arquivo}' gerado com sucesso ({num_arestas} arestas estritamente únicas).")

# Exemplos de uso:
# 1. Teste Pequeno
gerar_benchmark_fluxo_sem_repeticao("teste_grande.txt", num_nos=1000, num_arestas=2000, num_fontes=10, num_escoadouros=5)

# 2. Teste de Estresse Intermediário
# gerar_benchmark_fluxo_sem_repeticao("teste_medio_limpo.txt", num_nos=500, num_arestas=3000, num_fontes=10, num_escoadouros=10)