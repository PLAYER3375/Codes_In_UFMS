/*função que copia lista encadeada*/
#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

celula* copiaLista(celula *lista){
    celula *cpyL, *fim, *novo;
    cpyL=NULL;
    novo=NULL;
    fim=NULL;

    while(lista!=NULL){
        novo=(celula*)malloc(sizeof(celula));

        if(novo==NULL)
            return cpyL;

        novo->num=lista->num;
        novo->prox=NULL;
        
        if(cpyL==NULL){
            cpyL=novo;
            fim=novo;
        } else {
            fim->prox=novo;
            fim=fim->prox;
        }

        lista=lista->prox;
    }

    return cpyL;
}