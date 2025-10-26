#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lista.h"
#include"pilha.h"

int main(void){
    int opcao;
    stock *estoque=NULL;

    do{
        menu();
        scanf(" %d", &opcao);
        atualizaEstoque(&estoque);
        switch(opcao){
            case 1:
                statusEstoque(&estoque);
            break;
            
            case 2:
                
            break;

            case 3:
                
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