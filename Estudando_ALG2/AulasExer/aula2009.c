#include<stdio.h>
#include<time.h>

int main(void){
    int i, n, soma;
    float  result;
    clock_t inicio, fim;
    soma=0;

    scanf("%d", &n);
    inicio=clock();
    /*complexidade de tempo o(n)*/
    for(i=1; i<=n; i++){
        soma=soma+i;
    }
    fim=clock();

    result=(fim-inicio)/CLOCKS_PER_SEC;

    printf("%d\n", soma);
    printf("%f", result);

    return 0;
}