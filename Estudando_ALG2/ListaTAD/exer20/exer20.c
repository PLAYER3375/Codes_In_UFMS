#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}fator;

void addLista(fator **lista, int x){
    fator *novo;
    novo=(fator *)malloc(sizeof(fator));
    if(novo==NULL)
        return;

    novo->num=x;
    novo->prox=*lista;
    *lista=novo;
}

void limpaLista(fator **lista){
    fator *p;
    while(*lista!=NULL){
        p=*lista;
        *lista=(*lista)->prox;
        free(p);
    }
}

void fatoracao(fator **lista, int num){
    int i;

    while(num%2==0){
        num=num/2;
        addLista(lista, 2);
    }

    for(i=3; i<=num/i; i=i+2){
        while(num%i==0){
            num=num/i;
            addLista(lista, i);
        }   
    }

    if(num>1){
        addLista(lista, num);
    }
}

int main(void){
    FILE *arqv, *arqvResp;
    fator *lista, *p;
    int x;

    lista=NULL;
    p=NULL;
    arqv=fopen("nums.txt","r");
    if(arqv==NULL){
        printf("não pegou o arquivo");
        return 1;
    }

    arqvResp=fopen("resp.txt","w");
    if(arqvResp==NULL){
        printf("não pegou o arquivo");
        return 1;
    }

    while(!feof(arqv)){
        fscanf(arqv, "%d", &x);
        fatoracao(&lista, x);
        p=lista;
        while(p!=NULL){
            if(p->prox!=NULL){
                fprintf(arqvResp, " %d *", p->num);
            } else {
                fprintf(arqvResp, " %d\n", p->num);
            }
            p=p->prox;
        }
        limpaLista(&lista);
    }

    fclose(arqv);
    fclose(arqvResp);

    return 0;
}