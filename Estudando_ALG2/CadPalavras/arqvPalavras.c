/*
quero adicionar uma busca para contar a quantidade de palavras iguais
add uma função que confima se é ou não palindrome
add remove uma palavra da lista
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct celula{
    char palavra[31];
    struct celula *prox;
}newpala;

void addNo(newpala **palavras, char palavra[31]){
    newpala *aux;
    aux=(newpala *)malloc(sizeof(newpala));
    strcpy(aux->palavra, palavra);
    aux->prox=*palavras;
    *palavras=aux;
}

int main(void){
    FILE *arq;
    newpala *palavras, *aux;
    char palavra[99];
    int i;
    palavras=NULL;

    do{
        i=0;
        arq=fopen("palavra.txt", "r");
        if(arq==NULL){
            printf("Não foi possível encontrar o arquivo");
            i=1;
        }
    }while(i==1);

    while(!feof(arq)){
        fscanf(arq, "%s", palavra);
        addNo(&palavras, palavra);
    }
    fclose(arq);
    do{
        i=0;
        arq=fopen("palavrabackup.txt", "w");
        if(arq==NULL){
            printf("Não foi possível encontrar o arquivo");
            i=1;
        }
    }while(i==1);

    aux=palavras;
    while(aux!=NULL){
        fprintf(arq, "%s\n", aux->palavra);
        aux=aux->prox;
    }

    return 0;
}