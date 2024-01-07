

#ifndef PROJETOIAPG_ESTRUTURAS_H
#define PROJETOIAPG_ESTRUTURAS_H
#define MAX_LEN 100
typedef struct Cao

{
    int id;
    char raca[MAX_LEN];
    char cor[MAX_LEN];
    char pelo[MAX_LEN];
    char genero[MAX_LEN];
    int peso;
    char dataNascimento[MAX_LEN];
    char concelhoNascimento[MAX_LEN];
    int pai;
    int mae;
    char morada[MAX_LEN];

};

#endif //PROJETOIAPG_ESTRUTURAS_H
