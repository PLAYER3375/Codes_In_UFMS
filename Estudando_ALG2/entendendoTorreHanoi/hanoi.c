#include <stdio.h>

void torre_de_hanoi(int n, char origem, char destino, char auxiliar) {
    /* Caso base: se há apenas um disco, move-o diretamente*/
    if (n == 1) {
        printf("Mover disco %d da torre %c para a torre %c\n", n, origem, destino);
        return;
    }

    /*Passo 1: Mover n-1 discos da torre de origem para a torre auxiliar,
    usando a torre de destino como auxiliar.*/
    torre_de_hanoi(n - 1, origem, auxiliar, destino);

    /*Passo 2: Mover o disco n (o maior) da torre de origem para a torre de destino.*/
    printf("Mover disco %d da torre %c para a torre %c\n", n, origem, destino);

    /*Passo 3: Mover n-1 discos da torre auxiliar para a torre de destino,
    usando a torre de origem como auxiliar.*/
    torre_de_hanoi(n - 1, auxiliar, destino, origem);
}

int main(void) {
    int num_discos;

    printf("--- Solucao da Torre de Hanoi ---\n");
    printf("Digite o numero de discos: ");
    
    scanf("%d", &num_discos);
    
    if (num_discos <= 0) {
        printf("O numero de discos deve ser maior que 0.\n");
        return 0;
    }

    printf("\nPassos para resolver a Torre de Hanoi com %d discos:\n", num_discos);

    torre_de_hanoi(num_discos, 'A', 'C', 'B');

    return 0;
}