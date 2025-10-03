/*
  torre_resgate - Módulo final do jogo: organização de componentes da torre de fuga.

  Funcionalidades:
  - Cadastro de até 20 componentes (nome, tipo, prioridade)
  - Ordenações:
      * Bubble Sort por nome (string)
      * Insertion Sort por tipo (string)
      * Selection Sort por prioridade (int)
  - Medição de comparações e tempo (clock)
  - Busca binária por nome (após ordenação por nome)
  - Menu interativo e exibição formatada
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade; // 1..10
} Componente;

/* --- Protótipos --- */
void limparBuffer();
void lerString(const char *prompt, char *dest, int tamanho);
void mostrarComponentes(Componente comps[], int n);
void bubbleSortNome(Componente comps[], int n, long *comparacoes, double *tempoSegundos);
void insertionSortTipo(Componente comps[], int n, long *comparacoes, double *tempoSegundos);
void selectionSortPrioridade(Componente comps[], int n, long *comparacoes, double *tempoSegundos);
int buscaBinariaPorNome(Componente comps[], int n, const char nomeBusca[], long *comparacoes);
void trocarComponente(Componente *a, Componente *b);

/* --- Funções auxiliares de IO --- */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Lê uma string com fgets e retira newline. Usa prompt antes. */
void lerString(const char *prompt, char *dest, int tamanho) {
    printf("%s", prompt);
    if (fgets(dest, tamanho, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    /* remover '\n' final */
    dest[strcspn(dest, "\n")] = '\0';
}

/* Exibe vetor de componentes formatado */
void mostrarComponentes(Componente comps[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("\n----- Componentes (total: %d) -----\n", n);
    printf("%-3s | %-25s | %-12s | %-9s\n", "No", "Nome", "Tipo", "Prioridade");
    printf("----+---------------------------+--------------+-----------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %-25s | %-12s | %-9d\n",
               i + 1, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
    printf("-------------------------------------------\n");
}

/* Troca dois componentes */
void trocarComponente(Componente *a, Componente *b) {
    Componente tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ========== Ordenações (cada função retorna número de comparações e tempo) ========== */

/* Bubble Sort por nome (ordenação lexicográfica crescente)
   Conta comparações de string (strcmp) como 1 cada vez que é invocada. */
void bubbleSortNome(Componente comps[], int n, long *comparacoes, double *tempoSegundos) {
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                trocarComponente(&comps[j], &comps[j+1]);
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização: se nada trocou, já está ordenado
    }

    clock_t fim = clock();
    *tempoSegundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/* Insertion Sort por tipo (string) - ordena por tipo lexicograficamente.
   Conta comparações de string. */
void insertionSortTipo(Componente comps[], int n, long *comparacoes, double *tempoSegundos) {
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < n; i++) {
        Componente chave = comps[i];
        int j = i - 1;
        // enquanto j >= 0 e comps[j].tipo > chave.tipo
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(comps[j].tipo, chave.tipo) > 0) {
                comps[j + 1] = comps[j];
                j--;
            } else {
                break;
            }
        }
        comps[j + 1] = chave;
    }

    clock_t fim = clock();
    *tempoSegundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/* Selection Sort por prioridade (int) - menor prioridade primeiro (ascendente).
   Conta comparações de inteiros (uma comparação por verificação de prioridade). */
void selectionSortPrioridade(Componente comps[], int n, long *comparacoes, double *tempoSegundos) {
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n - 1; i++) {
        int idxMenor = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (comps[j].prioridade < comps[idxMenor].prioridade) {
                idxMenor = j;
            }
        }
        if (idxMenor != i) trocarComponente(&comps[i], &comps[idxMenor]);
    }

    clock_t fim = clock();
    *tempoSegundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/* Busca binária por nome (aplicável somente se array estiver ordenado por nome).
   Conta comparações (cada strcmp comparando meio vs alvo conta como 1). 
   Retorna índice encontrado ou -1. */
int buscaBinariaPorNome(Componente comps[], int n, const char nomeBusca[], long *comparacoes) {
    *comparacoes = 0;
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        int cmp = strcmp(comps[meio].nome, nomeBusca);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* ========== Menu principal ========== */
int main() {
    Componente comps[MAX_COMP];
    int n = 0;

    int opcao;
    int ultimoSort = 0; 
    /* ultimoSort: 0 = nenhum, 1 = ordenado por nome (bubble),
                   2 = ordenado por tipo (insertion),
                   3 = ordenado por prioridade (selection) */

    printf("=== Módulo Final: Montagem da Torre de Resgate ===\n\n");

    do {
        printf("\nMenu principal:\n");
        printf("1 - Cadastrar componente (atual: %d/%d)\n", n, MAX_COMP);
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar (escolher algoritmo)\n");
        printf("4 - Buscar componente-chave (busca binária por nome - exige ordenação por nome)\n");
        printf("5 - Resetar componentes (limpar lista)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Encerrando.\n");
            return 1;
        }
        limparBuffer();

        if (opcao == 1) {
            if (n >= MAX_COMP) {
                printf("Capacidade máxima atingida (%d).\n", MAX_COMP);
            } else {
                Componente c;
                lerString("Nome do componente: ", c.nome, MAX_NOME);
                lerString("Tipo do componente (ex: controle, suporte, propulsao): ", c.tipo, MAX_TIPO);

                // prioridade entre 1 e 10:
                int p;
                do {
                    printf("Prioridade (1 - menor .. 10 - maior): ");
                    if (scanf("%d", &p) != 1) {
                        printf("Entrada inválida. Tente novamente.\n");
                        limparBuffer();
                        p = 0;
                    } else {
                        limparBuffer();
                        if (p < 1 || p > 10) {
                            printf("Prioridade deve estar entre 1 e 10.\n");
                        }
                    }
                } while (p < 1 || p > 10);
                c.prioridade = p;

                comps[n++] = c;
                printf("Componente cadastrado com sucesso! (total: %d)\n", n);
                ultimoSort = 0; // qualquer alteração invalida ordenação
            }
        }
        else if (opcao == 2) {
            mostrarComponentes(comps, n);
        }
        else if (opcao == 3) {
            if (n == 0) {
                printf("Nenhum componente cadastrado para ordenar.\n");
            } else {
                printf("\nEscolha o algoritmo de ordenação:\n");
                printf("1 - Bubble Sort (por NOME)\n");
                printf("2 - Insertion Sort (por TIPO)\n");
                printf("3 - Selection Sort (por PRIORIDADE)\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                int s;
                if (scanf("%d", &s) != 1) {
                    printf("Entrada inválida.\n");
                    limparBuffer();
                    continue;
                }
                limparBuffer();

                long comparacoes = 0;
                double tempo = 0.0;

                if (s == 1) {
                    bubbleSortNome(comps, n, &comparacoes, &tempo);
                    printf("Ordenacao por NOME (Bubble) concluida.\n");
                    printf("Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
                    ultimoSort = 1;
                } else if (s == 2) {
                    insertionSortTipo(comps, n, &comparacoes, &tempo);
                    printf("Ordenacao por TIPO (Insertion) concluida.\n");
                    printf("Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
                    ultimoSort = 2;
                } else if (s == 3) {
                    selectionSortPrioridade(comps, n, &comparacoes, &tempo);
                    printf("Ordenacao por PRIORIDADE (Selection) concluida.\n");
                    printf("Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
                    ultimoSort = 3;
                } else if (s == 0) {
                    // voltar
                } else {
                    printf("Opcao invalida.\n");
                }

                // mostrar resultado após ordenação
                if (s >=1 && s <=3) mostrarComponentes(comps, n);
            }
        }
        else if (opcao == 4) {
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
                continue;
            }
            if (ultimoSort != 1) {
                printf("A busca binaria por NOME exige que os componentes estejam ordenados por NOME (Bubble Sort).\n");
                printf("Deseja ordenar agora por NOME com Bubble Sort? (s/n): ");
                char resp = getchar();
                limparBuffer();
                if (resp == 's' || resp == 'S') {
                    long compOrd = 0;
                    double tm = 0.0;
                    bubbleSortNome(comps, n, &compOrd, &tm);
                    printf("Ordenacao por NOME realizada. Comparacoes: %ld | Tempo: %.6f s\n", compOrd, tm);
                    ultimoSort = 1;
                } else {
                    printf("Operacao de busca binaria cancelada. Ordene por nome antes.\n");
                    continue;
                }
            }

            char chave[MAX_NOME];
            lerString("Digite o NOME do componente-chave para buscar: ", chave, MAX_NOME);
            long compBusca = 0;
            int idx = buscaBinariaPorNome(comps, n, chave, &compBusca);
            if (idx != -1) {
                printf("Componente encontrado na posicao %d (1-based).\n", idx + 1);
                printf("Detalhes: Nome: %s | Tipo: %s | Prioridade: %d\n",
                       comps[idx].nome, comps[idx].tipo, comps[idx].prioridade);
                printf("Comparacoes da busca binaria: %ld\n", compBusca);
            } else {
                printf("Componente NAO encontrado. Comparacoes da busca binaria: %ld\n", compBusca);
            }
        }
        else if (opcao == 5) {
            // reset
            printf("Tem certeza que deseja limpar todos os componentes? (s/n): ");
            char r = getchar();
            limparBuffer();
            if (r == 's' || r == 'S') {
                n = 0;
                ultimoSort = 0;
                printf("Componentes resetados.\n");
            } else {
                printf("Operacao cancelada.\n");
            }
        }
        else if (opcao == 0) {
            printf("Saindo. Boa sorte na fuga!\n");
        }
        else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
