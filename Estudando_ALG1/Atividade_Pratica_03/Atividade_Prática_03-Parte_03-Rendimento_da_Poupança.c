#include <stdio.h>

int main(void)
{
    float saldo, saldoant, investido, rendido, rendimes, aporte;
    int mesinicio, dura, mesatual, i;
    scanf("%d", &mesinicio);
    scanf("%d", &dura);
    saldo=0;
    investido=0;
    rendido=0;
    for(i=0; i<dura; i++)
    {
        mesatual=mesinicio+i;
        if(mesatual>12)
        {
            mesatual=mesatual%12;
        }
        if(saldo>0)
        {
            switch(mesatual)
            {
                case 1:
                    /*janeiro*/
                        rendido=rendido+saldo*0.015;
                        saldo=saldo*1.015;
                break;
                
                case 8:
                    /*agosto*/
                        rendido=rendido+saldo*0.003;
                        saldo=saldo*1.003;
                break;
                
                default:
                        rendido=rendido+(saldo*0.005);
                        saldo=saldo*1.005;
                break;
            }
        }
        scanf("%f", &aporte);
        saldo=saldo+aporte;
        if(aporte>0)
        {
            investido=investido+aporte;
        }
    }
    printf("Saldo: %0.2f \n", saldo);
    printf("Total Investido: %0.2f \n", investido);
    printf("Rendimento Total: %0.2f \n", rendido);
    
    return 0;
}