#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

/*primeiro vira ultimo e segundo vira penultimo*/
void invertOrdem(celula **lista){
    celula *ant, *atual, *prox;
    prox=NULL;
    ant=NULL;
    atual=*lista;

    while(atual!=NULL){
        prox=atual->prox;
        atual->prox=ant;
        ant=atual;
        atual=prox;
    }
    
    *lista=ant;
}