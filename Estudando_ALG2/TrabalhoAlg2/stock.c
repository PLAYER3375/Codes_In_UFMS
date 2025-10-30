#include"stock.h"

stock* alocaNovo(){
    stock *aux=NULL;

    aux=(stock *) malloc(sizeof(stock));

    if(aux==NULL){
        printf("Não foi possível alocar\n");
        return NULL;
    }

    aux->prox=NULL;

    return aux;
}

void colocaInicio(stock *p, char nome[max], int espessura){
    stock *aux=NULL;

    aux=alocaNovo();
    strcpy(aux->corChapa, nome);
    aux->espessuraChapa=espessura;
    aux->prox=p->prox;
    p->prox=aux;
}

void colocaFinal(stock *p, char nome[max], int espessura){
    stock *aux=NULL, *fim=NULL;

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

void atualizaEstoque(stock *p){
    FILE *arqv=NULL;
    char nome[max];
    int espessura, qtd;
    arqv=fopen("arquivostxt/estoque.txt", "r");
    if(arqv==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(fscanf(arqv, " %[^,], %d;", nome, &espessura)==2){
        colocaFinal(p, nome, espessura);
    }

    fclose(arqv);

    qtd=qtdChapas(p);

    if(qtd==0){
        printf("Estoque vazio!!!\n");
    } else if(qtd>0){
        printf("Estoque atualizado com sucesso!!!\n");
    }
}

void statusEstoque(stock *p){
    int qtd, i=1;
    
    qtd=qtdChapas(p);

    if(qtd>0){
        printf("As chapas que estão disponíveis estão na seguinte sequência:\n");
        printf("|\n");
        printf("V\n");
        p=p->prox;
        while(p!=NULL){
            printf("%d-%s %dmm\n", i, p->corChapa, p->espessuraChapa);
            i++;
            p=p->prox;
        }
    } else {
        printf("Nenhuma chapa disponível!!!\n");
    }
}

void retirarEstoque(stock *p, int posicChapa){
    stock *aux=NULL;
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

void liberaEstoque(stock *p){
    if(p!=NULL){
        liberaEstoque(p->prox);
        free(p);
    }
}

void guardaEstoque(stock *p){
    FILE *arqv=NULL;
    arqv=fopen("arquivostxt/estoque.txt", "w");
    if(arqv==NULL){
        printf("Não foi possível abrir o arquivo!!!");
        return;
    }

    p=p->prox;
    while(p!=NULL){
        fprintf(arqv, "%s, %d;\n", p->corChapa, p->espessuraChapa);
        p=p->prox;
    }

    fclose(arqv);
}

void trocaEstoque(stock *p, int posicIni, int posicFim){
    stock *ant1=NULL, *ant2=NULL, *atual=NULL;
    int qtd, i;

    qtd=qtdChapas(p);

    if(posicIni>qtd || posicIni<1 || posicFim<1 || posicFim>qtd){
        printf("Posição da chapa inválida");
    } else {
        ant1=p;
        for(i=1; i<posicIni; i++){
            ant1=ant1->prox;
        }
        atual=ant1->prox;
        ant1->prox=atual->prox;
        ant2=p;
        for(i=1; i<posicFim; i++){
            ant2=ant2->prox;
        }
        atual->prox=ant2->prox;
        ant2->prox=atual;
    }
}