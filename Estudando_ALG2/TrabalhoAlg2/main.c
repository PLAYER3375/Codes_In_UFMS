#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lista.h"
#include"pilha.h"

int main(void){
    int opcao=0, posicChapa=0;
    stock *estoque=NULL;
    estoque=(stock *)malloc(sizeof(stock));

    do{
        menu();
        scanf(" %d", &opcao);
        atualizaEstoque(estoque);
        switch(opcao){
            case 1:
                statusEstoque(estoque);
            break;
            
            case 2:
                addManualEstoque(estoque);
            break;

            case 3:
                printf("Observe o status do estoque:\n");
                statusEstoque(estoque);
                printf("Escolha o número da chapa que deseja retirar: ");
                scanf(" %d", &posicChapa);
                retirarEstoque(estoque, posicChapa);
            break;

            case 4:
                
            break;
            
            case 0:
                
            break;

            default:
                printf("Escolha novamente uma das opções a seguir");
            break;
        }

    }while(opcao!=0);


    return 0;
}