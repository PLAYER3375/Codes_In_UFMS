/*

A empresa Mato Motors realiza testes de desempenho em diferentes modelos de carros e deseja calcular a média de eficiência de
combustível de cinco veículos que foram testados sob condições idênticas. No entanto, a empresa quer garantir que apenas os resultados
significativos sejam considerados na média.
O problema é que, ocasionalmente, os sensores usados para medir a eficiência podem falhar ou produzir leituras duplicadas que não refletem
as verdadeiras condições do teste. Para manter a integridade dos dados, a empresa deseja que você desenvolva um programa que leia os cinco
valores de eficiência de combustível e calcule a média apenas dos valores que são diferentes entre si. Isso significa que, se algum
valor aparecer mais de uma vez, ele não deve ser contado mais de uma vez na média.
Por exemplo, se os valores coletados forem 30, 30, 35, 40 e 40, a média deve ser calculada usando apenas os valores únicos (30, 35, 40),
resultando em uma média de 35. Isso ajudará a empresa a ter uma visão mais clara e precisa do desempenho dos carros, sem ser influenciada
por dados duplicados que podem indicar falhas nos sensores ou erros de leitura.

Exemplo de entrada:
30 30 35 40 40
Exemplo de saída:
35.0

*/

#include <stdio.h>

int main(void)
{
    float media, soma, divis, x, y, z, w, k;
    scanf("%f %f %f %f %f", &x, &y, &z, &w, &k);
    soma=x;
    divis=1;
    if(y!=x)
    {
        soma=soma+y;
        divis=divis + 1;
    }
    if(z!=x && z!=y)
    {
        soma=soma+z;
        divis=divis + 1;
    }
    if(w!=x && w!=y && w!=z)
    {
        soma=soma+w;
        divis=divis + 1;
    }
    if(k!=x && k!=y && k!=z && k!=w)
    {
        soma=soma+k;
        divis=divis + 1;
    }
    media=soma/divis;
    printf("%f", media);
    
    
    return 0;
}