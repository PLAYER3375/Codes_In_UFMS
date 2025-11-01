#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cliente.h"
#include"stock.h"

typedef struct celula{
    cliente *cliente;
    char corChapa[max];
    int espessura;
    int cortado;
    int horaIni;
    int minIni;
    int horaFim;
    int minFim;
    struct celula *prox;
}planoCorte;

planoCorte* alocaNovoPla(){
    planoCorte *aux=NULL;

    aux=(planoCorte *) malloc(sizeof(planoCorte));

    if(aux==NULL){
        printf("Não foi possível alocar");
        return NULL;
    }

    aux->cortado=0;
    aux->prox=NULL;

    return aux;
}

void colocaFinalPla(planoCorte *p, cliente *Cli, int id, char nome[max], int espessura){
    planoCorte *aux=NULL, *fim=NULL;

    aux=alocaNovoPla();
    aux->cliente=Cli;
    strcpy(aux->corChapa, nome);
    aux->espessura=espessura;

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

int qtdPla(planoCorte *p){
    int x=0;
    while(p->prox!=NULL){
        x++;
        p=p->prox;
    }
    return x;
}

void atualizaPlano(planoCorte *p, cliente *q){
    FILE *arqv=NULL;
    char nome[max];
    int id, espessura, qtd;
    cliente *pCli=NULL;

    arqv=fopen("arquivostxt/cortes.txt", "r");
    if(arqv==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    while(fscanf(arqv, " %d, %[^,], %d;", &id, nome, &espessura)==3){
        pCli=buscaClienteID(q, id);
        if(pCli==NULL){
            printf("Cliente não encontrado, corte ignorado.\n");
        } else {
            colocaFinalPla(p, pCli, id, nome, espessura);
        }
    }

    fclose(arqv);

    qtd=qtdPla(p);

    if(qtd==0){
        printf("Nenhum corte cadastrado!!!\n");
    } else if(qtd>0){
        printf("Lista de corte atualizada com sucesso!!!\n");
    }
}

void liberaPlano(planoCorte **p){
    if(*p!=NULL){
        liberaPlano(&(*p)->prox);
        free(*p);
    }
}

void menu()
{
    printf("\n");
    printf("*********************************\n");
    printf("OPÇÕES PARA CONTROLE DE ESTOQUE:\n");
    printf("1-STATUS DO ESTOQUE\n");
    printf("2-ADICIONAR AO ESTOQUE\n");
    printf("3-RETIRAR DO ESTOQUE\n");
    printf("4-TROCAR MANUALMENTE A ORDEM DO ESTOQUE\n");

    printf("OPÇÕES PARA CONTROLE DE CLIENTES:\n");
    printf("5-LISTA DE CLIENTES\n");
    printf("6-ADICIONAR CLIENTE À LISTA\n");
    printf("7-RETIRAR CLIENTE DA LISTA\n");
    printf("8-ATUALIZAR INFORMAÇÕES DO CLIENTE NA LISTA\n");


    printf("OPÇÕES PARA CONTROLE DE PLANO DE CORTE:\n");
    printf("9-STATUS DO PLANO DE CORTE\n");
    printf("10-ADICIONAR AO PLANO DE CORTE\n");
    printf("11-RETIRAR DO PLANO DE CORTE\n");
    printf("12-TROCAR MANUALMENTE A ORDEM DE CORTE\n");
    printf("13-SUGESTÃO DE ORDEM PARA CORTE\n");

    printf("OPÇÕES PARA O REGISTRO DO DIA:\n");
    printf("14-INICIAR CORTES\n");
    printf("0-FINALIZAR\n");
    printf("*********************************\n");
    printf("Digite a opção desejada: ");
}


int main(void){
    int opcao=0, qtd=0, espessura, posicChapa=0, i, idCli=-1;
    char nome[max], ambiente[max];
    stock *estoque=NULL;
    cliente *clientes=NULL;
    planoCorte *planoDia=NULL;
    
    estoque=(stock *)malloc(sizeof(stock));
    clientes=(cliente *)malloc(sizeof(cliente));
    planoDia=(planoCorte *)malloc(sizeof(planoCorte));
    
    atualizaEstoque(estoque);
    atualizaClientes(clientes);
    atualizaPlano(planoDia, clientes);
    
    do{
        qtd=0;
        menu();
        scanf(" %d", &opcao);
        switch(opcao){
            case 1:
                statusEstoque(estoque);
            break;
            
            case 2:
                printf("*********************************\n");
                printf("AVISO: Lembre-se que uma chapa é adicionada acima da outra, formando uma pilha.\n");
                printf("Sendo assim, se for adicionar mais de uma chapa, deve começar de baixo para cima.\n");
                printf("*********************************\n");
                printf("Deseja adicionar quantas chapas?\n");
                scanf(" %d", &qtd);

                for(i=0; i<qtd; i++){
                    printf("Digite a cor da chapa: \n");
                    scanf(" %[^\n]", nome);
                    printf("Digite a espessura da chapa: \n");
                    scanf(" %d", &espessura);
                    colocaInicio(estoque, nome, espessura);
                    printf("Chapa adicionada com sucesso!!!\n");
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
                printf("AVISO: Lembre-se que uma chapa é adicionada acima da outra, formando uma pilha.\n");
                printf("Sendo assim, PEGAR UMA CHAPA E COLOCAR ELA EM OUTRA POSIÇÃO significa:\n");
                printf("Retirar todas que estão acima dela ou, em alguns casos, até mesmo as abaixo da mesma.\n");
                printf("*********************************\n");
                printf("QUANTAS CHAPAS VOCÊ IRÁ MANIPULAR?\n");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    statusEstoque(estoque);
                    printf("Digite a posição da chapa que deseja manipular: \n");
                    scanf(" %d", &posicChapa);
                    printf("Digite a posição que deseja deixar a chapa: \n");
                    scanf(" %d", &espessura);
                    trocaEstoque(estoque, posicChapa, espessura);
                    printf("Chapa movida com sucesso!!!\n");
                }
            break;

            case 5:
                statusCliente(clientes);
            break;
            
            case 6:
                printf("Deseja adicionar quantos clientes?\n");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    do{
                        printf("Digite o ID do cliente: \n");
                        scanf(" %d", &idCli);
                        espessura=buscaClienteIDint(clientes->prox, idCli);
                        if(espessura==1){
                            printf("Outro cliente possui o mesmo id, por favor, refaça o cadastro.\n");
                        }
                    }while(espessura==1);
                    printf("Digite o nome do cliente: \n");
                    scanf(" %[^\n]", nome);
                    printf("Digite os ambientes do cliente: \n");
                    scanf(" %[^\n]", ambiente);
                    do{
                        printf("Digite a prioridade do cliente (de 1 até 5, sendo 5 a prioridade mais alta): \n");
                        scanf(" %d", &posicChapa);
                        if(posicChapa<1 || posicChapa>5){
                            printf("Escolha SOMENTE entre 1 e 5.\n");
                        }
                    }while(posicChapa<1 || posicChapa>5);
                    colocaFinalCli(clientes, idCli, nome, posicChapa, ambiente);
                    printf("Cliente adicionado com sucesso!!!\n");
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
