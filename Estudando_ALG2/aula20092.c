#include<stdio.h>

int main(void){
    int i, n, soma=0;

    scanf("%d", &n);
    
    soma=(n*(n+1))/2;

    printf("%d", soma);

    return 0;
}