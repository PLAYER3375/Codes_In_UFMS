/*
NOME: Matheus Henrique dos Santos Gomes
DATA: 31/08/2025
ALGORITMOS E PROGRAMAÇÃO 2
PROJETO: SISTEMA DE CADASTRO DE PRODUTOS
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Struct que representa os produtos*/
typedef struct{
    char nome[31];
    char categoria[31];
    int cod;
    float preco;
    int qtd;
} produtos;

typedef struct{
    char categoria[31];
    int qtd;
} categorias;

/*Printa todos os produtos cadastrados na ordem que estão. Se ordenados por outra função, aparecerão naquela ordem*/
void printTodos(produtos produto[], int n){
    int i;
    printf("||CÓDIGO||NOME||CATEGORIA||PREÇO/UND||QTD||\n");
    for(i=0; i<n; i++){
        printf("||%d||%s||%s||%.2f||%d||\n", produto[i].cod, produto[i].nome, produto[i].categoria, produto[i].preco, produto[i].qtd);
    }
}

/*conta categorias*/
int contadorCAT(produtos produto[], int n, char categoria[]) {
    if(n == 0) {
        return 0;
    }
    if(strcmp(produto[n-1].categoria, categoria) == 0) {
        return produto[n-1].qtd + contadorCAT(produto, n-1, categoria);
    } else {
        return contadorCAT(produto, n-1, categoria);
    }
}

/*Ordena os produtos pelo QTD usando a técnica bubble sort*/
void ordenadoQTD(produtos produto[], int n){
    int i, j;
    produtos temp;
    /*Bubble Sort pelo QTD*/
    for(i=0; i<n-1; i++){
        for(j = 0; j < n-i-1; j++){
            /*Compara o QTD da posição que está com o próximo*/
            if(produto[j].qtd > produto[j+1].qtd){
                /*Guarda temporariamente um produto*/
                temp = produto[j];
                /*Atribui o próximo produto para a posição do produto que você está*/
                produto[j] = produto[j+1];
                /*Devolve o produto temporario para a próxima posição*/
                produto[j+1] = temp;
                /*Ao fim, você pegou o próximo produto e colocou na posição em que está, jogando o produto que ali estava para frente(tornando ele o próximo)*/
            } else if(produto[j].qtd == produto[j+1].qtd){
                if(strcmp(produto[j].nome, produto[j+1].nome) > 0){
                /*Guarda temporariamente um produto*/
                temp = produto[j];
                /*Atribui o próximo produto para a posição do produto que você está*/
                produto[j] = produto[j+1];
                /*Devolve o produto temporario para a próxima posição*/
                produto[j+1] = temp;
                /*Ao fim, você pegou o próximo produto e colocou na posição em que está, jogando o produto que ali estava para frente(tornando ele o próximo)*/
                }
            }
        }
    }
}

/*Ordena os produtos pelo nome usando a técnica bubble sort*/
void ordenadoNome(produtos produto[], int n){
    int i, j;
    produtos temp;
    /*Bubble Sort pelo nome*/
    for(i=0; i<n-1; i++){
        for(j = 0; j < n-i-1; j++){
            /*Compara o nome da posição que está com o próximo*/
            if(strcmp(produto[j].nome, produto[j+1].nome) > 0){
                /*Guarda temporariamente um produto*/
                temp = produto[j];
                /*Atribui o próximo produto para a posição do produto que você está*/
                produto[j] = produto[j+1];
                /*Devolve o produto temporario para a próxima posição*/
                produto[j+1] = temp;
                /*Ao fim, você pegou o próximo produto e colocou na posição em que está, jogando o produto que ali estava para frente(tornando ele o próximo)*/
            }
        }
    }
}

/*Ordena os produtos pela categoria usando a técnica bubble sort*/
void ordenadoCAT(categorias vetCAT[], int n){
    int i, j;
    categorias temp;
    /*Bubble Sort pelo nome*/
    for(i=0; i<n-1; i++){
        for(j = 0; j < n-i-1; j++){
            if(strcmp(vetCAT[j].categoria, vetCAT[j+1].categoria) > 0){
                temp = vetCAT[j];
                vetCAT[j] = vetCAT[j+1];
                vetCAT[j+1] = temp;
            }
        }
    }
}

/*funcao de busca recursiva*/
int buscar(produtos produto[], int n, int cod){
    if(n==0){
        return -1;
    }
    else{
        if(produto[n-1].cod==cod){
            return n-1;
        }
        else{
            return buscar(produto, n-1, cod);
        }
    }
}

/*Cadastra o produto pedido, usar com looping para cadastrar vários*/
void cadastro(produtos produto[], int i, int *n){
    int valido;

    do {
        printf("Qual o código do produto?\n");
        scanf(" %d", &produto[i].cod);
        valido=buscar(produto, *n, produto[i].cod);
        if(valido!=-1){
            printf("Código já registrado, digite outro.\n");
        }
    } while(valido!=-1);
    
    printf("Qual a categoria do produto?\n");
    scanf(" %30[^\n]", produto[i].categoria);
    printf("Qual o nome do produto?\n");
    scanf(" %30[^\n]", produto[i].nome);
    printf("Qual o preço do produto?\n");
    scanf(" %f", &produto[i].preco);
    printf("Qual a quantidade do produto?\n");
    scanf(" %d", &produto[i].qtd);
    /*Atribui a n um novo valor, pois ele marca quantos produtos estão cadastrados. Essa maneira de atribuição ocorre pela passagem de referência*/
    *n = *n + 1;
}

void leituraarq(produtos produto[], FILE *prodfile, int qtdReg, int *n){
    int m, i;
    fscanf(prodfile, "%d", &m);
    m=m+*n;
    for(i=qtdReg; i<m; i++){
        fscanf(prodfile, "\n%d;%30[^;];%30[^;];%d;%f", &produto[i].cod, produto[i].nome, produto[i].categoria, &produto[i].qtd, &produto[i].preco);
    }

    *n=m;
}

int main(void){
    int n;
    int i, j, cod, qtd, num, num2, aux, posic, qtdCAT, total, achou;
    char localarq[100];
    categorias *temp;
    produtos *produto;
    int qtdMAX;
    FILE *prodfile;
    
    n=0;
    prodfile=NULL;
    
    printf("Qual a capacidade máxima de produtos diferentes no seu sistema?\n");
    scanf(" %d", &qtdMAX);
    produto=(produtos *) malloc(qtdMAX * sizeof(produtos));
    if(produto==NULL){
        printf("\nNão foi possível alocar memoria\n");
        return 0;
    }

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
                printf("Você deseja cadastrar manualmente ou por arquivo?\n");
                printf("1: Cadastrar novos produtos manualmente\n");
                printf("2: Cadastrar novos produtos por um arquivo\n");
                scanf(" %d", &num2);
                switch(num2){
                    case 1:
                        printf("Quantos produtos você deseja cadastrar?\n");
                        scanf(" %d", &qtd);
                        for(i=0; i<qtd; i++){
                            cadastro(produto, n, &n);
                        }
                    break;

                    case 2:
                        do{
                            aux=0;
                            printf("Informe o local do arquivo:\n");
                            scanf(" %s", localarq);
                            prodfile=fopen(localarq, "r");
                            if(prodfile==NULL){
                                printf("\nNão foi possível encontrar o arquivo\n");
                                aux=1;
                            }
                        }while(aux==1);
                        leituraarq(produto, prodfile, n, &n);
                        fclose(prodfile);
                    break;
                }
            break;

            case 2:
                printf("Digite o código do produto que deseja remover:\n");
                scanf(" %d", &cod);
                posic=buscar(produto, n, cod);
                if(posic==-1){
                    printf("Não foi possível encontrar esse produto\n");
                }else if(posic<n-1){
                    for(i=posic; i<n-1; i++){
                        produto[i] = produto[i+1];
                    }
                    n=n-1;
                    printf("Produto removido\n");
                }else if(posic==n-1){
                    /*proximo produto cadastrado será por cima dele*/
                    n=n-1;
                    printf("Produto removido\n");
                }
            break;

            case 3:
                printf("Digite o código do produto que deseja atualizar:\n");
                scanf(" %d", &cod);
                posic=buscar(produto, n, cod);
                if(posic==-1){
                    printf("Não foi possível encontrar esse produto\n");
                }else{
                    printf("******Produto encontrado******\n");
                    printf("||%d||%s||%s||%.2f||%d||\n", produto[posic].cod, produto[posic].nome, produto[posic].categoria, produto[posic].preco, produto[posic].qtd);
                    
                    printf("Deseja atualizar qual informação?\n");
                    printf("1: Preço\n");
                    printf("2: Quantidade\n");
                    scanf(" %d", &aux);
                    switch(aux){
                        case 1:
                            printf("Digite o novo preço:\n");
                            scanf(" %f", &produto[posic].preco);
                            printf("Preço atualizado\n");
                        break;

                        case 2:
                            printf("Digite a nova quantidade:\n");
                            scanf(" %d", &produto[posic].qtd);
                            printf("Quantidade atualizada\n");
                        break;
                    }
                    printf("Produto atualizado\n");
                }
            break;

            case 4:
                ordenadoNome(produto, n);
                printTodos(produto, n);
            break;

            case 5:
                ordenadoQTD(produto, n);
                printTodos(produto, n);
            break;

            case 6:
                qtdCAT=0;
                temp=(categorias *) malloc(n * sizeof(categorias));
                if(temp==NULL){
                    printf("\nNão foi possível alocar memória\n");
                } else {

                    for(i=0; i<n; i++){
                        achou = 0;
                        for(j = 0; j < qtdCAT; j++){
                            if(strcmp(temp[j].categoria, produto[i].categoria) == 0){
                                achou = 1;
                            }
                        }
                        if(achou==0){
                            strcpy(temp[qtdCAT].categoria, produto[i].categoria);
                            qtdCAT++;
                        }
                    }
                    ordenadoCAT(temp, qtdCAT);
                    printf("\n||CATEGORIA||TOTAL DE ITENS||\n");
                    for(i=0; i<qtdCAT; i++){
                        total=contadorCAT(produto, n, temp[i].categoria);
                        printf("||%s||%d||\n", temp[i].categoria, total);
                    }

                    free(temp);
                }
            break;
            
            case 0:
                printf("\n***Fim da execução***\n");
            break;
        }
    }while(num!=0);

    free(produto);

    return 0;
}