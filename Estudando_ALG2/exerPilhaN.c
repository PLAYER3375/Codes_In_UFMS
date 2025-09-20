#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 100

typedef struct cel{
    char nome[max];
    struct cel *prox;
}fila;

fila* allocNo(char nome[max]){
    fila *aux;

    aux=(fila *) malloc(sizeof(fila));

    if(aux==NULL){
        printf("Não foi possível alocar");
        return NULL;
    }
    strcpy(aux->nome, nome);
    aux->prox=NULL;

    return aux;
}

void colocaFila(fila **f1, char nome[max]){
    fila *aux, *fim;

    aux=allocNo(nome);

    if(*f1==NULL){
        *f1=aux;
    } else {
        fim=*f1;
        while(fim->prox!=NULL){
            fim=fim->prox;
        }
        fim->prox=aux;
    }
}


void printInv(fila *F1){
    if(F1!=NULL){
        printInv(F1->prox);
        printf("%s\n", F1->nome);
    }
}

void libera(fila **F1){
    if(*F1!=NULL){
        libera(&(*F1)->prox);
        free(*F1);
    }
}

void printSeq(fila *F1){
    if(F1!=NULL){
        printf("%s\n", F1->nome);
        printSeq(F1->prox);
    }
}

int main(void){
    fila *F1, *aux;
    char nome[max];
    
    F1=NULL;
    
    do{
        scanf(" %s", nome);
        if(strcmp(nome,"fim")){
            colocaFila(&F1, nome);
        }
    }while(strcmp(nome,"fim"));

    printf("------------------------------\n");
    printSeq(F1);
    printf("------------------------------\n");
    printInv(F1);
    
    aux=F1;
    libera(&aux);

    return 0;
}