//
// Created by joaok on 12/12/2023.
//

#ifndef PROJETOIAPG_FUNCOES_H
#define PROJETOIAPG_FUNCOES_H

#define MAX_LEN 100
typedef struct Cao {
    int id;
    int anos;
    int meses;
    char genero[MAX_LEN];
    char raca[MAX_LEN];
    int peso;
    char nome[MAX_LEN];
    char comportamento[MAX_LEN];
    char dataNascimento[MAX_LEN];
    char cidadeNascimento[MAX_LEN];
    int id_pai;
    int id_mae;
    char cor[MAX_LEN];
    char morada[MAX_LEN];
    int irmao;
    int ninhada;
    int verificado;
    char pelagem[MAX_LEN];

}CAO;

void menu();
CAO InserirNovoCao(CAO cao,int* ncao);
void pesquisarCao(CAO cao[MAX_LEN], int ncao);
void printcao(CAO cao);
void estatisticas(int ncao, CAO array[]);
void lerFicheiroCao(CAO array[], CAO arrayFicheiro[], int* ncao, char fileName[]);
void printcaes(CAO array[], int ncao);
int escreverFicheiroCao(CAO array[], int ncao, int nFicheiro, char fileName[]);
char* lerFicheiroConfigs(char fileName[]);
int escreverFicheiroCaoBin(CAO array[], int ncao, char fileName[]);
int lerFicheiroCaoBin(CAO array[], int ncao, char fileName[]);
void verificarIntegridadeBD(CAO array[], CAO arrayFicheiro[], int ncao);
void estNinhadas(CAO array[], int ncao);
void estGenero (CAO array[], int ncao);


typedef struct {
    int dia, mes, ano;
} DataNascimento;

typedef struct {
    int dia, mes, ano;
} Nova_ocorrencia;

void adicionarEventoHistorico();
void mudanca_dono();
void acidente();
void registos_medicos();
void mudanca_morada();

#endif //PROJETOIAPG_FUNCOES_H



