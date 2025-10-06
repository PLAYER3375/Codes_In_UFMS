#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

/*primeiro vira ultimo e segundo vira penultimo*/
celula* pegaMeio(celula *lista){
    celula *ptr1, *ptr2;
    if(lista==NULL)
        return NULL;
    ptr1=lista;
    ptr2=lista;

    while(ptr2!=NULL && ptr2->prox!=NULL){
        ptr1=ptr1->prox;
        
        ptr2=ptr2->prox;
        ptr2=ptr2->prox;
    }

    return ptr1;
}