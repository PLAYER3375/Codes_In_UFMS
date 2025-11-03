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

void adicionaPlano(planoCorte *p, cliente *clientes, char nome[max], int espessura, int idCli){
    cliente *aux=NULL;
    aux=buscaClienteID(clientes, idCli);
    if(aux==NULL){
        printf("Cliente não encontrado, corte ignorado.\n");
        return;
    }
    colocaFinalPla(p, aux, idCli, nome, espessura);
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

void trocaPlano(planoCorte *p, int posicIni, int posicFim){
    int qtd = 0, i = 0;
    planoCorte *prev1 = NULL, *node = NULL, *prev2 = NULL;

    qtd = qtdPla(p);
    if(posicIni > qtd || posicIni < 1 || posicFim < 1 || posicFim > qtd){
        printf("Posição da corte inválida\n");
        return;
    }
    if(posicIni==posicFim)
        return;

    prev1 = p;
    for(i = 1; i < posicIni; i++) prev1 = prev1->prox;
    node = prev1->prox;         
    prev1->prox = node->prox;

    if(posicIni < posicFim) posicFim--;

    prev2 = p;
    for(i = 1; i < posicFim; i++) prev2 = prev2->prox;

    node->prox = prev2->prox;
    prev2->prox = node;
}


void retirarPlano(planoCorte *p, int idCliente){
    planoCorte *aux=NULL;
    while(p->prox!=NULL && p->prox->cliente->idCli!=idCliente){
        p=p->prox;
    }
    if(p->prox!=NULL){
        aux=p->prox;
        p->prox=aux->prox;
        free(aux);
        printf("Plano de corte removido com sucesso!!!\n");
    } else {
        printf("Plano não encontrado, operação ignorada.\n");
    }
}



void statusCortes(planoCorte *p){
    int qtd;
    char cortado[6];
    strcpy(cortado, "Não");
    
    qtd=qtdPla(p);

    if(qtd>0){
        printf("Os cortes disponíveis são:\n");
        printf("|\n");
        printf("V\n");
        p=p->prox;
        printf("  NOME DO CLIENTE  ||  AMBIENTE  ||  COR E ESPESSURA DA CHAPA  ||  CORTADA?\n");
        while(p!=NULL){
            if(p->cortado==1){
                strcpy(cortado, "Sim");
            } else {
                strcpy(cortado, "Não");
            }
            printf("  %s  ||  %s  ||  %s %dmm  ||  %s\n", p->cliente->nomeCli, p->cliente->ambiente, p->corChapa, p->espessura, cortado);
            p=p->prox;
        }
    } else {
        printf("Nenhum corte disponível!!!\n");
    }
}

void guardaNCortados(planoCorte *p){
    FILE *arqv=NULL;
    planoCorte *aux=NULL;

    arqv=fopen("arquivostxt/cortes.txt", "w");
    if(arqv==NULL){
        printf("Não foi possível abrir cortes.txt para salvar cortes\n");
        return;
    }

    aux=p->prox;
    while(aux!=NULL){
        if(aux->cortado==0){
            fprintf(arqv, "%d, %s, %d;\n", aux->cliente->idCli, aux->corChapa, aux->espessura);
        }
        aux=aux->prox;
    }

    fclose(arqv);
}

void liberaPlano(planoCorte *p){
    if(p!=NULL){
        liberaPlano(p->prox);
        free(p);
    }
}

int temChapaEmEstoque(stock *estoque, char cor[max], int espessura){
    int encontrado=0;

    if(estoque==NULL)
        return 0;

    if(strcmp(estoque->corChapa, cor)==0 && estoque->espessuraChapa==espessura){
        return 1;
    }
    encontrado=temChapaEmEstoque(estoque->prox, cor, espessura);
    return encontrado;
}

void gravaRelatorio(planoCorte *planoCorte1, stock *estoque){
    FILE *arqv=NULL;
    planoCorte *planoCorte2=planoCorte1;
    int tem=0;

    arqv=fopen("relatorioDia.txt", "w");
    if(arqv==NULL){
        printf("Não foi possível criar relatorioDia.txt\n");
        return;
    }
    fprintf(arqv, "*********************************\n");
    fprintf(arqv, "PLANOS CORTADOS:\n");
    planoCorte1=planoCorte1->prox;
    while(planoCorte1!=NULL){
        if(planoCorte1->cortado == 1){
            fprintf(arqv, "Cliente: %s | Ambiente: %s | Chapa: %s %dmm | Inicio: %02d:%02d | Fim: %02d:%02d\n", planoCorte1->cliente->nomeCli, planoCorte1->cliente->ambiente, planoCorte1->corChapa, planoCorte1->espessura, planoCorte1->horaIni, planoCorte1->minIni, planoCorte1->horaFim, planoCorte1->minFim);
        }
        planoCorte1=planoCorte1->prox;
    }
    fprintf(arqv, "*********************************\n\n");

    fprintf(arqv, "*********************************\n");
    fprintf(arqv, "PLANOS NÃO CORTADOS:\n");
    planoCorte2=planoCorte2->prox;
    while(planoCorte2!=NULL){
        if(planoCorte2->cortado==0){
            tem=temChapaEmEstoque(estoque->prox, planoCorte2->corChapa, planoCorte2->espessura);
            if(tem==1){
                fprintf(arqv, "Cliente: %s | Ambiente: %s | Chapa: %s %dmm | Em estoque: Sim\n", planoCorte2->cliente->nomeCli, planoCorte2->cliente->ambiente, planoCorte2->corChapa, planoCorte2->espessura);
            } else {
                fprintf(arqv, "Cliente: %s | Ambiente: %s | Chapa: %s %dmm | Em estoque: Não\n", planoCorte2->cliente->nomeCli, planoCorte2->cliente->ambiente, planoCorte2->corChapa, planoCorte2->espessura);
            }
        }
        planoCorte2=planoCorte2->prox;
    }
    fprintf(arqv, "*********************************\n\n");
    fclose(arqv);
    printf("Relatório do dia gerado: relatorioDia.txt\n");
}

void menu()
{
    printf("\n");
    printf("*********************************\n");
    printf("OPÇÕES PARA CONTROLE DE ESTOQUE:\n");
    printf("1-STATUS DO ESTOQUE\n");
    printf("2-ADICIONAR AO ESTOQUE\n");
    printf("3-RETIRAR DO ESTOQUE\n");
    printf("4-TROCAR MANUALMENTE A ORDEM DO ESTOQUE\n\n");

    printf("OPÇÕES PARA CONTROLE DE CLIENTES:\n");
    printf("5-LISTA DE CLIENTES\n");
    printf("6-ADICIONAR CLIENTE À LISTA\n");
    printf("7-RETIRAR CLIENTE DA LISTA\n");
    printf("8-ATUALIZAR INFORMAÇÕES DO CLIENTE NA LISTA\n\n");


    printf("OPÇÕES PARA CONTROLE DE PLANO DE CORTE:\n");
    printf("9-STATUS DO PLANO DE CORTE\n");
    printf("10-ADICIONAR AO PLANO DE CORTE\n");
    printf("11-RETIRAR DO PLANO DE CORTE\n");
    printf("12-TROCAR MANUALMENTE A ORDEM DE CORTE\n\n");

    printf("OPÇÕES PARA O REGISTRO DO DIA:\n");
    printf("13-INICIAR CORTES\n");
    printf("0-FINALIZAR\n");
    printf("*********************************\n");
    printf("Digite a opção desejada: ");
}


int main(void){
    int opcao=0, qtd=0, espessura, posicChapa=0, i, idCli=-1, hIni, mIni, hFim, mFim;
    char nome[max], ambiente[max], confirma;
    stock *estoque=NULL;
    cliente *clientes=NULL;
    planoCorte *planoDia=NULL, *percorrePlano=NULL;
    
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
                    colocaFinalCli(clientes, idCli, nome, ambiente);
                    printf("Cliente adicionado com sucesso!!!\n");
                }
            break;
            
            case 7:
                statusCliente(clientes);
                qtd=qtdClientes(clientes);
                if(qtd!=0){
                    printf("Escolha o id do cliente que deseja retirar: ");
                    scanf(" %d", &posicChapa);
                    retirarCliente(clientes, posicChapa);
                } else {
                    printf("Nenhum cliente para retirar.\n");
                }
            break;
            
            case 8:
                statusCliente(clientes);
                qtd=qtdClientes(clientes);
                if(qtd!=0){
                    do{
                      i=0;
                      printf("Escolha o id do cliente que deseja atualizar as informações: ");
                      scanf(" %d", &idCli);
                      i=buscaClienteIDint(clientes, idCli);
                      if(i==0){
                        printf("Id inválido.");
                      }
                    }while(i==0);
                    do{
                        printf("OPÇÕES DE INFORMAÇÕES ATUALIZÁVEIS:\n");
                        printf("1-ID\n");
                        printf("2-NOME\n");
                        printf("3-AMBIENTE\n");
                        printf("Qual informação deseja atualizar: ");
                        scanf(" %d", &espessura);
                    
                        switch(espessura){
                            case 1:
                                do{
                                  printf("Digite o novo ID do cliente: ");
                                  scanf(" %d", &posicChapa);
                                  i=0;
                                  i=buscaClienteIDint(clientes, posicChapa);
                                  if(i==1){
                                    printf("Outro cliente já utiliza este id.\n");
                                  }
                                }while(i==1);
                                atualizaIDCliente(clientes, idCli, posicChapa);
                            break;
                            
                            case 2:
                                printf("Digite o novo nome do cliente: ");
                                scanf(" %[^\n]", nome);
                                atualizaNomeCliente(clientes, idCli, nome);
                            break;
                            
                            case 3:
                                printf("Digite novamente os ambientes do cliente: ");
                                scanf(" %[^\n]", nome);
                                atualizaAmbiCliente(clientes, idCli, nome);
                            break;
                        }
                        if(espessura<1 || espessura>4){
                            printf("Opção inválida. Escolha outra opção.\n");
                        }
                    }while(espessura<1 || espessura>4);
                } else {
                    printf("Nenhum cliente para atualizar informações.\n");
                }
            break;
            
            case 9:
                statusCortes(planoDia);
            break;

            case 10:
                do{
                    statusCliente(clientes);
                    printf("Coloque o id do cliente que este corte irá pertencer: ");
                    scanf(" %d", &idCli);
                    i=0;
                    i=buscaClienteIDint(clientes, idCli);
                    if(i==0){
                        printf("Id inválido.");
                    }
                }while(i==0);
                printf("Qual a cor da chapa que este corte terá: ");
                scanf(" %[^\n]", nome);
                printf("Coloque espessura da chapa: ");
                scanf(" %d", &espessura);
                adicionaPlano(planoDia, clientes, nome, espessura, idCli);
            break;

            case 11:
                statusCortes(planoDia);
                qtd=qtdPla(planoDia);
                if(qtd!=0){
                    printf("Coloque o id do cliente do plano que deseja retirar: ");
                    scanf(" %d", &idCli);
                    retirarPlano(planoDia, idCli);
                } else {
                    printf("Nenhum plano para retirar.\n");
                }
            break;

            case 12:
                printf("QUANTAS MUDANÇAS NA ORDEM VOCÊ IRÁ FAZER? ");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    statusCortes(planoDia);
                    printf("Digite a posição do corte que deseja manipular: \n");
                    scanf(" %d", &posicChapa);
                    printf("Digite a posição que deseja deixar o corte: \n");
                    scanf(" %d", &espessura);
                    trocaPlano(planoDia, posicChapa, espessura);
                    printf("Corte movido com sucesso!!!\n");
                }
            break;

            case 13:{
                if(planoDia->prox==NULL){
                    printf("Nenhum corte cadastrado!!!\n");
                } else {
                    /* declaração feita no topo da função main */
                    percorrePlano = planoDia->prox;
                    while(percorrePlano!=NULL){
                        printf("Corte atual: cliente %s - chapa %s %dmm\n", percorrePlano->cliente->nomeCli, percorrePlano->corChapa, percorrePlano->espessura);
                        printf("Deseja cortar esta chapa agora? (s/n): ");
                        scanf(" %c", &confirma);
                        if(confirma=='s'){
                            /* verifica se chapa existe no estoque */
                            posicChapa = encontraPosEstoque(estoque, percorrePlano->corChapa, percorrePlano->espessura);
                            if(posicChapa > 0){
                                printf("Chapa encontrada em estoque na posição %d.\n", posicChapa);
                                printf("Digite hora e minuto de INICIO (HH MM): ");
                                scanf(" %d %d", &hIni, &mIni);
                                printf("Digite hora e minuto de FIM (HH MM): ");
                                scanf(" %d %d", &hFim, &mFim);
                                percorrePlano->horaIni=hIni;
                                percorrePlano->minIni=mIni;
                                percorrePlano->horaFim=hFim;
                                percorrePlano->minFim=mFim;
                                percorrePlano->cortado=1;
                                /* remove chapa do estoque assim que cortada */
                                retirarEstoque(estoque, posicChapa);
                                printf("Corte realizado e chapa removida do estoque.\n");
                            } else {
                                printf("Chapa não encontrada em estoque. Não é possível cortar.\n");
                            }
                        } else {
                            printf("Pulando este corte.\n");
                        }
                        percorrePlano = percorrePlano->prox;
                    }
                }
            } break;
            
            case 0: 
                guardaEstoque(estoque);
                guardaClientes(clientes);
                guardaNCortados(planoDia);
                gravaRelatorio(planoDia, estoque);
                estoque=estoque->prox;
                clientes=clientes->prox;
                planoDia=planoDia->prox;
                liberaEstoque(estoque);
                liberaCli(clientes);
                liberaPlano(planoDia);
            break;

            default:
                printf("Escolha novamente uma das opções a seguir");
            break;
        }

    }while(opcao!=0);


    return 0;
}
