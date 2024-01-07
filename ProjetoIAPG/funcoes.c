//
// Created by joaok on 12/12/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"



CAO InserirNovoCao(CAO cao, int* ncao) {
    printf("\nInsira os dados do novo cao:");

    ++*ncao;  // se nao mandar por apontador ele n vai guardar no endereço de memoria entao nao ia funcionar
    cao.id = *ncao;

    printf("\nNome: ");
    scanf ("%s", cao.nome);

    printf("\nIdade (anos meses): ");
    scanf ("%d %d", &cao.anos, &cao.meses);

    printf("\nGenero (masculino/feminino): ");
    scanf("%s", cao.genero);

    printf("\nRaca: ");
    getchar();
    scanf("%[^\n]%*c", cao.raca);

    printf("\nCor: ");
    scanf("%s", cao.cor);

    printf("\nPeso: ");
    scanf("%d", &cao.peso);

    printf("\nTipo comportamental (Calmo/Agressivo): ");
    scanf ("%s", cao.comportamento);

    printf("\nTipo pelo (curto/medio/longo): ");
    scanf ("%s", cao.pelagem);

    printf("\nData de nascimento (DD/MM/AAAA): ");
    scanf ("%s", cao.dataNascimento);

    printf("\nLocal de Nascimento (Cidade): ");
    scanf ("%s", cao.cidadeNascimento);

    printf("\nMorada atual (Cidade): ");
    getchar();
    scanf("%[^\n]%*c", cao.morada);

    printf("\nID do pai: ");
    scanf ("%d", &cao.id_pai);

    printf("\nID da mae: ");
    scanf ("%d", &cao.id_mae);

    printf("\nCao inserido com sucesso!\n");

    return cao;


}

void menu() {
    CAO array[MAX_LEN]; // array onde vao ficar os caes
    CAO cao;
    CAO arrayFicheiro[MAX_LEN];
    int nFicheiro;


    int ncao = 0;
    char *config = lerFicheiroConfigs("config_bd_canina.txt");

    //Leitura de caes
    if (stricmp(config, "txt") == 0) {
        lerFicheiroCao(array, arrayFicheiro ,&ncao, "bd_caes.txt");
        nFicheiro = ncao;
    } else {
        lerFicheiroCaoBin(array, ncao, "bd_caes.bin"); //não tinha como ler "n" caes por não saber o número de caes para iterar sobre o bin
    }

    int Iresposta = 0;

    do {
    printf("\n [1] - Inserir novo cao");
    printf("\n [2] - Pesquisar por cao");
    printf("\n [3] - Ver todos os caes");
    printf("\n [4] - Mostrar estatisticas: ");
    printf("\n [5] - Exportar para ficheiro: ");
    printf("\n [6] - Verificar integridade ficheiro: ");
    printf("\n [7] - Menu de Eventos: ");
    printf("\n\n Selecione a sua escolha: ");
    scanf("%d", &Iresposta);
        switch (Iresposta) {
            case 1:
                array[ncao] = InserirNovoCao(cao, &ncao);
                break;
            case 2:
                pesquisarCao(array, ncao);
                break;

            case 3:
                printcaes(array, ncao);
                break;
            case 4:
                estatisticas(ncao, array);
                break;
            case 5:
                escreverFicheiroCao(array, ncao, nFicheiro, "bd_caes.txt");
                escreverFicheiroCaoBin(array, ncao, "bd_caes.bin");
                break;
            case 6:
                verificarIntegridadeBD(array,arrayFicheiro,ncao);
                break;
            case 7:
                adicionarEventoHistorico();
                break;
            default:
                printf("\nEscolha uma opcao valida");
                break;
        }
    } while (Iresposta != 0);
}

void pesquisarCao(CAO array[], int ncao){

    int choice,idMatch, encontrado = 0, peso, idade, pelo;
    char porte[20];
    char generoMatch[20];
    char racaMatch[20];

    do {
        printf("\n Pesquisar por:\n");
        printf("\n [1] - ID");
        printf("\n [2] - Porte");
        printf("\n [3] - Faixa Etaria");
        printf("\n [4] - Genero");
        printf("\n [5] - Raca");
        printf("\n [6] - Pelagem");
        printf("\n [0] - Voltar ao menu");
        printf("\n\n Selecione a sua escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                menu();
                break;
            case 1:
                printf("Indique o ID que pretende procurar: ");
                scanf("%d", &idMatch);
                for (int i = 0; i < ncao; i++) {
                    if (array[i].id == idMatch){
                        printcao(array[i]);
                        encontrado = 1;
                    }
                }
                if (!encontrado)
                    printf("Cao nao encontrado\n");
                encontrado = 0;
                break;
            case 2:
                printf("Indique o porte do cao:\n");
                printf("Pequeno: 0-10kg\n"
                       "Medio: 10-25kg\n"
                       "Grande: +25kg\n");
                scanf("%s", porte);

                if (stricmp(porte, "pequeno") == 0)
                    peso = 0;
                if (stricmp(porte, "medio") == 0)
                    peso = 1;
                if (stricmp(porte, "grande") == 0)
                    peso = 2;

                for (int i = 0; i < ncao; i++) {
                    if (peso == 0 && array[i].peso < 10) {
                        printcao(array[i]);
                        encontrado = 1;
                    } else if (peso == 1 && array[i].peso <= 25) {
                        printcao(array[i]);
                        encontrado = 1;
                    } else if(peso == 2 && array[i].peso > 25){
                        printcao(array[i]);
                        encontrado = 1;
                    }
                }
                if(!encontrado)
                    printf("\nCao nao encontrado\n");
                encontrado = 0;
                break;
            case 3:
                printf("Indique a faixa etaria do cao:\n");
                printf("[1] - <3 meses\n"
                       "[2] - 3 a 6 meses\n"
                       "[3] - 6 a 9 meses\n"
                       "[4] - 9 a 12 meses\n"
                       "[5] - 1 a 3 anos\n"
                       "[6] - mais de 3 anos\n");
                 scanf("%d", &idade);

                for (int i = 0; i < ncao; i++) {
                    if (idade == 1 && array[i].anos == 0 && array[i].meses < 3) {
                        printcao(array[i]);
                        encontrado = 1;
                    } else if (idade == 2 && array[i].anos == 0 && array[i].meses < 6 && array[i].meses > 3) {
                        printcao(array[i]);
                        encontrado = 1;
                    } else if(idade == 3 && array[i].anos == 0 && array[i].meses < 9 && array[i].meses > 6){
                        printcao(array[i]);
                        encontrado = 1;
                    } else if(idade == 4 && array[i].anos == 0 && array[i].meses < 12 && array[i].meses > 9){
                        printcao(array[i]);
                        encontrado = 1;
                    } else if(idade == 5 && array[i].anos >= 1 && array[i].anos < 3 || (idade == 5 && array[i].anos == 3 && array[i].meses == 0)){
                        printcao(array[i]);
                        encontrado = 1;
                    } else if((idade == 6 && array[i].anos == 3 && array[i].meses > 0) || (idade == 6 && array[i].anos >= 4)){
                        printcao(array[i]);
                        encontrado = 1;
                    }
                }
                if(!encontrado)
                    printf("Cao nao encontrado\n");
                encontrado = 0;
                break;
            case 4:
                printf("Indique o genero que quer procurar: ");
                scanf("%s",generoMatch);
                for (int i = 0; i < ncao; i++) {
                    if (stricmp(generoMatch, array[i].genero) == 0) {
                        printcao(array[i]);
                        encontrado = 1;
                    }
                }
                if(!encontrado)
                    printf("Nenhum cao encontrado\n");
                encontrado = 0;
                break;
            case 5:
                printf("Indique a raca que quer procurar: ");
                scanf("%s",racaMatch);
                for (int i = 0; i < ncao; i++) {
                    if (stricmp(racaMatch, array[i].raca) == 0) {
                        printcao(array[i]);
                        encontrado = 1;
                    }
                }
                if(!encontrado)
                    printf("Nenhum cao encontrado\n");
                encontrado = 0;
                break;
            case 6:
                printf("Indique a pelagem do cao:\n");
                printf("Curto, Medio, Longo\n");
                scanf("%s", porte);

                if (stricmp(porte, "curto") == 0)
                    pelo = 0;
                if (stricmp(porte, "medio") == 0)
                    pelo = 1;
                if (stricmp(porte, "longo") == 0)
                    pelo = 2;

                for (int i = 0; i < ncao; i++) {
                    if (pelo == 0 && stricmp(array[i].pelagem, "curto") == 0) {
                        printcao(array[i]);
                        encontrado = 1;
                    } else if (pelo == 1 && stricmp(array[i].pelagem, "medio") == 0) {
                        printcao(array[i]);
                        encontrado = 1;
                    } else if(pelo == 2 && stricmp(array[i].pelagem, "longo") == 0){
                        printcao(array[i]);
                        encontrado = 1;
                    }
                }
                if(!encontrado)
                    printf("\nCao nao encontrado\n");
                encontrado = 0;
                break;
            default:
                break;
        }
    }while(choice != 0);
}

void estatisticas(int ncao, CAO array[]){ // p = percentagem  q = quantidade
    float pPequenos, pMedios, pGrandes, qPequenos = 0, qMedios = 0, qGrandes = 0;
    float p1, p2, p3, p4, p5, p6, q1 = 0, q2 = 0, q3 = 0, q4 = 0, q5 = 0, q6 = 0;

    for (int i = 0; i < ncao; i++) {
        if (array[i].peso < 10) {
            qPequenos++;
        } else if (array[i].peso < 25) {
            qMedios++;
        } else if(array[i].peso >= 25){
            qGrandes++;
        }
    }

    pPequenos = (qPequenos / (float)ncao) * 100;
    pMedios = (qMedios / (float)ncao) * 100;
    pGrandes = (qGrandes / (float)ncao) * 100;

    printf("\nExistem %.0f pequeno(s) (%.2f)%%\n"
           "Existem %.0f medio(s) (%.2f)%%\n"
           "Existem %.0f grande(s) (%.2f)%%\n", qPequenos, pPequenos, qMedios, pMedios, qGrandes, pGrandes);


    for (int i = 0; i < ncao; i++) {
        if (array[i].anos == 0 && array[i].meses < 3) {
            q1++;
        } else if (array[i].anos == 0 && array[i].meses < 6) {
            q2++;
        } else if(array[i].anos == 0 && array[i].meses < 9){
            q3++;
        } else if(array[i].anos == 0 && array[i].meses < 12){
            q4++;
        } else if(array[i].anos >= 1 && array[i].anos < 3 || (array[i].anos == 3 && array[i].meses == 0)){
            q5++;
        } else if(array[i].anos >= 3 ){
            q6++;
        }
    }

    p1 = (q1 / (float)ncao) * 100;
    p2 = (q2 / (float)ncao) * 100;
    p3 = (q3 / (float)ncao) * 100;
    p4 = (q4 / (float)ncao) * 100;
    p5 = (q5 / (float)ncao) * 100;
    p6 = (q6 / (float)ncao) * 100;

    printf ("\nExistem %.0f com <3 meses (%.2f)%%;\n"
            "Existem %.0f de 3 a 6 meses (%.2f)%%;\n"
            "Existem %.0f de 6 a 9 meses (%.2f)%%;\n"
            "Existem %.0f de 9 a 12 meses (%.2f)%%;\n"
            "Existem %.0f de 1 a 3 anos (%.2f)%%; \n"
            "Existem %.0f com mais de 3 anos (%.2f)%%\n", q1, p1, q2, p2, q3, p3, q4, p4, q5, p5, q6, p6);

    estNinhadas(array,ncao);
    estGenero(array, ncao);

}

void printcao(CAO cao){
    printf("\n Cao encontrado:\n");
    printf(" \n Id: %d\n",cao.id);
    printf(" Nome: %s\n",cao.nome);
    printf(" Genero: %s\n", cao.genero);
    printf(" Raca: %s\n",cao.raca);
    printf(" Cor: %s\n",cao.cor);
    printf(" Peso: %d\n",cao.peso);
    printf(" Pelagem: %s\n",cao.pelagem);
    printf(" Tipo de Comportamento: %s\n",cao.comportamento);
    printf(" Idade: %d ano(s) e %d mes(es)\n",cao.anos, cao.meses);
    printf(" ID Pai: %d\n",cao.id_pai);
    printf(" ID Mae: %d\n",cao.id_mae);
}

void printcaes(CAO array[], int ncao){
    for (int i = 0; i < ncao; i++) {
        printf(" \n Id: %d\n",array[i].id);
        printf(" Nome: %s\n",array[i].nome);
        printf(" Genero: %s\n", array[i].genero);
        printf(" Raca: %s\n",array[i].raca);
        printf(" Cor: %s\n",array[i].cor);
        printf(" Peso: %d\n",array[i].peso);
        printf(" Pelagem: %s\n",array[i].pelagem);
        printf(" Tipo de Comportamento: %s\n",array[i].comportamento);
        printf(" Idade: %d ano(s) e %d mes(es)\n",array[i].anos, array[i].meses);
        printf(" ID Pai: %d\n",array[i].id_pai);
        printf(" ID Mae: %d\n",array[i].id_mae);
    }
}

char* lerFicheiroConfigs(char fileName[]) {
    FILE* dadosConfig = fopen(fileName, "rt");

    if (dadosConfig == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[MAX_LEN];
    static char config[MAX_LEN];


    config[0] = '\0';

    while (fgets(linha, MAX_LEN, dadosConfig) != NULL) {

        strcat(config, linha);


        if (strlen(config) >= sizeof(config) - 1) {
            break;
        }
    }

    fclose(dadosConfig);

    return config;
}

void lerFicheiroCao(CAO array[], CAO arrayFicheiro[], int* ncao, char fileName[])
{
    int i = 0;
    FILE* dadosCao = fopen(fileName, "rt");

    char linha[MAX_LEN];
    while (fgets(linha, MAX_LEN, dadosCao))
    {
        sscanf(linha, "%d;%d;%d;%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;];%d;%d;%[^;];%[^;]\n", &array[i].id, &array[i].anos, &array[i].meses, array[i].genero,
               array[i].raca, array[i].pelagem, &array[i].peso, array[i].nome, array[i].comportamento, array[i].dataNascimento, array[i].cidadeNascimento,
               &array[i].id_pai, &array[i].id_mae, array[i].cor, array[i].morada);
        sscanf(linha, "%d;%d;%d;%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;];%d;%d;%[^;];%[^;]\n", &arrayFicheiro[i].id, &arrayFicheiro[i].anos, &arrayFicheiro[i].meses, arrayFicheiro[i].genero,
               arrayFicheiro[i].raca, array[i].pelagem, &arrayFicheiro[i].peso, arrayFicheiro[i].nome, arrayFicheiro[i].comportamento, arrayFicheiro[i].dataNascimento, arrayFicheiro[i].cidadeNascimento,
               &arrayFicheiro[i].id_pai, &arrayFicheiro[i].id_mae, arrayFicheiro[i].cor, arrayFicheiro[i].morada);
        i++;
        ++*ncao;
    }
    fclose(dadosCao);
}

int escreverFicheiroCao(CAO array[], int ncao, int nFicheiro, char fileName[])
{
    if (array == NULL)
    {
        return 0;
    }

    FILE *dadosCao = fopen(fileName, "wt");

    if (dadosCao == NULL)
    {
        return 0;
    }

    for (int i = 0; i < ncao; ++i) {
        if (array[i].id != 0)
        {
            if (i < nFicheiro) {
                fprintf(dadosCao, "%d;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s;%d;%d;%s;%s", array[i].id, array[i].anos, array[i].meses, array[i].genero,
                        array[i].raca, array[i].pelagem, array[i].peso, array[i].nome, array[i].comportamento, array[i].dataNascimento, array[i].cidadeNascimento,
                        array[i].id_pai, array[i].id_mae, array[i].cor, array[i].morada);
            } else {
                fprintf(dadosCao, "\n%d;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s;%d;%d;%s;%s", array[i].id, array[i].anos, array[i].meses, array[i].genero,
                        array[i].raca, array[i].pelagem, array[i].peso, array[i].nome, array[i].comportamento, array[i].dataNascimento, array[i].cidadeNascimento,
                        array[i].id_pai, array[i].id_mae, array[i].cor, array[i].morada);
            }
        }
    }

    fclose(dadosCao);
    return 1;
}

int lerFicheiroCaoBin(CAO array[], int ncao, char fileName[]) {

    FILE *dadosCao = fopen(fileName, "rb");

    if (dadosCao == NULL) {
        return 0;
    }

    fread(array, sizeof(CAO), ncao, dadosCao);

    fclose(dadosCao);
    return 1;
}

int escreverFicheiroCaoBin(CAO array[], int ncao, char fileName[]) {

    FILE *dadosCao = fopen(fileName, "wb");

    if (dadosCao == NULL) {
        return 0;
    }

    fwrite(array, sizeof(CAO), ncao, dadosCao);

    fclose(dadosCao);
    return 1;
}

void verificarIntegridadeBD(CAO array[], CAO arrayFicheiro[], int ncao) {

    int idUnmatch[MAX_LEN];  // vai percorrer o array com os caes e verificar os ID. Se estiverem iguais aos do ficheiro vai considerar a integridade verificada com sucesso, caso n ele vai indicar o id do cao que esta no array mas n no ficheiro ( depois é so exportar para ficheiro que resolve)
    int index=0, encontrado=0, print=0;

    lerFicheiroCao(array, arrayFicheiro, &ncao,"bd_caes.txt");

    for (int i = 0; i <= ncao; i++) {
        encontrado=0;
        for (int j = 0; j <= ncao; j++ ) {
           if ( array[i].id == arrayFicheiro[j].id ) {
               encontrado = 1;
           }
        }
        if (encontrado == 0) {
            print = 1;
            idUnmatch[index] = array[i].id;
            index++;
        }

    }
    if (print == 0) {
        printf("\nA integridade foi verificada com sucesso\n");
    } else {
        printf("Os seguintes IDs nao foram encontrados: \n");

        for (int i = 0; i < index; i++) {
            printf("%d ", idUnmatch[i]);
        }
    }
}

void estNinhadas(CAO array[], int ncao){

    for (int i = 0; i < ncao; i++) {
        for (int j = 0; j < ncao; j++ ) {
            if ((array[i].id_pai == array[j].id_pai) && (array[i].id_mae == array[j].id_mae) && (array[i].id_mae != 0 ||array[j].id_mae != 0 || array[i].id_pai != 0 || array[j].id_pai != 0) && array[i].id != array[j].id ) {
                array[i].irmao++;
            }
        }
    }

    float min, max, med, soma=0;

    max = (float)array[0].irmao;

    for(int i=0; i < ncao; i++) {
        if((float)array[i].irmao > max) {
            max = (float)array[i].irmao;
        }
        soma = soma + ((float)array[i].irmao + 1);
    }

    min = max;
    for (int i = 0; i < ncao; i++) {
        if((float)array[i].irmao < min && array[i].irmao != 0) {
            min = (float)array[i].irmao;
        }
    }

    med = soma/(float)ncao;
    if (min > 1 ) {
        min++;
    }
    max++;

    printf("\nO tamanho minimo da ninhada e: %.2f \n"
           "O tamanho maximo da ninhada e: %.2f\n"
           "O tamanho medio das ninhadas e: %.2f\n", min,max,med);
}

void estGenero(CAO array[], int ncao) {
    float pM = 0, pF = 0, qM = 0, qF = 0, pO = 0, qO = 0;

    for (int i = 0; i < ncao; i++) {
        if (stricmp(array[i].genero, "feminino") == 0) {
            qF++;
        } else if (stricmp(array[i].genero, "masculino") == 0) {
            qM++;
        } else qO++;
    }

    pF = (qF / (float)ncao) * 100;
    pM = (qM / (float)ncao) * 100;
    pO = (qO / (float)ncao * 100);

    printf("\nExistem %.0f Macho(s) (%.2f)%%\n"
           "Existem %.0f Femea(s) (%.2f)%%\n"
           "Existem %.0f com outro(s) genero(s) (%.2f)%%\n", qM, pM, qF, pF, qO, pO);


}



//parte da beatriz
/*
int Iresposta;
//--------------------------------------------------[DECLARAÇÃO DAS FUNÇÕES QUE ESTÃO PRESENTES NOS MENUS]------------------------------------------------------------------

//----------------------------------------------------------------------[MENU DA 3ª OPÇÃO]---------------------------------------------------------------------------------

void adicionarEventoHistorico() { // criação de um menu que permite a escolha do tipo de evento a adicionar

    do {
        printf("[Menu de informacoes adicionais]\n");
        printf("[1] Adicionar um acidente.\n");
        printf("[2] Atualizar registos medicos.\n");
        printf("[3] Alterar a informacao sobre o dono.\n");
        printf("[4] Alterar a morada da vivencia do cao. \n ");
        printf("Faca a sua escolha: ");
        scanf("%d", &Iresposta);

        if (Iresposta <= 4) {
            switch (Iresposta) {
                case 1:
                    printf("[Escolheu adicionar um acidente.] ");
                    acidente();
                    break;
                case 2:
                    printf("[Escolheu atualizar registos medicos.]");
                    registos_medicos();
                    break;
                case 3:
                    printf("[Escolheu alterar a informacao sobre o dono.]\n");
                    mudanca_dono();
                    break;
                case 4:
                    printf("[Escolheu alterar a morada da vivencia do cão] ");
                    mudanca_morada();
                    break;
                default:
                    printf("Opção invalida, por favor escolha uma outra opcao ");
                    printf("\nSelecione uma opcao: ");
                    scanf("%d", &Iresposta);
                    break;
            }


        }
    } while (Iresposta > 4 || Iresposta == 0);

}
//-------------------------------------------------------------------[COMPONENTE DA OPÇÃO Nº3 DO MENU ACIMA]---------------------------------------------------------------------------------

void mudanca_dono() {
    FILE *pWrite;

    char morada[MAX_LEN];
    char nome[MAX_LEN];
    int idade;
    char cc[MAX_LEN];
    char email[MAX_LEN];
    int telemovel;
    char cp[MAX_LEN];
    DataNascimento dataNascimento;

    pWrite = fopen("eventoscaes.txt", "w");

    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {
        printf("Introduza as informacoes sobre o novo dono\n");

        printf("\nInsira o nome completo: ");
        getchar();
        fgets(nome, MAX_LEN, stdin);

        printf("\nInsira a idade: ");
        scanf("%d", &idade);

        printf("\nInsira a data de nascimento (dia mes ano): ");
        scanf("%d %d %d", &dataNascimento.dia, &dataNascimento.mes, &dataNascimento.ano);


        printf("\nInsira o email: ");
        scanf("%s", email);

        printf("\nInsira o numero de telemovel: ");
        scanf("%d", &telemovel);

        printf("\nInisra o numero do cartao de cidadao: ");
        scanf("%s", cc);

        printf("\nInsira a morada: ");
        getchar();
        fgets(morada, MAX_LEN, stdin);

        printf("\nInsira o codigo postal: ");
        scanf("%s", cp);


        fprintf(pWrite,
                "\nNome Completo: %sIdade: %d anos \nData de Nascimento: %d/%d/%d \nEmail: %s \nTelemovel: %d \nCartão de Cidadão: %s \nMorada: %sCodigo Postal: %s",
                nome, idade, dataNascimento.dia, dataNascimento.mes, dataNascimento.ano, email, telemovel, cc, morada,
                cp);

        fclose(pWrite);
    }
}

//-------------------------------------------------------------------[COMPONENTE DA OPÇÃO Nº4 DO MENU ACIMA]---------------------------------------------------------------
void mudanca_morada() {

    FILE *pWrite;
    pWrite = fopen("eventoscaes.txt", "w");
    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {

        Nova_ocorrencia data_nova_ocorrencia;
        printf("\nInsira da data do evento: ");
        scanf("%d %d %d", &data_nova_ocorrencia.dia, &data_nova_ocorrencia.mes, &data_nova_ocorrencia.ano);
        fprintf(pWrite, "data: %d/%d/%d", data_nova_ocorrencia.dia, data_nova_ocorrencia.mes, data_nova_ocorrencia.ano);

        char morada[MAX_LEN];
        char morada_antiga[MAX_LEN];

        printf("\nInsira a morada antiga: ");
        getchar();
        fgets(morada_antiga, MAX_LEN, stdin);
        fprintf(pWrite, "\nMorada Antiga: %s\n", morada_antiga);

        printf("\nInsira a nova morada:  ");
        fgets(morada, MAX_LEN, stdin);
        fprintf(pWrite, "Nova Morada: %s", morada);

        fclose(pWrite);
    }

}

//-------------------------------------------------------------------[COMPONENTE DA OPÇÃO Nº1 DO MENU ACIMA]---------------------------------------------------------------
void acidente() {
    FILE *pWrite;
    pWrite = fopen("eventoscaes.txt", "w");
    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {
        Nova_ocorrencia data_nova_ocorrencia;
        printf("\nInsira a data do evento: ");
        scanf("%d %d %d", &data_nova_ocorrencia.dia, &data_nova_ocorrencia.mes, &data_nova_ocorrencia.ano);
        fprintf(pWrite, "Acidente;%d/%d/%d;", data_nova_ocorrencia.dia, data_nova_ocorrencia.mes, data_nova_ocorrencia.ano);

        char acidente[MAX_LEN];
        printf("\nInsira o tipo de acidente que o cao sofreu:");
        getchar();
        fgets(acidente, MAX_LEN, stdin);
        fprintf(pWrite, "%s", acidente);

        fclose(pWrite);
    }
}

//-------------------------------------------------------------------[COMPONENTE DA OPÇÃO Nº2 DO MENU ACIMA]---------------------------------------------------------------
void registos_medicos() {

    FILE *pWrite;
    pWrite = fopen("eventoscaes.txt", "w");
    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {
        Nova_ocorrencia data_nova_ocorrencia;
        printf("\nInsira da data do evento: ");
        scanf("%d %d %d", &data_nova_ocorrencia.dia, &data_nova_ocorrencia.mes, &data_nova_ocorrencia.ano);
        fprintf(pWrite, "data: %d/%d/%d", data_nova_ocorrencia.dia, data_nova_ocorrencia.mes, data_nova_ocorrencia.ano);


        char registos_medicos[MAX_LEN];
        printf("Insira as alteracoes desejadas: ");
        getchar();
        fgets(registos_medicos, MAX_LEN, stdin);
        fprintf(pWrite, "\nAssunto: %s", registos_medicos);

        fclose(pWrite);
    }
} */
void adicionarEventoHistorico() { // criação de um menu que permite a escolha do tipo de evento a adicionar

    int Jresposta = 0;
    do {
        printf("\n\t[Menu de Eventos]\n");
        printf("[1] Adicionar um acidente.\n");
        printf("[2] Atualizar registos medicos.\n");
        printf("[3] Alterar a informacao sobre o dono.\n");
        printf("[4] Alterar a morada da vivencia do cao.\n");
        printf("[0] Voltar ao menu inicial\n");
        printf("Faca a sua escolha: ", Jresposta);
        scanf("%d", &Jresposta);

        if (Jresposta <= 5) {
            switch (Jresposta) {
                case 0:
                    menu();
                    break;
                case 1:
                    printf("[Escolheu adicionar um acidente.] ");
                    acidente();
                    break;
                case 2:
                    printf("[Escolheu atualizar registos medicos.]");
                    registos_medicos();
                    break;
                case 3:
                    printf("[Escolheu alterar a informacao sobre o dono.]\n");
                    mudanca_dono();
                    break;
                case 4:
                    printf("[Escolheu alterar a morada da vivencia do cao]\n ");
                    mudanca_morada();
                    break;
                case 5:
                    printf("Escolheu exportar para ficheiro:");
                    int escreverFicheiroCaoEventos(int tipoEvento, char infoAdicional[], char fileName[]);
                    break;

                default:
                    printf("Opcao invalida, por favor escolha uma outra opcao ");
                    printf("\nSelecione uma opcao: ");
                    scanf("%d", &Jresposta);
                    break;
            }


        }
    } while (Jresposta > 5 || Jresposta == 0);



}

void mudanca_dono() {
    FILE *pWrite;
    char morada[MAX_LEN];
    char nome[MAX_LEN];
    int idade;
    char cc[MAX_LEN];
    char email[MAX_LEN];
    int telemovel;
    char cp[MAX_LEN];
    int id;
    DataNascimento dataNascimento;

    pWrite = fopen("eventoscaes.txt", "a");

    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {
        printf("\nInsira o ID do cao referente: ");
        scanf("%d", &id);

        printf("\nInsira o nome completo: ");
        //scanf(" %[^\n]", nome);
        getchar();
        fgets(nome, MAX_LEN, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        printf("\nInsira a idade: ");
        scanf("%d", &idade);

        printf("\nInsira a data de nascimento (dia mes ano): ");
        scanf("%d %d %d", &dataNascimento.dia, &dataNascimento.mes, &dataNascimento.ano);


        printf("\nInsira o email: ");
        scanf("%s", email);

        printf("\nInsira o numero de telemovel: ");
        scanf("%d", &telemovel);

        printf("\nInisra o numero do cartao de cidadao: ");
        scanf("%s", cc);

        printf("\nInsira a morada: ");
        //scanf(" %[^\n]", morada);
        getchar();
        fgets(morada, MAX_LEN, stdin);
        morada[strcspn(morada, "\n")] = '\0';

        printf("\nInsira o codigo postal: ");
        scanf("%s", cp);


        fprintf(pWrite, "mudanca_dono;%d;%s;%d;%d/%d/%d;%s;%d;%s;%s;%s\n", id, nome, idade, dataNascimento.dia,
                dataNascimento.mes, dataNascimento.ano, email, telemovel, cc, morada, cp);

        fclose(pWrite);
    }

}
void mudanca_morada(){
    int id;
    FILE *pWrite;
    pWrite = fopen("eventoscaes.txt", "a");
    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {

        printf("\nInsira o ID do cao referente: ");
        scanf("%d", &id);

        Nova_ocorrencia data_nova_ocorrencia;
        printf("\nInsira da data do evento (dia mes ano): ");
        scanf("%d %d %d", &data_nova_ocorrencia.dia, &data_nova_ocorrencia.mes, &data_nova_ocorrencia.ano );

        char morada_antiga[MAX_LEN];
        printf("\nInsira a morada antiga: ");
        //scanf(" %[^\n]", morada_antiga);
        getchar();
        fgets(morada_antiga, MAX_LEN, stdin);
        morada_antiga[strcspn(morada_antiga, "\n")] = '\0';

        char morada_nova[MAX_LEN];
        printf("\nInsira a nova morada:  ");
        //scanf(" %[^\n]", morada_nova);
        fgets(morada_nova, MAX_LEN, stdin);



        fprintf(pWrite, "mudanca_morada;%d;%d/%d/%d;%s;%s", id, data_nova_ocorrencia.dia, data_nova_ocorrencia.mes, data_nova_ocorrencia.ano, morada_antiga, morada_nova);


        fclose(pWrite);
    }

}
void acidente() {
    int id;

    FILE *pWrite;
    pWrite = fopen("eventoscaes.txt", "a");
    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {
        char acidente[MAX_LEN];
        Nova_ocorrencia data_nova_ocorrencia;

        printf("\nInsira o ID do cao referente: ");
        scanf("%d", &id);

        printf("\nInsira a data do evento (dia mes ano): ");
        scanf("%d %d %d", &data_nova_ocorrencia.dia, &data_nova_ocorrencia.mes, &data_nova_ocorrencia.ano);

        printf("\nInsira o tipo de acidente que o cao sofreu:");
        //scanf(" %[^\n]", acidente);
        getchar();
        fgets(acidente, MAX_LEN, stdin);

        fprintf(pWrite, "acidente;%d;%d/%d/%d;%s",id, data_nova_ocorrencia.dia, data_nova_ocorrencia.mes, data_nova_ocorrencia.ano, acidente);


        fclose(pWrite);

    }
}
void registos_medicos() {
    int id;
    FILE *pWrite;
    pWrite = fopen("eventoscaes.txt", "a");
    if (pWrite == NULL) {
        printf("\n O ficheiro nao foi aberto");
    } else {
        char registos_medicos[MAX_LEN];
        Nova_ocorrencia data_nova_ocorrencia;

        printf("\nInsira o ID do cao referente: ");
        scanf("%d", &id);

        printf("\nInsira da data do evento (dia mes ano): ");
        scanf("%d %d %d", &data_nova_ocorrencia.dia, &data_nova_ocorrencia.mes, &data_nova_ocorrencia.ano);

        printf("Insira as alteracoes desejadas: ");
        getchar();
        fgets(registos_medicos, MAX_LEN, stdin);

        fprintf(pWrite, "registos_medicos;%d;%d/%d/%d;%s", id, data_nova_ocorrencia.dia, data_nova_ocorrencia.mes,data_nova_ocorrencia.ano, registos_medicos);

        fclose(pWrite);
    }

}