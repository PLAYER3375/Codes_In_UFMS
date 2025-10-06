/*não acabei*/
#include<stdio.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

/*primeiro vira ultimo e segundo vira penultimo*/
void inverteKPrimeiros(celula **pilha, int k){
    int i;
    celula *pilhaaux, *ptr1, *prox, *ant, *atual;
    if(*pilha==NULL)
        return;

    pilhaaux=*pilha;
    ptr1=NULL;

    for(i=0; i<k+1; i++){
        ptr1=pilhaaux;
        pilhaaux=pilhaaux->prox;
        if(i==k){
            ptr1->prox=NULL;
        }
    }

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

    prt1->prox=pilhaaux;
}