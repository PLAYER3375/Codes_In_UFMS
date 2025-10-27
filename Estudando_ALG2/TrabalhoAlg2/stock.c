#include"stock.h"

stock* alocaNovo(){
    stock *aux;

    aux=(stock *) malloc(sizeof(stock));

    if(aux==NULL){
        printf("Não foi possível alocar\n");
        return NULL;
    }

    aux->prox=NULL;

    return aux;
}

void colocaInicio(stock *p, char nome[max], int espessura){
    stock *aux;

    aux=alocaNovo();
    strcpy(aux->corChapa, nome);
    aux->espessuraChapa=espessura;
    aux->prox=p->prox;
    p=aux;
}

void colocaFinal(stock *p, char nome[max], int espessura){
    stock *aux, *fim;

    aux=alocaNovo();
    strcpy(aux->corChapa, nome);
    aux->espessuraChapa=espessura;

    if(p->prox==NULL){
        p->prox=aux;
    } else {
        fim=p->prox;
        while(fim->prox!=NULL){
            fim=fim->prox;
        }
        fim->prox=aux;
    }
}

int qtdChapas(stock *p){
    int x=0;
    while(p->prox!=NULL){
        x++;
        p=p->prox;
    }
    return x;
}

void atualizaEstoque(stock **p){
    FILE *arqv;
    char nome[max];
    int espessura, qtd;
    arqv=fopen("estoque.txt", "r");
    if(arqv==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(fscanf(arqv, " %[^,], %d;", nome, &espessura)==2){
        colocaFinal(p, nome, espessura);
    }

    fclose(arqv);

    qtd=qtdChapas(*p);

    if(qtd==0){
        printf("Estoque vazio!!!\n");
    } else if(qtd>0){
        printf("Estoque atualizado com sucesso!!!\n");
    }
}

void addManualEstoque(stock *p){
    char nome[max];
    int espessura, qtd=0, i;

    printf("Deseja adicionar quantas chapas?\n");
    scanf(" %d", &qtd);
    printf("AVISO: Lembre-se que uma chapa é adicionada acima da outra, formando uma pilha.\n");
    printf("Sendo assim, se for adicionar mais de uma chapa, deve começar de baixo para cima.\n");

    for(i=0; i<=qtd; i++){
        printf("Digite a cor da chapa: \n");
        scanf(" %[^\n]", nome);
        printf("Digite a espessura da chapa: \n");
        scanf(" %d", &espessura);
        colocaInicio(p, nome, espessura);
    }
}

void statusEstoque(stock *p){
    int qtd, i=1;
    
    qtd=qtdChapas(p);

    if(qtd>0){
        printf("As chapas que estão disponíveis estão na seguinte sequência:\n");
        printf("|\n");
        printf("V\n");
        while(p!=NULL){
            printf("%d-%s %dmm\n", i, p->corChapa, p->espessuraChapa);
            i++;
        }
    } else {
        printf("Nenhuma chapa disponível!!!\n");
    }
}

void retirarEstoque(stock *p, int posicChapa){
    stock *aux;
    int qtd, i;

    qtd=qtdChapas(p);

    if(posicChapa>qtd || posicChapa<1){
        printf("Posição da chapa inválida");
    } else {
        for(i=1; i<posicChapa; i++){
            p=p->prox;
        }
        aux=p->prox;
        p->prox=aux->prox;
        free(aux);
    }
}