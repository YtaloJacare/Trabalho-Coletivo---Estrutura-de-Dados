#ifndef QUARTO_H
#define QUARTO_H

typedef struct Quarto;

void limparBuffer();
void limparString(char *str);
void iniciarLista(Quarto quarto[], int *posicaoQuarto);
void reescreverLista(Quarto quarto[], int quantidadeQuartos);
void inserirHospede(Quarto quarto[], int *posicaoQuarto);
void buscarHospede(Quarto quarto[], int quantidadeQuartos);
void editarHospede(Quarto quarto[], int quantidadeQuartos);
void liberarQuarto(Quarto quarto[], int quantidadeQuartos);
void mostrarQuartosVazios(Quarto quarto[], int quantidadeQuartos);
void listarHospedes(Quarto quarto[], int quantidadeQuartos);

#endif
