/*
NOME: Matheus Henrique dos Santos Gomes
DATA: 31/08/2025
ALGORITMOS E PROGRAMAÇÃO 2
PROJETO: SISTEMA DE CADASTRO DE PRODUTOS
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Struct que representa os produtos*/
struct produtos{
    char nome[31];
    char categoria[31];
    int cod;
    float preco;
    int qtd;
    struct produtos *prox;
};
typedef struct produtos produtos;


typedef struct{
    char categoria[31];
    int qtd;
    struct categorias *prox;
} categorias;

int main(void){
    int cont;
    char localarq[100];
    produtos *produto, *novo;
    FILE *prodfile;

    /*inicializar com null*/
    produto=NULL;
    novo=NULL;
    prodfile=NULL;
    cont=0;

    /*leitura do local do arquivo original*/
    scanf("%[^\n]", localarq);
    prodfile=fopen(localarq, "r");

    /*enquanto não chegar na linha do EOF, faça:*/
    while(!feof(prodfile)){
        /*alocação*/
        novo=(produtos *)malloc(sizeof(produtos));
        if(novo==NULL){
            printf("Erro de alocação de memória.\n");
            fclose(prodfile);
            return 1;
        }
        /*leitura para dentro do ponteiro novo*/
        fscanf(prodfile, "%d;%30[^;];%30[^;];%d;%f", &novo->cod, novo->nome, novo->categoria, &novo->qtd, &novo->preco);
        /*o ponteiro recebe a direção do inicio*/
        novo->prox=produto;
        /*o inicio recebe o novo, empilhando*/
        produto=novo;
        cont++;
    }
    fclose(prodfile);

    /*print no terminal, com contador ainda para saber se está lendo a quantidade de linhas certas*/
    printf("%d\n", cont);
    novo=produto;
    while(novo!=NULL){
        printf("%d;%s;%s;%d;%f\n", novo->cod, novo->nome, novo->categoria, novo->qtd, novo->preco);
        novo=novo->prox;
    }
    
    /*leitura do local do arquivo save*/
    printf("Onde deseja salvar?\n");
    scanf(" %[^\n]", localarq);
    prodfile=fopen(localarq, "w");

    novo=produto;
    /*se iniciar no primeiro printa nada... por isso pulo para o proximo*/
    novo=novo->prox;
    while(novo!=NULL){
        fprintf(prodfile, "%d;%s;%s;%d;%f\n", novo->cod, novo->nome, novo->categoria, novo->qtd, novo->preco);
        novo=novo->prox;
    }
    fclose(prodfile);

    return 0;
}