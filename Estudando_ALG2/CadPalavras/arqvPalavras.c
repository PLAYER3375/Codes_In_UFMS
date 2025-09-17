#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct celula{
    char palavra[30];
    struct celula *prox;
}newpala;

int main(void){
    FILE *arq;
    newpala *palavras, *aux;
    int i;
    i=0;
    palavras=NULL;

    do{
        arq=fopen("palavra.txt", "r");
        if(arq==NULL){
            printf("Não foi possível encontrar o arquivo");
            i=1;
        }
    }while(i==1);

    aux=(newpala *)malloc(sizeof(newpala));
    if(aux==NULL){
        printf("Não foi possível alocar");
        return 1;
    }

    while(!feof(arq)){
        fscanf(arq, " %[^\n]", aux->palavra);
        aux->prox=NULL;
        aux=(newpala *)malloc(sizeof(newpala));
        if(aux==NULL){
            printf("Não foi possível alocar");
            return 1;
        }
    }
    

    

    return 0;
}