#ifndef PILHA_H

#define PILHA_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define max 100

typedef struct cel{
    char corChapa[max];
    int espessuraChapa;
    struct cel *prox;
}stock;

void colocaInicio(stock **p, char nome[max], int espessura);

int qtdChapas(stock *p);

void atualizaEstoque(stock **p);

void addManualEstoque(stock **p);

void statusEstoque(stock *p);

#endif