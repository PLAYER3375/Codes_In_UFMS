#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lista.h"

int main(void){
    int opcao;
    char nome[max];
    celula *p;

    p=NULL;

    do{
        menu();
        scanf(" %d", &opcao);

        switch(opcao){
            case 1:
                printSeq(p);
            break;
            
            case 2:
                printf("Adicione um nome:");
                scanf(" %[^\n]", nome);
                colocaIniNome(&p, nome);
            break;

            case 3:
                printf("Adicione um nome:");
                scanf(" %[^\n]", nome);
                colocaFinNome(&p, nome);
            break;
        }

    }while(opcao!=0);
    
    libera(&p);

    printf("***Fim da execução***\n");

    return 0;
}