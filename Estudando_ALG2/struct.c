#include<stdio.h>

typedef struct{
    char nome[50];
    int idade;
    float nota;
} aluno;

int main() {
    /*precisa chamar a estrutura e apelidar ela dentro da main*/
    aluno a1;
    aluno a2;

    /*para dar valor nas var da struct precisa usar o <apelido>.<nome da var de dentro da struct>*/
    printf("Digite o nome do aluno 1: ");
    scanf(" %49[^\n]", a1.nome);
    printf("Digite a idade do aluno 1: ");
    scanf(" %d", &a1.idade);
    printf("Digite a nota do aluno 1: ");
    scanf(" %f", &a1.nota);

    /*na hora de apresentar é o mesmo esquema de colocar as coisas*/
    printf("Nome: %s\n", a1.nome);
    printf("Idade: %d\n", a1.idade);
    printf("Nota: %.2f\n", a1.nota);

    return 0;
}