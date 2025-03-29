#include <stdio.h>

int main(void)
{
    int numlinhas, numtermos, numanterior, negav, numantanterior, termoatual, cont, i, j, k;
    scanf("%d", &numlinhas);
    for(i=1; i<=numlinhas; i++)
    {
        scanf("%d", &numtermos);
        if(numtermos==1)
        {
            printf("0");
        }
        else
        {
            if(numtermos==2)
            {
                printf("0, 1");
            }
            else
            {
                if(numtermos>=3)
                {
                    printf("0, 1, ");
                    numantanterior=0;
                    numanterior=1;
                    cont=2;
                    for(j=0; j<=numtermos-3; j++)
                    {
                        termoatual=numantanterior+numanterior;
                        numantanterior=numanterior;
                        numanterior=termoatual;
                        cont=cont+1;
                        if(cont==numtermos)
                        {
                            if(cont>=3 && cont%2!=0)
                            {
                                negav=-1*termoatual;
                                printf("%d", negav);
                            }
                            else
                            {
                                printf("%d", termoatual);
                            }
                        }
                        else
                        {
                            if(cont>=3 && cont%2!=0)
                            {
                                negav=-1*termoatual;
                                printf("%d, ", negav);
                            }
                            else
                            {
                                printf("%d, ", termoatual);
                            }
                        }
                    }
                }
            }
        }
        
        printf("\n");
    }
    
    
    return 0;
}