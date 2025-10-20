#include"pilha.h"

void colocaInicio(stock **p, char nome[max]){
    stock *aux;

    aux=alocaNovo();
    strcpy(aux->corChapa, nome);
    aux->prox=*p;
    *p=aux;
}

void atualizaEstoque(stock **p){
    FILE *arqv;
    arqv=fopen("estoque.txt", "r");
    if(arqv==NULL)
        return;

    
}