#include"pilha.h"
#include"lista.h"

void colocaInicio(stock **p, char nome[max], int espessura){
    stock *aux;

    aux=alocaNovo();
    strcpy(aux->corChapa, nome);
    aux->espessuraChapa=espessura;
    aux->prox=*p;
    *p=aux;
}

int qtdChapas(stock *p){
    int x=0;
    while(p!=NULL){
        x++;
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

void addManualEstoque(stock **p){
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
    int qtd;
    
    qtd=qtdChapas(p);

    if(qtd>0){
        printf("As chapas que estão disponíveis estão na seguinte sequência:\n");
        printf("|\n");
        printf("V\n");
        while(p!=NULL){
            printf("%s %dmm\n", p->corChapa, p->espessuraChapa);
        }
    } else {
        printf("Nenhuma chapa disponível!!!\n");
    }
}