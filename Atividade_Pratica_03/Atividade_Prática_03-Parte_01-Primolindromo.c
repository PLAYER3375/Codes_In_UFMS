#include <stdio.h>

int main(void)
{
    int a, z, x, k, troca, quant, armazen, nov, teste1, verifp, i, j;
    float verif;
    scanf("%d %d", &a, &z);
    if(a>z)
    {
        troca=z;
        z=a;
        a=troca;
    }
    for(i=a; i<=z; i++)
    {
        /*verificação de casas*/
        quant=0;
        
        if(i<=9)
        {
            quant=1;
        }
        else
        {
            if(i>=10 && i<=99)
            {
                quant=2;
            }
            else
            {
                if(i>=100 && i<=999)
                {
                    quant=3;
                }
                else
                {
                    if(i>=1000 && i<=9999)
                    {
                        quant=4;
                    }
                    else
                    {
                        if(i>=10000 && i<=99999)
                        {
                            quant=5;
                        }
                        else
                        {
                            if(i>=100000 && i<=999999)
                            {
                                quant=6;
                            }
                        }
                    }
                }
            }
        }
        
        /*verifica palindrome*/
        armazen=0;
        teste1=i;
        for(j=1; j<=quant; j++)
        {
            x=teste1%10;
            teste1=teste1/10;
            armazen=(armazen*10)+x;
        }
        if(i==armazen)
        {
            /*verifica primo*/
            verifp=0;
            if(i>1)
            {
                for(k=2; k<=i; k++)
                {
                    verif=i%k;
                    if(verif==0)
                    {
                        verifp=verifp+1;
                    }
                }
                if(verifp==1)
                {
                    printf("%d ", i);
                }
            }
        }
        
    }
    
    
    return 0;
}