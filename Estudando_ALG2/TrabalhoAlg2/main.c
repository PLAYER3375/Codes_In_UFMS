#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lista.h"
#include"stock.h"

int main(void){
    int opcao=0, qtd=0, espessura, posicChapa=0, i;
    char nome[max];
    stock *estoque=NULL;
    estoque=(stock *)malloc(sizeof(stock));
    atualizaEstoque(estoque);
    do{
        qtd=0;
        menu();
        scanf(" %d", &opcao);
        switch(opcao){
            case 1:
                statusEstoque(estoque);
            break;
            
            case 2:
                printf("Deseja adicionar quantas chapas?\n");
                scanf(" %d", &qtd);
                printf("AVISO: Lembre-se que uma chapa é adicionada acima da outra, formando uma pilha.\n");
                printf("Sendo assim, se for adicionar mais de uma chapa, deve começar de baixo para cima.\n");

                for(i=0; i<qtd; i++){
                    printf("Digite a cor da chapa: \n");
                    scanf(" %[^\n]", nome);
                    printf("Digite a espessura da chapa: \n");
                    scanf(" %d", &espessura);
                    colocaInicio(estoque, nome, espessura);
                }
            break;

            case 3:
                statusEstoque(estoque);
                printf("Escolha o número da chapa que deseja retirar: ");
                scanf(" %d", &posicChapa);
                retirarEstoque(estoque, posicChapa);
            break;

            case 4:
                printf("*********************************\n");
                printf("QUANTAS CHAPAS VOCÊ IRÁ MANIPULAR?\n");
                printf("AVISO: Lembre-se que uma chapa é adicionada acima da outra, formando uma pilha.\n");
                printf("Sendo assim, PEGAR UMA CHAPA E COLOCAR ELA EM OUTRA POSIÇÃO significa:\n");
                printf("Retirar todas que estão acima dela ou, em alguns casos, até mesmo as abaixo da mesma.\n");
                printf("*********************************\n");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    statusEstoque(estoque);
                    printf("Digite a posição da chapa que deseja manipular: \n");
                    scanf(" %d", &posicChapa);
                    printf("Digite a posição que deseja deixar a chapa: \n");
                    scanf(" %d", &espessura);
                    trocaEstoque(estoque, posicChapa, espessura);
                }
            break;
            
            case 0:
                guardaEstoque(estoque);
                estoque=estoque->prox;
                liberaEstoque(estoque);
            break;

            default:
                printf("Escolha novamente uma das opções a seguir");
            break;
        }

    }while(opcao!=0);


    return 0;
}