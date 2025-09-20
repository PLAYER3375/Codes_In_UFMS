#include<stdio.h>
#include<time.h>

int main(void){
    int i, n, soma=0;
    clock_t inicio, fim;

    scanf("%d", &n);
    inicio=clock();
    /*complexidade de tempo o(n)*/
    for(i=1; i<=n; i++){
        soma=soma+i;
    }

    printf("%d", soma);

    return 0;
}