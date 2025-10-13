#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 20

typedef struct cel{
    char descricao[max];
    int qtd;
    float valor;
    char categoria[max];
    char consumidores[max][max];
    struct cel *prox;
} celula;

float letraA(celula *lista){
    if(lista->prox==NULL){
        return lista->valor*lista->qtd;
    }else{
        return (lista->valor*lista->qtd)+letraA(lista->prox);
    }
}

celula* letraB(celula *lista){
    celula *maior;

    if(lista==NULL){
        return NULL;
    }

    if(lista->prox==NULL){
        return lista;
    }

    maior=letraB(lista->prox);

    if(lista->valor >= maior->valor){
        return lista;
    } else {
        return maior;
    }
}

int letraC(celula *lista, char categoria[]){
    if(lista==NULL){
        return 0;
    }

    if(strcmp(lista->categoria, categoria)==0){
        return lista->qtd+letraC(lista->prox, categoria);
    } else {
        return letraC(lista->prox, categoria);
    }
}


float letraD(celula *lista, char categoria[]){
    if(lista==NULL){
        return 0.0;
    }

    if(strcmp(lista->categoria, categoria)==0){
        return (lista->valor*lista->qtd)+letraD(lista->prox, categoria);
    } else {
        return letraD(lista->prox, categoria);
    }
}

int qtdPessoas(celula *item){
    int i=0;
    if(item==NULL)
        return 0;
    
    while(item->consumidores[i][0] != '\0' && i < max) { 
        i++;
    }
    return i;
}

celula* letraE(celula *lista){
    celula *prox;
    int qtdAtual, qtdProx;

    if(lista==NULL){
        return NULL;
    }

    if(lista->prox==NULL){
        return lista;
    }

    prox=letraE(lista->prox);
    qtdAtual=qtdPessoas(lista);
    
    if(prox!=NULL){
        qtdProx=qtdPessoas(prox);
    } else {
        qtdProx=-1;
    }

    if(qtdAtual >= qtdProx){
        return lista;
    } else {
        return prox;
    }
}

celula* letraF(celula *lista){
    celula *prox;
    int qtdAtual, qtdProx;

    if(lista==NULL){
        return NULL;
    }

    if(lista->prox==NULL){
        return lista;
    }

    prox=letraF(lista->prox);
    qtdAtual=qtdPessoas(lista);
    
    if(prox!=NULL){
        qtdProx=qtdPessoas(prox);
    } else {
        qtdProx=-1;
    }

    if(((lista->valor*lista->qtd)/qtdAtual) >= ((prox->valor*prox->qtd)/qtdProx)){
        return lista;
    } else {
        return prox;
    }
}

float letraG(celula *lista, char pessoa[]){
    int i=0, valida=0, qtdAtual;
    float valorAtual, valorProx;

    if(lista==NULL){
        return 0.0;
    }

    while(lista->consumidores[i][0] != '\0' && i < max) { 
        if(strcmp(lista->consumidores[i], pessoa)==0){
            valida=1;
        }
        i++;
    }

    if(valida==1){
        valorProx=letraG(lista->prox, pessoa);
        qtdAtual=qtdPessoas(lista);

        valorAtual=(lista->valor*lista->qtd)/qtdAtual;

        return valorAtual+valorProx;
    } else {
        return letraG(lista->prox, pessoa);
    }
}