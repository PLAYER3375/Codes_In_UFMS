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
    while(p->prox!=NULL && p->idCli!=id){
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

void colocaFinalCli(cliente *p, int id, char nome[max], int prioridade, char ambiente[max]){
    cliente *aux=NULL, *fim=NULL;

    aux=alocaNovoCli();
    aux->idCli=id;
    strcpy(aux->nomeCli, nome);
    aux->prioridade=prioridade;
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
        printf("  ID  ||  NOME  ||  AMBIENTE  ||  PRIORIDADE\n");
        while(p!=NULL){
            printf("  %d  ||  %s  ||  %s  ||  %d\n", p->idCli, p->nomeCli, p->ambiente, p->prioridade);
            p=p->prox;
        }
    } else {
        printf("Nenhuma chapa disponível!!!\n");
    }
}

void atualizaClientes(cliente *p){
    FILE *arqv=NULL;
    char nome[max], ambiente[max];
    int id, prioridade, qtd;
    arqv=fopen("arquivostxt/clientes.txt", "r");
    if(arqv==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(fscanf(arqv, " %d, %[^,], %d, %[^;];", &id, nome, &prioridade, ambiente)==4){
        colocaFinalCli(p, id, nome, prioridade, ambiente);
    }

    fclose(arqv);

    qtd=qtdClientes(p);

    if(qtd==0){
        printf("Nenhum cliente cadastrado!!!\n");
    } else if(qtd>0){
        printf("Lista de clientes atualizada com sucesso!!!\n");
    }
}

void liberaCli(cliente **p){
    if(*p!=NULL){
        liberaCli(&(*p)->prox);
        free(*p);
    }
}
