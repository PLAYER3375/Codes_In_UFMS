/************************************************************
*                                                           *
* Nome do(a) estudante:Matheus Henrique dos Santos Gomes    *
* Trabalho Prático - CutPlanner                             *
* Disciplinas: Algoritmos e Programação II                  *
* Laboratório de Algoritmos e Programação II                *
* Professores: Ivone e Ronaldo                              *
* Data: 08/11/25                                            *
* Versão: 1.9                                               *
* Descrição: Arquivo cabeçalho do arquivo stock.c           *
*                                                           *
*************************************************************/

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

void colocaInicio(stock *p, char nome[max], int espessura);

void colocaFinal(stock *p, char nome[max], int espessura);

int qtdChapas(stock *p);

void atualizaEstoque(stock *p);

void statusEstoque(stock *p);

void retirarEstoque(stock *p, int posicChapa);

void liberaEstoque(stock *p);

void guardaEstoque(stock *p);

void trocaEstoque(stock *p, int posicIni, int posicFim);

int encontraPosEstoque(stock *estoque, const char *corChapa, int espessura);

#endif
