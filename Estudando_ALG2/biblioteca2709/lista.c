#include"lista.h"

void menu()
{
    printf("\n");
    printf("*********************************\n");
    printf("1-MOSTRAR LISTA\n");
    printf("2-INSERIR NO INICIO\n");
    printf("3-INSERIR NO FIM\n");
    printf("4-INSERIR EM ORDEM\n");
    printf("5-APAGAR DA LISTA\n");
    printf("6-BUSCAR NA LISTA\n");
    printf("7-SALVA LISTA EM ARQUVO EM TXT\n");
    printf("8-CARREGAR LISTA DE ARQUVO EM TXT\n");
    printf("0-SAIR\n");
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
    
    strcpy(aux->nome,"0101");
    aux->prox=NULL;

    return aux;
}

void printSeq(celula *p){
    if(p!=NULL){
        printf("%s\n", p->nome);
        printSeq(p->prox);
    }
}

void colocaIniNome(celula **p, char nome[max]){
    celula *aux;

    aux=alocaNovo();
    strcpy(aux->nome, nome);
    aux->prox=*p;
    *p=aux;
}

void colocaFinNome(celula **p, char nome[max]){
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

void colocaTxt(celula *p){
    FILE *file;

    file=fopen("lista.txt","w");
    if(file==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(p!=NULL){
        fprintf(file, "%s\n", p->nome);
        p=p->prox;
    }
    printf("Valores salvos com sucesso");
    fclose(file);
}

void libera(celula **p){
    if(*p!=NULL){
        libera(&(*p)->prox);
        free(*p);
    }
}