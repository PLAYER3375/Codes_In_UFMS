#include"pilha.h"

void colocaInicio(stock **p, char nome[max], int espessura){
    stock *aux;

    aux=alocaNovo();
    strcpy(aux->corChapa, nome);
    aux->espessuraChapa=espessura;
    aux->prox=*p;
    *p=aux;
}

void atualizaEstoque(stock **p){
    FILE *arqv;
    char nome[max];
    int espessura;
    arqv=fopen("estoque.txt", "r");
    if(arqv==NULL)
        return;

    while(!feof){
        fscanf("%[^,], %d;", nome, espessura);
        colocaInicio(p, nome, espessura);
    }

    printf("Estoque atualizado com sucesso!!!\n");
}