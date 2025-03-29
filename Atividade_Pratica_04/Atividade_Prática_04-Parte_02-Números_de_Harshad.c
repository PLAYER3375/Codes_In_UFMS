#include <stdio.h>

int main(void)
{
    int num, maisperto, i, j, aux1, aux2, cont, cont2, soma, guarda1, guarda2, teste, paraverif;
    scanf("%d", &num);
    while(num!=0)
    {
        aux1=num;
        cont=0;
        soma=0;
        aux2=num;
        guarda2=0;
        guarda1=0;
        while(aux1!=0)
        {
            aux1=aux1/10;
            cont=cont+1;
        }
        for(i=1; i<=cont; i++)
        {
            aux1=aux2%10;
            soma=soma+aux1;
            aux2=aux2/10;
        }
        if(num%soma==0)
        {
            printf("%d\n", num);
        }
        else
        {
            for(j=num; j>0; j--)
            {
                cont2=0;
                soma=0;
                aux2=j;
                aux1=0;
                for(i=1; i<=cont; i++)
                {
                    aux1=aux2%10;
                    soma=soma+aux1;
                    aux2=aux2/10;
                }
                if(j%soma==0)
                {
                    guarda1=j;
                    teste=num-guarda1;
                    paraverif=num+teste;
                    aux1=paraverif;
                    while(aux1!=0)
                    {
                        aux1=aux1/10;
                        cont2=cont2+1;
                    }
                    soma=0;
                    aux2=paraverif;
                    for(i=1; i<=cont2; i++)
                    {
                        aux1=aux2%10;
                        soma=soma+aux1;
                        aux2=aux2/10;
                    }
                    if(paraverif%soma==0)
                    {
                        guarda2=paraverif;
                        j=0;
                    }
                    else
                    {
                        j=0;
                    }
                }
                
            }
            if(guarda2>0)
            {
                printf("%d ou %d\n", guarda1, guarda2);
            }
            else
            {
                printf("%d\n", guarda1);
            }
        }
        scanf("%d", &num);
    }
    
    return 0;
}