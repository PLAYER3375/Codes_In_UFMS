#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

/*primeiro vira ultimo e segundo vira penultimo*/
void invertOrdem(celula **lista){
    celula *ant, *atual, *prox;
    prox=*lista;
    ant=*lista;
    atual=ant->prox;

    while(prox!=NULL){
        prox=atual->prox;
        atual->prox=ant;
        ant=atual;
        atual=prox;
    }
    
    *lista=ant;
}