#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

void rotaciona(celula **lista, int n){
    celula *novoIni, *novoFim, *aux;
    int i;

    novoIni=*lista;

    for(i=0; i<n; i++){
        novoIni=novoIni->prox;
    }
    novoFim=novoIni;

    while(novoFim->prox!=NULL){
        novoFim=novoFim->prox;
    }

    novoFim->prox=*lista;
    aux=novoFim->prox;

    for(i=0; i<n-1; i++){
        aux=aux->prox;
    }
    *lista=aux->prox;

    aux->prox=NULL;

    
}