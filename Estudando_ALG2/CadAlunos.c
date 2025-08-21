#include<stdio.h>
#include<string.h>

typedef struct{
    char nome[51];
    int rga;
    float p1;
    float p2;
    float tb;
    float media;
    int aprovado;
} reg_alunos;

void atribui(reg_alunos aluno[], int i){   
    aluno[i].media = (aluno[i].p1 + aluno[i].p2 + aluno[i].tb)/3
    if(aluno[i].media>=6){
        aluno[i].aprovado=1;
    }
    else{
        aluno[i].aprovado=0;
    }
}

void ordenadoRGA(reg_alunos aluno[], int n){
    reg_alunos ordRGA[100];
    int i, j, k;
    k=0;
    for(i=0; i<n; i++){
        k++;
        for(j=0; j<k; j++){
            if(i==0){
                ordRGA[j]=aluno[i];
            }
            else{
                if(aluno[i]>ordRGA[j] && aluno[i]<ordRGA[j+1]){
                    
                }
            }
        }
    }
    printf("||RGA||Nome do aluno||Prova 1||Prova 2||Trabalho||MA||\n");

}

void cadastro(reg_alunos aluno[], int *n){
    int i;
    printf("Qual o nome do aluno?");
    scanf(" %50[^\n]", aluno[i].nome);
    printf("Qual o rga do aluno?");
    scanf(" %d", aluno[i].rga);
    printf("Qual a nota da p1 do aluno?");
    scanf(" %f", aluno[i].p1);
    printf("Qual a nota da p2 do aluno?");
    scanf(" %f", aluno[i].p2);
    printf("Qual a nota do tb do aluno?");
    scanf(" %f", aluno[i].tb);
    *n = *n + 1;
    atribui(aluno, i);
}

int main(void){
    reg_alunos aluno[100];
    int n;
    n=0;
    int i, qtd;
    int num;
    char resp;

    do{
        printf("Escolha uma das opções:\n
            1: Cadastra alunos\n
            2: Remove alunos\n
            3: Atualiza nota pelo rga\n
            4: Mostra todos os alunos cadastrados ordenados pelo rga ou nome\n
            5: Mostra todos os alunos aprovados ordenados pelo nome\n
            6: Mostra todos os alunos reprovados ordenados pela media\n
            7: Exibe a média da sala\n
            8: Exibe a média dos aprovados\n
            9: Exibe a média dos reprovados\n");
        scanf(" %d", &num);
        switch(num){
            case 1:
                printf("Quantos alunos você quer cadastrar?\n");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    cadastro(aluno, &n);
                }
            break;

            case 4:
                printf("Escolha entre as duas opções de ordenação\n
                    1:RGA
                    2:Nome");
                scanf(" %d", &qtd);
                for(i=0; i<qtd; i++){
                    cadastro(aluno, &n);
                }
            break;

        }
        printf("Deseja fazer outra operação? y/n\n");
        scanf(" %c", &resp);
    }while(resp==y);
    printf("\n***Fim do código***");

    return 0;
}