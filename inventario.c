#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_ARQUIVO "inventario.txt"

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

// Carrega produtos de um arquivo texto (se existir)
void carregar_arquivo(Produto **produtos, int *qtd) {
    FILE *f = fopen(NOME_ARQUIVO, "r");
    if (!f) {
        // Arquivo ainda não existe, começamos com lista vazia
        *produtos = NULL;
        *qtd = 0;
        return;
    }

    int capacidade = 0;
    *qtd = 0;
    *produtos = NULL;

    while (1) {
        Produto p;
        // Leitura: id nome quantidade preco (nome sem espaços)
        if (fscanf(f, "%d %49s %d %f", &p.id, p.nome, &p.quantidade, &p.preco) != 4) {
            break;
        }

        if (*qtd == capacidade) {
            capacidade = capacidade == 0 ? 4 : capacidade * 2;
            Produto *tmp = realloc(*produtos, capacidade * sizeof(Produto));
            if (!tmp) {
                printf("Erro de memoria ao carregar arquivo.\n");
                fclose(f);
                exit(1);
            }
            *produtos = tmp;
        }

        (*produtos)[*qtd] = p;
        (*qtd)++;
    }

    fclose(f);
}

// Salva produtos em arquivo texto
void salvar_arquivo(Produto *produtos, int qtd) {
    FILE *f = fopen(NOME_ARQUIVO, "w");
    if (!f) {
        printf("Nao foi possivel abrir arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(f, "%d %s %d %.2f\n",
                produtos[i].id,
                produtos[i].nome,
                produtos[i].quantidade,
                produtos[i].preco);
    }

    fclose(f);
}

// Busca indice de produto pelo ID
int buscar_produto(Produto *produtos, int qtd, int id) {
    for (int i = 0; i < qtd; i++) {
        if (produtos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Cadastra um novo produto, realocando o vetor dinamicamente
void cadastrar_produto(Produto **produtos, int *qtd) {
    Produto p;
    printf("ID do produto: ");
    scanf("%d", &p.id);

    // Evita IDs duplicados
    if (buscar_produto(*produtos, *qtd, p.id) != -1) {
        printf("Ja existe produto com esse ID.\n");
        return;
    }

    printf("Nome (sem espacos): ");
    scanf("%49s", p.nome);
    printf("Quantidade inicial: ");
    scanf("%d", &p.quantidade);
    printf("Preco: ");
    scanf("%f", &p.preco);

    Produto *tmp = realloc(*produtos, (*qtd + 1) * sizeof(Produto));
    if (!tmp) {
        printf("Erro de memoria ao cadastrar produto.\n");
        return;
    }

    *produtos = tmp;
    (*produtos)[*qtd] = p;
    (*qtd)++;

    printf("Produto cadastrado com sucesso!\n");
}

// Lista todos os produtos cadastrados
void listar_produtos(Produto *produtos, int qtd) {
    if (qtd == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- INVENTARIO ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Nome: %s | Quantidade: %d | Preco: R$ %.2f\n",
               produtos[i].id,
               produtos[i].nome,
               produtos[i].quantidade,
               produtos[i].preco);
    }
    printf("------------------\n");
}

// Atualiza a quantidade em estoque (entrada ou saída)
void atualizar_estoque(Produto *produtos, int qtd) {
    int id, delta;
    printf("ID do produto: ");
    scanf("%d", &id);

    int idx = buscar_produto(produtos, qtd, id);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Quantidade (positivo para entrada, negativo para saida): ");
    scanf("%d", &delta);

    if (produtos[idx].quantidade + delta < 0) {
        printf("Estoque insuficiente para essa saida.\n");
        return;
    }

    produtos[idx].quantidade += delta;
    printf("Estoque atualizado. Nova quantidade: %d\n", produtos[idx].quantidade);
}

int main() {
    Produto *produtos = NULL;
    int qtd = 0;
    int opcao;

    // Carrega inventario existente do arquivo, se houver
    carregar_arquivo(&produtos, &qtd);

    do {
        printf("\n=== INVENTARIO DE LOJA ===\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Atualizar estoque\n");
        printf("4 - Salvar e sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_produto(&produtos, &qtd);
                break;
            case 2:
                listar_produtos(produtos, qtd);
                break;
            case 3:
                atualizar_estoque(produtos, qtd);
                break;
            case 4:
                salvar_arquivo(produtos, qtd);
                printf("Inventario salvo. Encerrando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    free(produtos);
    return 0;
}
