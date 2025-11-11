/************************************************************
*                                                           *
* Nome do(a) estudante:Matheus Henrique dos Santos Gomes    *
* Trabalho Prático - CutPlanner                             *
* Disciplinas: Algoritmos e Programação II                  *
* Laboratório de Algoritmos e Programação II                *
* Professores: Ivone e Ronaldo                              *
* Data: 08/11/25                                            *
* Versão: 1.9                                               *
* Descrição: Arquivo cliente.c com todas as funções.        *
*                                                           *
*************************************************************/

#include"cliente.h"

cliente* alocaNovoCli(){
    cliente *aux=NULL;

    aux=(cliente *) malloc(sizeof(cliente));

    if(aux==NULL){
        printf("Não foi possível alocar");
        return NULL;
    }

    aux->prox=NULL;

    return aux;
}

cliente* buscaClienteID(cliente *p, int id){
    while(p!=NULL && p->idCli!=id){
        p=p->prox;
    }

    return p;
}

int buscaClienteIDint(cliente *p, int id){
    while(p!=NULL && p->idCli!=id){
        p=p->prox;
    }
    if(p==NULL){
        return 0;
    } else {
        return 1;
    }
}

void colocaFinalCli(cliente *p, int id, char nome[max], char ambiente[max]){
    cliente *aux=NULL, *fim=NULL;

    aux=alocaNovoCli();
    aux->idCli=id;
    strcpy(aux->nomeCli, nome);
    strcpy(aux->ambiente, ambiente);

    if(p->prox==NULL){
        p->prox=aux;
    } else {
        fim=p->prox;
        while(fim->prox!=NULL){
            fim=fim->prox;
        }
        fim->prox=aux;
    }
}

int qtdClientes(cliente *p){
    int x=0;
    while(p->prox!=NULL){
        x++;
        p=p->prox;
    }
    return x;
}

void statusCliente(cliente *p){
    int qtd;
    
    qtd=qtdClientes(p);

    if(qtd>0){
        printf("Os clientes disponíveis são:\n");
        printf("|\n");
        printf("V\n");
        p=p->prox;
        printf("  ID  ||  NOME  ||  AMBIENTE\n");
        while(p!=NULL){
            printf("  %d  ||  %s  ||  %s\n", p->idCli, p->nomeCli, p->ambiente);
            p=p->prox;
        }
    } else {
        printf("Nenhum cliente disponível!!!\n");
    }
}

void retirarCliente(cliente *p, int idCliente){
    cliente *aux=NULL;
    while(p->prox!=NULL && p->prox->idCli!=idCliente){
        p=p->prox;
    }
    if(p->prox!=NULL){
        aux=p->prox;
        p->prox=aux->prox;
        free(aux);
        printf("Cliente retirado com sucesso!!!\n");
    } else {
        printf("Cliente não encontrado, operação  de retirada ignorada.\n");
    }
}

void liberaCliente(cliente *p){
    if(p!=NULL){
        liberaCliente(p->prox);
        free(p);
    }
}

void atualizaNomeCliente(cliente *p, int idCliente, char nome[max]){
    cliente *aux=NULL;
    aux=buscaClienteID(p, idCliente);
    strcpy(aux->nomeCli, nome);
}

void atualizaIDCliente(cliente *p, int idCliente, int idTroca){
    cliente *aux=NULL;
    aux=buscaClienteID(p, idCliente);
    aux->idCli=idTroca;
}

void atualizaAmbiCliente(cliente *p, int idCliente, char nome[max]){
    cliente *aux=NULL;
    aux=buscaClienteID(p, idCliente);
    strcpy(aux->ambiente, nome);
}

void atualizaClientes(cliente *p){
    FILE *arqv=NULL;
    char nome[max], ambiente[max];
    int id, qtd;
    arqv=fopen("bancotxt/clientes.txt", "r");
    if(arqv==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(fscanf(arqv, " %d, %[^,], %[^;];", &id, nome, ambiente)==3){
        colocaFinalCli(p, id, nome, ambiente);
    }

    fclose(arqv);

    qtd=qtdClientes(p);

    if(qtd==0){
        printf("Nenhum cliente cadastrado!!!\n");
    } else if(qtd>0){
        printf("Lista de clientes atualizada com sucesso!!!\n");
    }
}

void guardaClientes(cliente *clients){
    FILE *arqv=NULL;
    cliente *c=NULL;

    arqv=fopen("bancotxt/clientes.txt", "w");
    if(arqv==NULL){
        printf("Não foi possível abrir clientes.txt para salvar clientes\n");
        return;
    }

    c=clients->prox;
    while(c != NULL){
        fprintf(arqv, "%d, %s, %s;\n", c->idCli, c->nomeCli, c->ambiente);
        c=c->prox;
    }

    fclose(arqv);
}

void liberaCli(cliente *p){
    if(p!=NULL){
        liberaCli(p->prox);
        free(p);
    }
}
