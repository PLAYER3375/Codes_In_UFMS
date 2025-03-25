/*

Pedro e Carol moram em cidades distantes (A e B, respectivamente) e combinaram de se encontrar em uma cidade (C)
que fica no caminho das duas cidades, e os dois querem chegar no mesmo horário na cidade escolhida. Considere que eles
vão se deslocar de carro a uma velocidade constante.

Escreva um algoritmo que receba a distância entre as cidades A e B (km), a distância entre as cidades B e C (km), a
velocidade de Pedro (km/h), e o horário de partida de Pedro (hh:mm). O seu algoritmo deve definir qual horário (hh:mm)
Carol precisa sair de sua cidade considerando que ela viajará à 50% da velocidade de Pedro.

Exemplo:

Entrada: 100 40 20.0 12:00
Saída: 11:0

*/

#include <stdio.h>

int main(void)
{
    float Vp, Vc, Tp, Tc;
    int Hp, Mp, Hc, Mc, Dab, Dac, Dbc, Horachegada, Minutochegada, Horapartida, Minutopartida, aux;
    
    scanf("%d %d %f %d:%d", &Dab, &Dbc, &Vp, &Hp, &Mp);
    
    Dac=Dab-Dbc;
    if(Dac<0)
    {
        Dac=Dac*-1;
    }
    
    Tp=Dac/Vp;
    Minutochegada=Mp+(Tp*60);
    Horachegada=Hp;
    if(Minutochegada>=60)
    {
        Horachegada=Horachegada+(Minutochegada/60);
        Minutochegada=Minutochegada%60;
    }
    Vc=Vp/2;
    Tc=Dbc/Vc;
    Mc=Tc*60;
    if(Mc>=60)
    {
        Hc=Mc/60;
        Mc=Mc%60;
    }
    Horapartida=Horachegada-Hc;
    Minutopartida=Minutochegada-Mc;
    if(Horapartida>=24)
    {
        Horapartida=Horapartida%24;
    }
    if(Horapartida<0)
    {
        Horapartida=24+Horapartida;
    }
    printf("%d:%d", Horapartida, Minutopartida);
    
    return 0;
}