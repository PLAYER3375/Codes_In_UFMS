#ifndef STOCK_H

#define STOCK_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define max 100

typedef struct cel{
    char corChapa[max];
    int espessuraChapa;
    struct cel *prox;
}stock;

stock* alocaNovo();

void colocaInicio(stock **p, char nome[max], int espessura);

void colocaFinal(stock **p, char nome[max], int espessura);

int qtdChapas(stock *p);

void atualizaEstoque(stock **p);

void addManualEstoque(stock *p);

void statusEstoque(stock *p);

void retirarEstoque(stock *p, int posicChapa);

#endif