#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct celula{
    int cod;
    struct celula *prox;
}produtos;

produtos * allocEsp(int cod){
    produtos *new;
    new=(produtos *) malloc(sizeof(produtos));
    if(new==NULL){
        printf("não foi possível alocar memória\n");
        return NULL;
    }
    new->cod=cod;
    new->prox=NULL;
    return new;
}

int busca(produtos *prod, int cod){
    int i;
    i=0;
    while(prod!=NULL){
        if(prod->cod==cod){
            return i;
        }
        
        prod=prod->prox;
        i++;
    }
    
    return -1;
}


int main(void){
    produtos *Initprod, *prod, *aux, *aux2;
    int i, cod, qtd, num, posic, valid;
    
    do{
        printf("Escolha uma das opções:\n");
        printf("1: Cadastrar um novo produto\n");
        printf("2: Remover produtos\n");
        printf("3: Atualizar dados do produto\n");
        printf("4: Listar produtos ordenados pelo nome\n");
        printf("5: Listar produtos ordenados pela quantidade\n");
        printf("6: Listar produtos ordenados pela categoria\n");
        printf("0: Encerrar o programa\n");

        scanf(" %d", &num);

        switch(num){
            case 1:
                printf("Quantos produtos você deseja cadastrar?\n");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    scanf(" %d", &cod);
                    aux=allocEsp(cod);
                    if(Initprod==NULL){
                        Initprod=aux;
                    } else {
                        prod=Initprod;
                        while(prod->prox!=NULL){
                            prod=prod->prox;
                        }
                        prod->prox=aux;
                    }
                }
                free(aux);
            break;

            case 2:
                do{
                    printf("Qual produto você deseja excluir?\n");
                    scanf(" %d", &cod);
                    aux=Initprod;
                    posic=busca(aux, cod);
                    if(posic==-1){
                        printf("Produto não encontrado, tente novamente\n");
                        valid=0;
                    } else if(posic==0){
                        Initprod=Initprod->prox;
                    } else {
                        aux=Initprod;
                        i=0;
                        while(i<posic-1){
                            aux=aux->prox;
                            i++;
                        }
                        aux2=aux->prox;
                        aux->prox=aux2->prox;
                    }
                    valid=1;
                }while(valid==0);
                free(aux2);
            break;

            case 3:
                
            break;

            case 4:
                prod=Initprod;
                do{
                    printf(" %d" prod->cod);
                    prod=prod->prox;
                }while(prod->prox!=NULL);
            break;

            case 5:
                
            break;

            case 6:
                
            break;
            
            case 0:
                printf("\n***Fim da execução***\n");
            break;
        }
    }while(num!=0);

    return 0;
}