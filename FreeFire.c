#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10  // Capacidade máxima da mochila

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens (mochila) e contador
Item mochila[MAX];
int qtdItens = 0;

// Função para inserir um novo item na mochila
void inserirItem() {
    if (qtdItens >= MAX) {
        printf("\n⚠️ A mochila está cheia!\n");
        return;
    }

    Item novo;

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo.nome);  // lê string com espaços

    printf("Digite o tipo do item (arma, municao, cura...): ");
    scanf(" %[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[qtdItens] = novo;
    qtdItens++;

    printf("\n✅ Item cadastrado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem() {
    if (qtdItens == 0) {
        printf("\n⚠️ A mochila está vazia, nada a remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < qtdItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Desloca os itens seguintes para "tapar o buraco"
        for (int i = encontrado; i < qtdItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        qtdItens--;
        printf("\n🗑️ Item removido com sucesso!\n");
    } else {
        printf("\n❌ Item não encontrado.\n");
    }
}

// Função para listar os itens cadastrados
void listarItens() {
    if (qtdItens == 0) {
        printf("\n📭 Mochila vazia.\n");
        return;
    }

    printf("\n--- Mochila do Jogador ---\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------\n");

    for (int i = 0; i < qtdItens; i++) {
        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função para buscar item pelo nome (busca sequencial)
void buscarItem() {
    if (qtdItens == 0) {
        printf("\n📭 Mochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < qtdItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
}

// Função principal com menu interativo
int main() {
    int opcao;

    do {
        printf("\n===== MENU - MOCHILA =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); listarItens(); break;
            case 2: removerItem(); listarItens(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("\n👋 Saindo do jogo...\n"); break;
            default: printf("\n⚠️ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
