🔫🎒 Desafio Código da Ilha – Edição Free Fire
Projeto desenvolvido por Nathalia Bento Maciel

Bem-vindo ao Desafio Código da Ilha – Edição Free Fire!
Este projeto foi desenvolvido em linguagem C como parte da disciplina de Programação Estruturada, seguindo as instruções da empresa fictícia MateCheck.

O sistema simula o gerenciamento de uma mochila de sobrevivência em uma ilha misteriosa.
O jogador pode adicionar, remover, listar e buscar itens, com diferentes níveis de complexidade conforme o progresso no desafio.

🧭 Sobre o Projeto

O código implementa um sistema de mochila com 3 níveis de dificuldade:

🥉 Nível Novato

Adicionar itens (nome, tipo, quantidade)

Remover itens pelo nome

Listar todos os itens cadastrados

🥈 Nível Aventureiro

Inclui busca sequencial por nome

Exibe os detalhes completos do item encontrado

🥇 Nível Mestre

Adiciona o campo prioridade (1 a 5)

Permite ordenar os itens por nome, tipo ou prioridade

Implementa busca binária, com contagem de comparações e verificação de ordenação prévia

⚙️ Funcionalidades Técnicas Implementadas

Uso de struct para representar cada item da mochila

Vetor estático com capacidade para até 20 itens (#define MAX_ITENS 20)

Operações CRUD completas (Criar, Ler, Atualizar e Deletar)

Funções modulares (adicionarItem, removerItem, listarItens, buscarItemSequencial, ordenarItens, buscaBinaria)

Insertion Sort para ordenação

Busca binária otimizada com contador de comparações

Controle de entrada do usuário com limparBuffer() para evitar erros de leitura

Uso de stdbool.h para controle lógico (por exemplo, saber se a lista já está ordenada por nome)

🧩 Estrutura do Código
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;


Cada item da mochila contém:

nome: nome do item

tipo: categoria (ex: arma, alimento, item médico)

quantidade: número de unidades

prioridade: importância (1 = baixa, 5 = alta)

💻 Como Executar o Programa
🪟 No Windows (VS Code ou terminal)

Abra o terminal na pasta do projeto

Compile o programa com:

gcc mochila_freefire.c -o mochila


Execute:

./mochila

🐧 No Linux / Mac
gcc mochila_freefire.c -o mochila
./mochila

🧠 Conceitos Aplicados

Estruturas (struct)

Vetores e manipulação de dados

Controle de fluxo (switch, do-while)

Funções e modularização

Comparação de strings (strcmp)

Ordenação por inserção (Insertion Sort)

Busca binária (Binary Search)

Contagem de comparações para análise de desempenho

📈 Exemplo de Uso

Menu Principal:

=== Desafio Código da Ilha – Free Fire ===
1. Adicionar item
2. Remover item
3. Listar itens
4. Buscar item (sequencial)
5. Ordenar itens
6. Buscar item (binária por nome)
0. Sair


Saída de exemplo:

--- Itens na mochila (3) ---
Nome                 | Tipo       | Qtd   | Prioridade
Medkit               | Cura       | 2     | 4
AK47                 | Arma       | 1     | 5
Granada              | Arma       | 3     | 3

🏁 Conclusão

Ao concluir este projeto, foi possível:

Exercitar conceitos de estrutura de dados e algoritmos de busca e ordenação

Aplicar boas práticas de modularização em C

Entender a importância de organização e validação em programas interativos

“Cada linha de código é um passo a mais rumo à sobrevivência na ilha!” 🏝️

👩‍💻 Autoria e Créditos

Desenvolvido por: Nathalia Bento Maciel

Orientação: Equipe de Ensino – MateCheck

Curso: Sistemas de Informação – Estácio

Linguagem: C

Tema: Estruturas, Ordenação e Busca