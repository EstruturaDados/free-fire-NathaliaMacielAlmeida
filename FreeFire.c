/*
  Desafio Código da Ilha – Edição Free Fire
  Sistema de mochila em C com 3 níveis:
  - Novato: CRUD básico (adicionar, remover, listar)
  - Aventureiro: inclui busca sequencial
  - Mestre: inclui prioridade, ordenação e busca binária
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 20

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // usado no nível Mestre (1..5)
} Item;

/* Protótipos */
void adicionarItem(Item mochila[], int *n);
void removerItem(Item mochila[], int *n);
void listarItens(Item mochila[], int n);
void buscarItemSequencial(Item mochila[], int n);
void ordenarItens(Item mochila[], int n, int criterio, long *comparacoes);
int buscaBinaria(Item mochila[], int n, char *chave, long *comparacoes);

/* Funções utilitárias */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Adicionar item */
void adicionarItem(Item mochila[], int *n) {
    if (*n >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: ");
    fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();
    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);
    limparBuffer();
    mochila[*n] = novo;
    (*n)++;
    printf("Item adicionado!\n");
}

/* Remover item pelo nome */
void removerItem(Item mochila[], int *n) {
    if (*n == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char alvo[30];
    printf("Nome do item a remover: ");
    fgets(alvo, 30, stdin); alvo[strcspn(alvo, "\n")] = '\0';
    for (int i = 0; i < *n; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            for (int j = i; j < *n - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*n)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

/* Listar itens */
void listarItens(Item mochila[], int n) {
    if (n == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("\n--- Itens na mochila (%d) ---\n", n);
    printf("%-20s | %-10s | %-5s | %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-10s | %-5d | %-10d\n",
               mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

/* Busca sequencial */
void buscarItemSequencial(Item mochila[], int n) {
    if (n == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char alvo[30];
    printf("Digite o nome do item para buscar: ");
    fgets(alvo, 30, stdin); alvo[strcspn(alvo, "\n")] = '\0';
    for (int i = 0; i < n; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            printf("Item encontrado: Nome=%s | Tipo=%s | Qtd=%d | Prioridade=%d\n",
                   mochila[i].nome, mochila[i].tipo,
                   mochila[i].quantidade, mochila[i].prioridade);
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

/* Ordenar itens (Insertion Sort) */
void ordenarItens(Item mochila[], int n, int criterio, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            int cmp = 0;
            if (criterio == 1) cmp = strcmp(mochila[j].nome, chave.nome);
            else if (criterio == 2) cmp = strcmp(mochila[j].tipo, chave.tipo);
            else if (criterio == 3) cmp = (mochila[j].prioridade - chave.prioridade);

            if (cmp > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j + 1] = chave;
    }
}

/* Busca binária (após ordenar por nome) */
int buscaBinaria(Item mochila[], int n, char *chave, long *comparacoes) {
    int ini = 0, fim = n - 1;
    *comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* ================= MENU PRINCIPAL ================= */
int main() {
    Item mochila[MAX_ITENS];
    int n = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n=== Desafio Codigo da Ilha – Free Fire ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        printf("5. Ordenar itens\n");
        printf("6. Buscar item (binaria por nome)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: adicionarItem(mochila, &n); ordenadoPorNome = false; break;
            case 2: removerItem(mochila, &n); ordenadoPorNome = false; break;
            case 3: listarItens(mochila, n); break;
            case 4: buscarItemSequencial(mochila, n); break;
            case 5: {
                printf("Ordenar por: 1=Nome | 2=Tipo | 3=Prioridade: ");
                int c; scanf("%d", &c); limparBuffer();
                long comp;
                ordenarItens(mochila, n, c, &comp);
                printf("Itens ordenados! Comparacoes: %ld\n", comp);
                if (c == 1) ordenadoPorNome = true;
                else ordenadoPorNome = false;
                listarItens(mochila, n);
            } break;
            case 6: {
                if (!ordenadoPorNome) {
                    printf("Primeiro ordene por nome!\n");
                    break;
                }
                char chave[30];
                printf("Nome do item para buscar: ");
                fgets(chave, 30, stdin); chave[strcspn(chave, "\n")] = '\0';
                long comp;
                int idx = buscaBinaria(mochila, n, chave, &comp);
                if (idx != -1)
                    printf("Item encontrado: %s | Tipo=%s | Qtd=%d | Prioridade=%d (comparacoes=%ld)\n",
                           mochila[idx].nome, mochila[idx].tipo,
                           mochila[idx].quantidade, mochila[idx].prioridade, comp);
                else
                    printf("Item nao encontrado (comparacoes=%ld).\n", comp);
            } break;
            case 0: printf("Saindo da ilha... Boa sorte, sobrevivente!\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while(opcao != 0);

    return 0;
}
