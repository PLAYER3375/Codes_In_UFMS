/*
NOME: Matheus Henrique dos Santos Gomes
DATA: 21/08/2025
ALGORITMOS E PROGRAMAÇÃO 2
PROJETO: SISTEMA DE CADASTRO DE ALUNOS
*/

/*
1)Crie uma struct para representar os alunos de Algoritmos e Programação II do 2ºsem. 2025.

2)Escreva um programa que mantém um conjunto de alunos (no máximo 50) e forneça para o usuário as seguintes opções:
-Cadastrar um novo aluno
-Remover um aluno através do RGA
-Atualizar notas de um aluno através do RGA
-Exibir o nome, as três notas e a MA de todos os alunos aprovados na disciplina, ordenados por nome. 
-Exibir o nome, as três notas e a MA de todos os alunos reprovados na disciplina, ordenados decrescentemente pela MA obtida. Caso existam dois ou mais alunos com a mesma MA, esses alunos devem ser exibidos em ordem alfabética.
-Exibir as seguintes médias:
    -MA dos alunos aprovados
    -MA dos alunos reprovados
    -MA de todos os alunos
Você é livre para criar funções auxiliares caso ache conveniente.
*/

#include<stdio.h>
#include<string.h>

/*Struct que representa um aluno de Algoritmos e Programação II do 2ºsem. 2025*/
typedef struct{
    char nome[51];
    int rga;
    float p1;
    float p2;
    float tb;
    float media;
    int aprovado;
} reg_alunos;

/*Atribui a média e avisa se está aprovado, deve ser chamada após qualquer atualização nas notas de um aluno*/
void atribui(reg_alunos aluno[], int i){   
    aluno[i].media = (aluno[i].p1 + aluno[i].p2 + aluno[i].tb)/3;
    if(aluno[i].media>=6){
        aluno[i].aprovado=1;
    }
    else{
        aluno[i].aprovado=-1;
    }
}

/*Printa todos os alunos cadastrados na ordem que estão. Se ordenados por outra função, aparecerão naquela ordem*/
void printTodos(reg_alunos aluno[], int n, int aprovacao){
    int i;
    printf("||RGA||Nome do aluno||Prova 1||Prova 2||Trabalho||MA||\n");
    for(i=0; i<n; i++){
        if(aprovacao==1 && aluno[i].aprovado==1){
            printf("||%d||%s||%2.f||%2.f||%2.f||%2.f||\n", aluno[i].rga, aluno[i].nome, aluno[i].p1, aluno[i].p2, aluno[i].tb, aluno[i].media);
        } else if(aprovacao==-1 && aluno[i].aprovado==-1){
            printf("||%d||%s||%2.f||%2.f||%2.f||%2.f||\n", aluno[i].rga, aluno[i].nome, aluno[i].p1, aluno[i].p2, aluno[i].tb, aluno[i].media);
        } else if(aprovacao==0){
            printf("||%d||%s||%2.f||%2.f||%2.f||%2.f||\n", aluno[i].rga, aluno[i].nome, aluno[i].p1, aluno[i].p2, aluno[i].tb, aluno[i].media);
        }
    }
}

void printMA(reg_alunos aluno[], int n, int aprovacao){
    int i;
    printf("||RGA||Nome do aluno||MA||\n");
    for(i=0; i<n; i++){
        if(aprovacao==1 && aluno[i].aprovado==1){
            printf("||%d||%s||%2.f||\n", aluno[i].rga, aluno[i].nome, aluno[i].media);
        } else if(aprovacao==-1 && aluno[i].aprovado==-1){
            printf("||%d||%s||%2.f||\n", aluno[i].rga, aluno[i].nome, aluno[i].media);
        } else if(aprovacao==0){
            printf("||%d||%s||%2.f||\n", aluno[i].rga, aluno[i].nome, aluno[i].media);
        }
    }
}

/*Ordena os alunos pelo RGA usando a técnica bubble sort*/
void ordenadoRGA(reg_alunos aluno[], int n){
    int i, j;
    reg_alunos temp;
    /*Bubble Sort pelo RGA*/
    for(i=0; i<n-1; i++){
        for(j = 0; j < n-i-1; j++){
            /*Compara o RGA da posição que está com o próximo*/
            if(aluno[j].rga > aluno[j+1].rga){
                /*Guarda temporariamente um aluno*/
                temp = aluno[j];
                /*Atribui o próximo aluno para a posição do aluno que você está*/
                aluno[j] = aluno[j+1];
                /*Devolve o aluno temporario para a próxima posição*/
                aluno[j+1] = temp;
                /*Ao fim, você pegou o próximo aluno e colocou na posição em que está, jogando o aluno que ali estava para frente(tornando ele o próximo)*/
            }
        }
    }
}

/*Ordena os alunos pelo nome usando a técnica bubble sort*/
void ordenadoNome(reg_alunos aluno[], int n){
    int i, j;
    reg_alunos temp;
    /*Bubble Sort pelo nome*/
    for(i=0; i<n-1; i++){
        for(j = 0; j < n-i-1; j++){
            /*Compara o nome da posição que está com o próximo*/
            if(strcmp(aluno[j].nome, aluno[j+1].nome) > 0){
                /*Guarda temporariamente um aluno*/
                temp = aluno[j];
                /*Atribui o próximo aluno para a posição do aluno que você está*/
                aluno[j] = aluno[j+1];
                /*Devolve o aluno temporario para a próxima posição*/
                aluno[j+1] = temp;
                /*Ao fim, você pegou o próximo aluno e colocou na posição em que está, jogando o aluno que ali estava para frente(tornando ele o próximo)*/
            }
        }
    }
}

/*Ordena os alunos pela media usando a técnica bubble sort*/
void ordenadoMA(reg_alunos aluno[], int n){
    int i, j;
    reg_alunos temp;
    /*Bubble Sort pela media*/
    for(i=0; i<n-1; i++){
        for(j = 0; j < n-i-1; j++){
            /*Compara a media da posição que está com o próximo*/
            if(aluno[j].media < aluno[j+1].media){
                /*Guarda temporariamente um aluno*/
                temp = aluno[j];
                /*Atribui o próximo aluno para a posição do aluno que você está*/
                aluno[j] = aluno[j+1];
                /*Devolve o aluno temporario para a próxima posição*/
                aluno[j+1] = temp;
                /*Ao fim, você pegou o próximo aluno e colocou na posição em que está, jogando o aluno que ali estava para frente(tornando ele o próximo)*/
            } else if(aluno[j].media==aluno[j+1].media){
                if(strcmp(aluno[j].nome, aluno[j+1].nome) > 0){
                temp = aluno[j];
                aluno[j] = aluno[j+1];
                aluno[j+1] = temp;
                }
            }
        }
    }
}

int buscar(reg_alunos aluno[], int n, int rga){
    if(n==0){
        return -1;
    }
    else{
        if(aluno[n-1].rga==rga){
            return n-1;
        }
        else{
            return buscar(aluno, n-1, rga);
        }
    }
}

/*Cadastra o aluno pedido, usar com looping para cadastrar vários*/
void cadastro(reg_alunos aluno[], int i, int *n){
    printf("Qual o nome do aluno?");
    scanf(" %50[^\n]", aluno[i].nome);
    printf("Qual o rga do aluno?");
    scanf(" %d", &aluno[i].rga);
    printf("Qual a nota da p1 do aluno?");
    scanf(" %f", &aluno[i].p1);
    printf("Qual a nota da p2 do aluno?");
    scanf(" %f", &aluno[i].p2);
    printf("Qual a nota do tb do aluno?");
    scanf(" %f", &aluno[i].tb);
    /*Atribui a n um novo valor, pois ele marca quantos alunos estão cadastrados. Essa maneira de atribuição ocorre pela passagem de referência*/
    *n = *n + 1;
    atribui(aluno, i);
}

int main(void){
    reg_alunos aluno[51];
    int n;
    int i, j, qtd, num, aux, posic;
    char resp;
    n=0;

    do{
        printf("Escolha uma das opções:\n");
        printf("1: Cadastra alunos\n");
        printf("2: Remove alunos\n");
        printf("3: Atualiza nota pelo rga\n");
        printf("4: Mostra os alunos cadastrados ordenados\n");
        printf("5: Exibe a média dos alunos\n");

        scanf(" %d", &num);

        switch(num){
            case 1:
                printf("Quantos alunos você quer cadastrar?\n");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    cadastro(aluno, i, &n);
                }
            break;
            
            case 2:
                printf("Digite o RGA do aluno que deseja remover:\n");
                scanf(" %d", &aux);
                posic=buscar(aluno, n, aux);
                if(posic==-1){
                    printf("Não foi possível encontrar esse produto\n");
                }else if(posic<n-1){
                    for(i=posic; i<n-1; i++){
                        aluno[i]=aluno[i+1];
                    }
                    n=n-1;
                    printf("Aluno removido\n");
                }else if(posic==n-1){
                    /*proximo aluno cadastrado será por cima dele*/
                    n=n-1;
                    printf("Aluno removido\n");
                }
            break;
            
            case 3:
                printf("Digite o rga do aluno que deseja atualizar:\n");
                scanf(" %d", &rga);
                posic=buscar(aluno, n, rga);
                if(posic==-1){
                    printf("Não foi possível encontrar esse produto\n");
                }else{
                    printf("******Produto encontrado******\n");
                    printf("||%d||%s||%.2f||%.2f||%.2f||\n", aluno[posic].rga, aluno[posic].nome, aluno[posic].p1, aluno[posic].p2, aluno[posic].tb);
                    printf("Deseja atualizar qual informação?\n");
                    do{
                        printf("1: P1\n");
                        printf("2: P2\n");
                        printf("2: TB\n");
                        scanf(" %d", &aux);
                        switch(aux){
                            case 1:
                                printf("Digite a nova nota da P1:\n");
                                scanf(" %f", &aluno[posic].p1);
                                printf("Nota atualizada\n");
                            break;

                            case 2:
                                printf("Digite a nova nota da P2:\n");
                                scanf(" %f", &aluno[posic].p2);
                                printf("Nota atualizada\n");
                            break;

                            case 3:
                                printf("Digite a nova nota do TB:\n");
                                scanf(" %f", &aluno[posic].tb);
                                printf("Nota atualizada\n");
                            break;

                            default:
                                printf("Escolha SOMENTE uma das três opções:");
                            break;
                        }
                    }while(aux!=1&&aux!=2&&aux!=3)
                }
            break;

            case 4:
                printf("Escolha entre as três opções de ordenação\n");
                do{
                    aux=0;
                    printf("1:RGA\n");
                    printf("2:Nome\n");
                    printf("3:MA\n");
                    scanf(" %d", &i);
                    switch (i){
                        case 1:
                            ordenadoRGA(aluno, n);
                        break;

                        case 2:
                            ordenadoNome(aluno, n);
                        break;

                        case 3:
                            ordenadoMA(aluno, n);
                        break;
                        
                        default:
                            aux=1;
                            printf("Escolha SOMENTE entre as três opções:");
                        break;
                    }
                }while(aux==1);
                
                do{
                    aux=0;
                    printf("Escolha a visualização:\n");
                    printf("1:Visualizar todos os alunos\n");
                    printf("2:Visualizar apenas os aprovados\n");
                    printf("3:Visualizar apenas os reprovados\n");
                    scanf(" %d", &i);
                    switch (i){
                        case 1:
                            printTodos(aluno, n, 0);
                        break;

                        case 2:
                            printTodos(aluno, n, 1);
                        break;

                        case 3:
                            printTodos(aluno, n, -1);
                        break;
                        
                        default:
                            aux=1;
                            printf("Escolha SOMENTE entre as três opções:");
                        break;
                    }
                }while(aux==1);

            break;

            case 5:
                do{
                    aux=0;
                    printf("Escolha a visualização:\n");
                    printf("1:Visualizar todos os alunos\n");
                    printf("2:Visualizar apenas os aprovados\n");
                    printf("3:Visualizar apenas os reprovados\n");
                    scanf(" %d", &i);
                    switch (i){
                        case 1:
                            printMA(aluno, n, 0);
                        break;

                        case 2:
                            printMA(aluno, n, 1);
                        break;

                        case 3:
                            printMA(aluno, n, -1);
                        break;
                        
                        default:
                            aux=1;
                            printf("Escolha SOMENTE entre as três opções:");
                        break;
                    }
                }while(aux==1);
            break;

        }
        printf("Deseja fazer outra operação? y/n\n");
        scanf(" %c", &resp);
    }while(resp=='y');
    printf("\n***Fim da execução***\n");

    return 0;
}