/*

Ivanildo trabalhou muito tempo como professor de programação mas, devido ao alto stress da profissão e cansado de lidar com colegas
de trabalho desagradáveis e alunos desinteressados, resolveu mudar de ramo e abrir uma oficina mecânica de automóveis.
Para facilitar seu trabalho, Ivanildo decidiu desenvolver um sistema para classificar os problemas mais comuns dos automóveis que
chegam à sua oficina. Ivanildo contratou você para desenvolver o sistema.
O sistema deve ler três características/sintomas do carro e diagnosticar o provável problema.
O diagrama abaixo relaciona as características/sintomas às instruções de reparo que devem ser respondidas pelo sistema.

*Diagrama_Parte03.png*

Entrada
A entrada é composta pela lista de sintomas do veículo. Os sintomas podem ser caracteres, valores reais e/ou inteiros.

Saída
A saída consiste em uma mensagem com a instrução de reparo adequada para os sintomas informados.


Exemplo 1:

Entrada: L A 5000

Saída: Trocar velas.


Exemplo 2:

Entrada: L T 3.0 I

Saída: Limpar/trocar bicos injetores.
*/

#include <stdio.h>

int main(void)
{
    char Letra;
    int Inteiro;
    float Real;
    
    scanf("%c", &Letra);
    if(Letra=='L')
    {
        scanf(" %c", &Letra);
        if(Letra=='T')
        {
            scanf("%f", &Real);
            if(Real<2.0)
            {
                printf("Inspecionar bomba de combustível e regulador de pressão.");
            }
            
            if(Real>=2.0 && Real<=4.0)
            {
                scanf(" %c", &Letra);
                if(Letra=='R')
                {
                    printf("Medir a compressão do motor");
                }
                if(Letra=='I')
                {
                    printf("Limpar/trocar bicos injetores.");
                }
            }
            if(Real>4.0)
            {
                printf("Inspecionar regulador de pressão");
            }
        }
        if(Letra=='A')
        {
            scanf("%d", &Inteiro);
            if(Inteiro>=4000 && Inteiro<=16000)
            {
                printf("Trocar velas");
            }
    
            if(Inteiro<4000 || Inteiro>16000)
            {
                printf("Trocar bobinas");
            }
        }
    }
    if(Letra=='N')
    {
        scanf(" %c", &Letra);
        if(Letra=='O')
        {
            scanf(" %c", &Letra);
            if(Letra=='N')
            {
                printf("Inspecionar sistemas de ignição e de injeção");
            }
            if(Letra=='B')
            {
                printf("Retificar  o motor.");
            }
        }
        if(Letra=='I')
        {
            scanf("%f", &Real);
            if(Real>12.2)
            {
                printf("Inspecionar motor de arranque");
            }
            if(Real<=12.2)
            {
                printf("Inspecionar bateria e/ou alternador.");
            }
        }
        
    }
    
    return 0;
}
