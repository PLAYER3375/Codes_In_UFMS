#ifndef LISTA_H

#define LISTA_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define max 100

typedef struct cel{
    char nome[max];
    struct cel *prox;
}celula;

void menu();

void printSeq(celula *p);

celula* alocaNovo();

void colocaInicio(celula **p, char nome[max]);

void colocaFinal(celula **p, char nome[max]);

void pegaTxt(celula **p);

void colocaTxt(celula *p, char nomeArqv[]);

void libera(celula **p);


#endif