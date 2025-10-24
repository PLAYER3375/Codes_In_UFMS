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

void atualizaEstoque(stock **p);

#endif