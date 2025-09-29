#include<stdio.h>
#include<stdlib.h>

typedef struct cel{
    int num;
}celula;

celula* inverte(int n, celula *pilha, int topo){
    int i, j;
    celula *pilha2;
    pilha2=(celula*) malloc(n * sizeof(celula));

    j=topo-1;
    for(i=0; i<topo; i++){
        pilha2[j].num=pilha[i].num;
        j--;
    }

    pilha=pilha2;

    
    return pilha;
}

int main(void){
    int n, i, topo;
    celula *pilha;

    topo=0;

    printf("Quantos elementos?\n");
    scanf(" %d", &n);
    pilha=(celula*) malloc(n * sizeof(celula));

    printf("Dê os elementos:\n");
    for(i=0; i<n; i++){
        scanf(" %d", &pilha[i].num);
        topo++;
    }

    pilha=inverte(n, pilha, topo);

    for(i=0; i<n; i++){
        printf("%d ", pilha[i].num);
    }
    
    return 0;
}