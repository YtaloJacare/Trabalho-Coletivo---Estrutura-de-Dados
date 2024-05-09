#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 500

typedef struct Quartos {
  char quarto[800];
  char status[800];
  char tipo[800];
  char hospedes[800];

} Quartos;

typedef struct listaQH {
  Quartos *QH;
  int quantidade;
} listaQH;

typedef struct Dados {
  int opcao;
  char procurandoQuarto[100];
  char procurandoHospede[100];
  char NovoQuarto[100];
  char NovoStatus[200];
  char Novatipo[800];
  int Busca;
  int resultadoBusca;

} Dados;

int Sort(const void *a, const void *b) {
  return strcmp(((Quartos *)a)->quarto, ((Quartos *)b)->quarto);
}

void Iniciando(listaQH *listaqh) {
  listaqh->QH = NULL;
  listaqh->quantidade = 0;
}

void InserindoQuarto(listaQH *listaqh, const Quartos *ref) {
  listaqh->quantidade++;
  listaqh->QH =
      (Quartos *)realloc(listaqh->QH, listaqh->quantidade * sizeof(Quartos));
  if (listaqh->QH == NULL) {
    printf("Erro.\n");
    exit(1);
  }
  listaqh->QH[listaqh->quantidade - 1] = *ref;
}

void imprimir(listaQH *listaqh) {
  for (int i = 0; i < listaqh->quantidade; i++) {
    printf("Quarto: %s\n", listaqh->QH[i].quarto);
    printf("Status: %s\n", listaqh->QH[i].status);
    printf("Tipo: %s\n", listaqh->QH[i].tipo);
    printf("Hospedes:\n%s\n", listaqh->QH[i].hospedes);
    printf("==================\n");
  }
}

void Liberarlistaab(listaQH *listaqh) {
  free(listaqh->QH);
  listaqh->QH = NULL;
  listaqh->quantidade = 0;
}

int buscaBinaria(listaQH *listaqh, char *quarto) {
  int esq = 0;
  int dir = listaqh->quantidade - 1;

  while (esq <= dir) {
    int referencia = esq + (dir - esq) / 2;
    int cmp = strcmp(listaqh->QH[referencia].quarto, quarto);

    if (cmp == 0) {
      return referencia;
    } else if (cmp < 0) {
      esq = referencia + 1;
    } else {
      dir = referencia - 1;
    }
  }

  return -1;
}

void Ordenando(listaQH *listaqh, const Quartos *artista, const char *arquivo) {
  int PosInicial = 0;

  while (PosInicial < listaqh->quantidade &&
         strcmp(artista->quarto, listaqh->QH[PosInicial].quarto) > 0) {
    PosInicial++;
  }

  listaqh->quantidade++;
  listaqh->QH =
      (Quartos *)realloc(listaqh->QH, listaqh->quantidade * sizeof(Quartos));

  if (listaqh->QH == NULL) {
    perror("Erro.\n");
    exit(1);
  }

  for (int i = listaqh->quantidade - 1; i > PosInicial; i--) {
    listaqh->QH[i] = listaqh->QH[i - 1];
  }

  listaqh->QH[PosInicial] = *artista;

  FILE *albumArquivo = fopen(arquivo, "w");
  if (albumArquivo == NULL) {
    perror("Erro ao abrir arquivo.\n");
    exit(1);
  }

  for (int i = 0; i < listaqh->quantidade; i++) {
    fprintf(albumArquivo, "%s\n%s\n%s\n%s\n==========\n", listaqh->QH[i].quarto,
            listaqh->QH[i].status, listaqh->QH[i].tipo,
            listaqh->QH[i].hospedes);
  }

  fclose(albumArquivo);
}

int main() {
  listaQH listaqh;
  Dados Dados;
  Iniciando(&listaqh);

  FILE *arquivo = fopen("quartos.txt", "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo\n");
    exit(1);
  }

  char parametroTexto[MAX];
  Quartos artista;
  int parametro = 0;

  while (fgets(parametroTexto, MAX, arquivo)) {
    parametroTexto[strcspn(parametroTexto, "\n")] = '\0';

    if (strcmp(parametroTexto, "==========") == 0) {
      if (parametro >= 4) {
        InserindoQuarto(&listaqh, &artista);
      }
      parametro = 0;
    } else {
      switch (parametro) {
      case 0:
        strcpy(artista.quarto, parametroTexto);
        break;
      case 1:
        strcpy(artista.status, parametroTexto);
        break;
      case 2:
        strcpy(artista.tipo, parametroTexto);
        break;
      case 3:
        strcpy(artista.hospedes, parametroTexto);
        break;
      default:
        strcat(artista.hospedes, "\n");
        strcat(artista.hospedes, parametroTexto);
        break;
      }
      parametro++;
    }
  }
  fclose(arquivo);

  do {
    printf("\nMenu ADM:\n");
    printf("(1) - Buscar Quarto\n");
    printf("(2) - Adicionar Quarto (ADM)\n");
    printf("(3) - Mostrar Lista de Quato e Hospedes\n");
    printf("(4) - Sair\n");
    printf("\nEscolha uma das opcoes(Informe o valor): ");
    scanf("%d", &Dados.opcao);

    switch (Dados.opcao) {
    case 1:
      printf("\n\nInforme o Quarto pesquisa: ");
      getchar();
      fgets(Dados.procurandoQuarto, sizeof(Dados.procurandoQuarto), stdin);
      Dados.procurandoQuarto[strcspn(Dados.procurandoQuarto, "\n")] = '\0';

      Dados.Busca = buscaBinaria(&listaqh, Dados.procurandoQuarto);

      if (Dados.Busca != -1) {
        printf("\nEncontrado\n");
        printf("quarto: %s\n", listaqh.QH[Dados.Busca].quarto);
        printf("Gênero Musical: %s\n", listaqh.QH[Dados.Busca].status);
        printf("Local de Nascimento: %s\n", listaqh.QH[Dados.Busca].tipo);
        printf("Álbuns:\n%s\n", listaqh.QH[Dados.Busca].hospedes);
      } else {
        printf("Nao encontrado\n");
      }
      break;

    case 2:
      printf("\nInforme o Quarto: ");
      getchar();
      fgets(artista.quarto, sizeof(artista.quarto), stdin);
      artista.quarto[strcspn(artista.quarto, "\n")] = '\0';

      printf("Informe o Status: ");
      fgets(artista.status, sizeof(artista.status), stdin);
      artista.status[strcspn(artista.status, "\n")] = '\0';

      printf("Informe o Tipo: ");
      fgets(artista.tipo, sizeof(artista.tipo), stdin);
      artista.tipo[strcspn(artista.tipo, "\n")] = '\0';

      printf("Informe os hospedes (Separe com Virgula): ");
      fgets(artista.hospedes, sizeof(artista.hospedes), stdin);
      artista.hospedes[strcspn(artista.hospedes, "\n")] = '\0';

      Ordenando(&listaqh, &artista, "quartos.txt");
      printf("\nArtista adicionado.\n");
      break;

    case 3:
      printf("\nLista de Quartos \n\n");
      qsort(listaqh.QH, listaqh.quantidade, sizeof(Quartos), Sort);
      imprimir(&listaqh);
      break;

    case 4:
      printf("Obrigado!!\n");
      break;

    default:
      printf("\nOpcao invalida. \nEscolha uma opçao de 1 a 4.\n");
      break;
    }

  } while (Dados.opcao != 7);

  Liberarlistaab(&listaqh);

  return 0;
}
