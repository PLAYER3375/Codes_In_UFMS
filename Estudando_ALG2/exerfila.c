#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 100;

typedef struct cel{
    char nome[max];
    struct cel *ant;
    struct cel *prox;
}fila;


int existe()

fila allocFila(fila *f1, char nome[max]){
    fila *aux, *aux2;
    int num;

    aux=(fila *) malloc(sizeof(fila));

    if(aux==NULL){
        printf("Não foi possível alocar")
        return NULL;
    } else {
        strcpy(aux->nome, nome);
        if(*f1==NULL){
            aux->ant=NULL;
            aux->prox=NULL;
        } else if(existe(*f1)==1) {
            aux->ant=f1;
            aux->prox=NULL;
        } else {
            num=existe(*f1);
            aux2=*f1;

        }

    }

}


int main(void){
    fila *F1, *F2;
    F1=NULL;
    F2=NULL;




    return 0;
}