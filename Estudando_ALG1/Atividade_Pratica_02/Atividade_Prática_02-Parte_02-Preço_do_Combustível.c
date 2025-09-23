/*
João quer calcular quantos vai gastar com combustível em uma viagem para o Estado de São Paulo,
ao utilizar um automóvel que faz 12 KM/L.  O automóvel possui um tanque de 40 litros e o preço do combustível em sua cidade é R$4,80
e nas demais cidades do trajeto o preço médio é R$5,20. O tanque pode conter gasolina, e ele deseja chegar ao destino com a mesma quantidade
de combustível e economizar nos abastecimentos. Para isso, ele gostaria que você o auxiliasse através de um programa.


Entrada
Tempo gasto na viagem (em horas), a velocidade média durante a mesma (em km/h) e a quantidade atual de combustível no tanque (litros).

Saída
Valor gasto no abastecimento de combustível, com duas casas decimais após a vírgula.

Exemplo:

Entrada:
10 80 10.0

Saída:
R$ 334.67

*/

#include<stdio.h>

int main(void)
{
    int Tempgast, Velomed;
    float Litrtanq, Aguent, Valor, x, Distreal;
    
    Valor=0;
    scanf("%d %d %f", &Tempgast, &Velomed, &Litrtanq);
    Distreal=Velomed*Tempgast;
    Aguent=(40-Litrtanq)*12;
    
    if(Distreal<=Aguent)
    {
        Valor=(Distreal/12)*4.8;
    }
    else
    {
        x=Distreal-((40-Litrtanq)*12);
        Valor=((x/12)*5.2)+((40-Litrtanq)*4.8);
    }
    printf("R$ %0.2f", Valor);
    
    return 0;
}