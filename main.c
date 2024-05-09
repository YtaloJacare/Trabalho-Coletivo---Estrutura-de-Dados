#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUARTOS 100
#define MAX_HOSPEDES 4
#define MAX_NOME 100

typedef struct {
    char numeroQuarto[MAX_NOME];
    char status[MAX_NOME];
    char listaHospedes[MAX_HOSPEDES][MAX_NOME];
    int quantHospedesQuarto;
} Quarto;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparString(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void iniciarLista(Quarto quarto[], int *posicaoQuarto) {
    FILE *arquivo = fopen("hospedes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    while (!feof(arquivo)) {
        fscanf(arquivo, "%s", quarto[*posicaoQuarto].numeroQuarto);
        fscanf(arquivo, "%s", quarto[*posicaoQuarto].status);

        for (int i = 0; i < MAX_HOSPEDES; i++) {
            fscanf(arquivo, "%s", quarto[*posicaoQuarto].listaHospedes[i]);
            if (strcmp(quarto[*posicaoQuarto].listaHospedes[i], "==========") == 0) {
                break;
            }
            quarto[*posicaoQuarto].quantHospedesQuarto++;
        }
        (*posicaoQuarto)++;
    }

    fclose(arquivo);
}

void reescreverLista(Quarto quarto[], int quantidadeQuartos) {
    FILE *arquivo = fopen("hospedes.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidadeQuartos; i++) {
        fprintf(arquivo, "%s\n", quarto[i].numeroQuarto);
        fprintf(arquivo, "%s\n", quarto[i].status);
        for (int j = 0; j < quarto[i].quantHospedesQuarto; j++) {
            fprintf(arquivo, "%s\n", quarto[i].listaHospedes[j]);
        }
        fprintf(arquivo, "%s\n", "==========");
    }
                                                                                            
    fclose(arquivo);
}

void inserirHospede(Quarto quarto[], int *posicaoQuarto) {
    int quartoVazio = -1;
    for (int i = 0; i < *posicaoQuarto; i++) {
        if (strcmp(quarto[i].status, "vazio") == 0) {
            quartoVazio = i;
            break;
        }
    }

    if (quartoVazio == -1) {
        printf("Não há quartos disponíveis.\n");
        return;
    }

    for (int i = 0; i < MAX_HOSPEDES; i++) {
        printf("Digite o nome do hóspede %d (ou 'fim' para encerrar): ", i + 1);
        fgets(quarto[quartoVazio].listaHospedes[i], MAX_NOME, stdin);
        limparString(quarto[quartoVazio].listaHospedes[i]);
        if (strcmp(quarto[quartoVazio].listaHospedes[i], "fim") == 0) {
            break;
        }
        quarto[quartoVazio].quantHospedesQuarto++;
    }
    strcpy(quarto[quartoVazio].status, "reservado");
    reescreverLista(quarto, *posicaoQuarto);
}

void buscarHospede(Quarto quarto[], int quantidadeQuartos) {
    char nomeProcurado[MAX_NOME];
    printf("Digite o nome do hóspede: ");
    scanf("%s", nomeProcurado);

    int encontrado = 0;
    for (int i = 0; i < quantidadeQuartos; i++) {
        for (int j = 0; j < quarto[i].quantHospedesQuarto; j++) {
            if (strcmp(quarto[i].listaHospedes[j], nomeProcurado) == 0) {
                printf("O hóspede está no quarto %s.\n", quarto[i].numeroQuarto);
                encontrado = 1;
                break;
            }
        }
    }
    if (!encontrado) {
        printf("O hóspede não foi encontrado.\n");
    }
}

void editarHospede(Quarto quarto[], int quantidadeQuartos) {
    char nomeEditar[MAX_NOME];
    printf("Digite o nome do hóspede que deseja editar: ");
    scanf("%s", nomeEditar);

    int encontrado = 0;
    for (int i = 0; i < quantidadeQuartos; i++) {
        for (int j = 0; j < quarto[i].quantHospedesQuarto; j++) {
            if (strcmp(quarto[i].listaHospedes[j], nomeEditar) == 0) {
                printf("Digite o novo nome para o hóspede: ");
                scanf("%s", quarto[i].listaHospedes[j]);
                encontrado = 1;
                break;
            }
        }
    }
    if (!encontrado) {
        printf("O hóspede não foi encontrado.\n");
    }
    reescreverLista(quarto, quantidadeQuartos);
}

void liberarQuarto(Quarto quarto[], int quantidadeQuartos) {
    char numeroQuarto[MAX_NOME];
    printf("Digite o número do quarto que deseja liberar: ");
    scanf("%s", numeroQuarto);

    int encontrado = 0;
    for (int i = 0; i < quantidadeQuartos; i++) {
        if (strcmp(quarto[i].numeroQuarto, numeroQuarto) == 0) {
            strcpy(quarto[i].status, "vazio");
            quarto[i].quantHospedesQuarto = 0;
            encontrado = 1;
            printf("O quarto %s foi liberado.\n", numeroQuarto);
            break;
        }
    }
    if (!encontrado) {
        printf("Quarto não encontrado.\n");
    }
    reescreverLista(quarto, quantidadeQuartos);
}

void mostrarQuartosVazios(Quarto quarto[], int quantidadeQuartos) {
    printf("Quartos vazios:\n");
    for (int i = 0; i < quantidadeQuartos; i++) {
        if (strcmp(quarto[i].status, "vazio") == 0) {
            printf("%s\n", quarto[i].numeroQuarto);
        }
    }
}

void listarHospedes(Quarto quarto[], int quantidadeQuartos) {
    char hospedesTemp[MAX_QUARTOS * MAX_HOSPEDES][MAX_NOME];
    int totalHospedes = 0;

    for (int i = 0; i < quantidadeQuartos; i++) {
        for (int j = 0; j < quarto[i].quantHospedesQuarto; j++) {
            strcpy(hospedesTemp[totalHospedes], quarto[i].listaHospedes[j]);
            totalHospedes++;
        }
    }

    qsort(hospedesTemp, totalHospedes, sizeof(hospedesTemp[0]), strcmp);

    printf("\nLista de hóspedes em ordem alfabética:\n");
    for (int i = 0; i < totalHospedes; i++) {
        printf("%d. %s\n", i + 1, hospedesTemp[i]);
    }
}

int main() {
    Quarto quarto[MAX_QUARTOS];
    int posicaoQuarto = 0;
    int opcao;

    iniciarLista(quarto, &posicaoQuarto);

    do {
        printf("\n====== MENU ======\n");
        printf("[1] Inserir hóspedes\n");
        printf("[2] Listar hóspedes em ordem alfabética\n");
        printf("[3] Buscar hóspede\n");
        printf("[4] Editar hóspede\n");
        printf("[5] Liberar quarto\n");
        printf("[6] Mostrar quartos vazios\n");
        printf("[7] Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirHospede(quarto, &posicaoQuarto);
                break;
            case 2:
                listarHospedes(quarto, posicaoQuarto);
                break;
            case 3:
                buscarHospede(quarto, posicaoQuarto);
                break;
            case 4:
                editarHospede(quarto, posicaoQuarto);
                break;
            case 5:
                liberarQuarto(quarto, posicaoQuarto);
                break;
            case 6:
                mostrarQuartosVazios(quarto, posicaoQuarto);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);
                                                                                                               












    return 0;

}
