#ifndef CLIENTE_H

#define CLIENTE_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define max 100

typedef struct celul{
    int idCli;
    char nomeCli[max];
    int prioridade;
    char ambiente[max];
    struct celul *prox;
}cliente;

cliente* alocaNovoCli();

cliente* buscaClienteID(cliente *p, int id);

int buscaClienteIDint(cliente *p, int id);

void colocaFinalCli(cliente *p, int id, char nome[max], int prioridade, char ambiente[max]);

int qtdClientes(cliente *p);

void statusCliente(cliente *p);

void retirarCliente(cliente *p, int idCliente);

void atualizaNomeCliente(cliente *p, int idCliente, char nome[max]);

void atualizaIDCliente(cliente *p, int idCliente, int idTroca);

void atualizaAmbiCliente(cliente *p, int idCliente, char nome[max]);

void atualizaPrioCliente(cliente *p, int idCliente, int prioridade);

void atualizaClientes(cliente *p);

void liberaCli(cliente **p);

#endif
