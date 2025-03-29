#include <stdio.h>

int main(void)
{
    char letra;
    int x, aux, trocado, teste, opa, soma, i, cont, j, ult, finaliza;
    finaliza==0;
    while(finaliza==0)
    {
        scanf(" %c", &letra);
        trocado=0;
        opa=0;
        teste=0;
        soma=0;
        switch(letra)
        {
            case 'a':
                scanf("%d", &x);
                while(x!=0)
                {
                    aux=x%10;
                    printf("%d", aux);
                    x=x/10;
                }
                printf("\n");
            break;
                
            case 'b':
                scanf("%d", &x);
                teste=1;
                while(x!=0)
                {
                    aux=x%2;
                    trocado=trocado+(aux*teste);
                    x=x/2;
                    teste=teste*10;
                }
                printf("%d\n", trocado);
            break;
            
            case 'c':
                scanf("%d", &x);
                teste=1;
                while(x!=0)
                {
                    aux=x%10;
                    soma=soma+(aux*teste);
                    x=x/10;
                    teste=teste*2;
                }
                printf("%d\n", soma);
            break;
            
            case 'd':
                scanf("%d", &x);
                teste=1;
                cont=-1;
                soma=1;
                j=-1;
                while(x!=0)
                {
                    aux=x%2;
                    if(aux==1)
                    {
                        j=j+1;
                    }
                    trocado=trocado+(aux*teste);
                    x=x/2;
                    teste=teste*10;
                    cont=cont+1;
                    soma=soma*10;
                }
                soma=soma/10;
                while(soma!=0)
                {
                    aux=trocado/soma;
                    trocado=trocado%soma;
                    if(aux==1)
                    {
                        printf("2^%d", cont);
                        if(j>0)
                        {
                            printf(" + ");
                            j=j-1;
                        }
                        else
                        {
                            printf(";\n");
                        }
                    }
                    cont=cont-1;
                    soma=soma/10;
                }
                
            break;
            
            case 'e':
                scanf("%d", &x);
                teste=1;
                trocado=x;
                cont=-1;
                soma=1;
                j=-1;
                while(trocado!=0)
                {
                    ult=trocado%10;
                    trocado=trocado/10;
                    cont=cont+1;
                    soma=soma*10;
                    if(ult==1)
                    {
                        j=j+1;
                    }
                }
                soma=soma/10;
                while(soma!=0)
                {
                    aux=x/soma;
                    x=x%soma;
                    if(aux==1)
                    {
                        opa=1;
                        for(i=0; i<cont; i++)
                        {
                            opa=opa*2;
                        }
                        printf("%d", opa);
                        if(j>0)
                        {
                            printf(" + ");
                            j=j-1;
                        }
                        else
                        {
                            printf(";\n");
                        }
                    }
                    cont=cont-1;
                    soma=soma/10;
                }
            break;
            case 'x':
                finaliza=1;
            break;
            default:
                printf("Código de operação inválido.\n");
            break;
        }
    }  
    
    
    return 0;
}