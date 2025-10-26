#include"lista.h"

void menu()
{
    printf("\n");
    printf("*********************************\n");
    printf("1-STATUS DO ESTOQUE\n");
    printf("2-ADICIONAR AO ESTOQUE\n");
    printf("3-RETIRAR DO ESTOQUE\n");

    printf("4-STATUS DO PLANO DE CORTE\n");
    printf("5-ADICIONAR AO PLANO DE CORTE\n");
    printf("6-RETIRAR DO PLANO DE CORTE\n");
    printf("7-SUGESTÃO DE ORDEM PARA CORTE\n");
    printf("8-TROCAR MANUALMENTE A ORDEM DE CORTE\n");
    
    printf("9-INICIAR CORTES\n");
    printf("0-FINALIZAR\n");
    printf("*********************************\n");
    printf("Digite a opção desejada: ");
}

celula* alocaNovo(){
    celula *aux;

    aux=(celula *) malloc(sizeof(celula));

    if(aux==NULL){
        printf("Não foi possível alocar");
        return NULL;
    }

    aux->prox=NULL;

    return aux;
}

void printSeq(celula *p){
    if(p!=NULL){
        printf("%s\n", p->nome);
        printSeq(p->prox);
    }
}

void colocaFinal(celula **p, char nome[max], int espessura){
    celula *aux, *fim;

    aux=alocaNovo();
    strcpy(aux->nome, nome);

    if(*p==NULL){
        *p=aux;
    } else {
        fim=*p;
        while(fim->prox!=NULL){
            fim=fim->prox;
        }
        fim->prox=aux;
    }
}

/*
void pegaTxt(celula **p){
    FILE *file;
    char nome[max];

    file=fopen("lista.txt","r");
    if(file==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(!feof(file)){
        fscanf(file, " %[^\n]", nome);
        colocaFinNome(p, nome);
    }
    printf("Valores carregados com sucesso");
    fclose(file);
}


void colocaTxt(celula *p, char nomeArqv[]){
    FILE *file;

    file=fopen(nomeArqv,"w");
    if(file==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(p!=NULL){
        fprintf(file, "%s\n", p->nome);
        p=p->prox;
    }
    
    printf("%s salvo com sucesso", nomeArqv);
    fclose(file);
}
*/

void libera(celula **p){
    if(*p!=NULL){
        libera(&(*p)->prox);
        free(*p);
    }
}