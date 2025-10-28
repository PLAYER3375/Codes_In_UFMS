
#ifndef LISTA_H

#define LISTA_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define max 100

typedef struct celula{
    char nome[max];
    struct celula *prox;
}celula;

void menu();

/*
celula* alocaNovo();

void colocaInicio(celula **p, char nome[max]);

void colocaFinal(celula **p, char nome[max], int espessura);
*/
/*void pegaTxt(celula **p);

void colocaTxt(celula *p, char nomeArqv[]);*/

void libera(celula **p);


#endif
