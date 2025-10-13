/*não acabei*/
#include<stdio.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

int qtdElementos(celula *pilha){
    int i=0;

    if(pilha==NULL)
        return 0;

    while(pilha!=NULL){
        pilha=pilha->prox;
        i++;
    }

    return i;
}

/*primeiro vira ultimo e segundo vira penultimo*/
void inverteKPrimeiros(celula **pilha, int k){
    int i, qtd;
    celula *pilhaaux, *ptr1, *prox, *ant, *atual;
    if(*pilha==NULL)
        return;

    qtd=qtdElementos(*pilha);

    if(qtd<k)
        return;

    pilhaaux=*pilha;
    ptr1=*pilha;

    for(i=0; i<k-1; i++){
        ptr1=ptr1->prox;
    }
    pilhaaux=ptr1->prox;
    ptr1->prox=NULL;

    prox=NULL;
    ant=NULL;
    atual=*pilha;

    while(atual!=NULL){
        prox=atual->prox;
        atual->prox=ant;
        ant=atual;
        atual=prox;
    }

    ptr1=ant;
    while(ptr1->prox!=NULL)
        ptr1=ptr1->prox;

    ptr1->prox=pilhaaux;
}