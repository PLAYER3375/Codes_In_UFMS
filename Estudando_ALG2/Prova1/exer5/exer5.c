#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct cel{
    char letra;
    struct cel *prox;
}linha;

void addPilha(linha **l, char carac){
    linha *novo;
    novo=(linha *)malloc(sizeof(linha));
    if(novo==NULL)
        return;

    novo->letra=carac;
    novo->prox=*l;
    *l=novo;
}

void addArqv(linha *l, char nomeA[]){
    FILE *arqv;
    arqv=fopen(nomeA, "a");
    if(arqv==NULL)
        return;
    
    while(l!=NULL){
        fprintf(arqv, "%c", l->letra);
        l=l->prox;
    }
    fprintf(arqv, "\n");
    
    fclose(arqv);
}

void libera(linha **l){
    linha *p;
    while(*l!=NULL){
        p=*l;
        *l=(*l)->prox;
        free(p);
    }
}

void descripto(char nomeC[], char nomeA[]){
    FILE *arqv;
    char carac;
    linha *l=NULL;
    arqv=fopen(nomeC, "r");
    if(arqv==NULL)
        return;

    while(!feof(arqv)){
        fscanf(arqv, "%c", &carac);
        if(carac!='@'){
            addPilha(&l, carac);
        } else {
            addArqv(l, nomeA);
            libera(&l);
        }
    }
}

int main(void){
    char nomeC[30], nomeA[30];
    strcpy(nomeC, "cripto.txt");
    strcpy(nomeA, "descripto.txt");

    descripto(nomeC, nomeA);

    return 0;
}