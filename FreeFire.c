#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ======================
// Estruturas
// ======================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ======================
// Funções - Mochila Vetor
// ======================
void inserirItemVetor(Item mochila[], int *n, Item novo) {
    mochila[*n] = novo;
    (*n)++;
}

void removerItemVetor(Item mochila[], int *n, char nome[]) {
    for(int i = 0; i < *n; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            for(int j = i; j < *n - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*n)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void listarVetor(Item mochila[], int n) {
    if(n == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int n, char nome[], int *comparacoes) {
    *comparacoes = 0;
    for(int i = 0; i < n; i++) {
        (*comparacoes)++;
        if(strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(Item mochila[], int n) {
    Item temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("Mochila ordenada!\n");
}

int buscarBinariaVetor(Item mochila[], int n, char nome[], int *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while(inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, nome);

        if(cmp == 0) return meio;
        else if(cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ======================
// Funções - Mochila Lista Encadeada
// ======================
void inserirItemLista(No **inicio, Item novo) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = *inicio;
    *inicio = novoNo;
}

void removerItemLista(No **inicio, char nome[]) {
    No *atual = *inicio, *anterior = NULL;
    while(atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }
    if(anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Item removido com sucesso!\n");
}

void listarLista(No *inicio) {
    if(inicio == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    No* atual = inicio;
    while(atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(No *inicio, char nome[], int *comparacoes) {
    *comparacoes = 0;
    No* atual = inicio;
    while(atual != NULL) {
        (*comparacoes)++;
        if(strcmp(atual->dados.nome, nome) == 0) {
            return 1; // encontrado
        }
        atual = atual->proximo;
    }
    return 0;
}

// ======================
// Função Principal (Menu)
// ======================
int main() {
    Item mochilaVetor[100];
    int n = 0; // quantidade no vetor
    No* mochilaLista = NULL;

    int opcaoMochila, opcao, comp, pos;
    Item novo;
    char nomeBusca[30];

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Mochila com VETOR\n");
        printf("2 - Mochila com LISTA\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcaoMochila);
        getchar();

        if(opcaoMochila == 1) {
            do {
                printf("\n--- Mochila Vetor ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial\n");
                printf("5 - Ordenar\n");
                printf("6 - Buscar binaria\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                switch(opcao) {
                    case 1:
                        printf("Nome: "); fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = 0;
                        printf("Tipo: "); fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = 0;
                        printf("Quantidade: "); scanf("%d", &novo.quantidade); getchar();
                        inserirItemVetor(mochilaVetor, &n, novo);
                        break;
                    case 2:
                        printf("Nome para remover: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                        removerItemVetor(mochilaVetor, &n, nomeBusca);
                        break;
                    case 3:
                        listarVetor(mochilaVetor, n);
                        break;
                    case 4:
                        printf("Nome para buscar: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                        pos = buscarSequencialVetor(mochilaVetor, n, nomeBusca, &comp);
                        if(pos != -1) printf("Item encontrado! Comparacoes: %d\n", comp);
                        else printf("Nao encontrado. Comparacoes: %d\n", comp);
                        break;
                    case 5:
                        ordenarVetor(mochilaVetor, n);
                        break;
                    case 6:
                        printf("Nome para buscar (binaria): "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                        pos = buscarBinariaVetor(mochilaVetor, n, nomeBusca, &comp);
                        if(pos != -1) printf("Item encontrado! Comparacoes: %d\n", comp);
                        else printf("Nao encontrado. Comparacoes: %d\n", comp);
                        break;
                }
            } while(opcao != 0);

        } else if(opcaoMochila == 2) {
            do {
                printf("\n--- Mochila Lista ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                switch(opcao) {
                    case 1:
                        printf("Nome: "); fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = 0;
                        printf("Tipo: "); fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = 0;
                        printf("Quantidade: "); scanf("%d", &novo.quantidade); getchar();
                        inserirItemLista(&mochilaLista, novo);
                        break;
                    case 2:
                        printf("Nome para remover: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                        removerItemLista(&mochilaLista, nomeBusca);
                        break;
                    case 3:
                        listarLista(mochilaLista);
                        break;
                    case 4:
                        printf("Nome para buscar: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                        if(buscarSequencialLista(mochilaLista, nomeBusca, &comp))
                            printf("Item encontrado! Comparacoes: %d\n", comp);
                        else
                            printf("Nao encontrado. Comparacoes: %d\n", comp);
                        break;
                }
            } while(opcao != 0);
        }

    } while(opcaoMochila != 0);

    printf("Encerrando...\n");
    return 0;
}
