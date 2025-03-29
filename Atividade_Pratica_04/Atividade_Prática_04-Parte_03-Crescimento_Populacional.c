#include<stdio.h>

int main(void)
{
    int numcasos, PA, PB, i, resultMaior, resultMenor, cont;
    float GA, GB, crescdamenor, crescdamaior;
    scanf("%d", &numcasos);
    for(i=1; i<=numcasos; i++)
    {
        scanf("%d %d %f %f", &PA, &PB, &GA, &GB);
        if(GA>GB)
        {
            resultMaior=PB*((GB/100)+1);
            resultMenor=PA*((GA/100)+1);
            crescdamaior=(GB/100)+1;
            crescdamenor=(GA/100)+1;
        }
        else
        {
            resultMaior=PA*((GA/100)+1);
            resultMenor=PB*((GB/100)+1);
            crescdamaior=(GA/100)+1;
            crescdamenor=(GB/100)+1;
        }
        cont=1;
        do
        {
            resultMaior=resultMaior*crescdamaior;
            resultMenor=resultMenor*crescdamenor;
            cont=cont+1;
        }while(resultMenor<=resultMaior);
        if(cont<=100)
        {
            printf("%d anos.\n", cont);
        }
        else
        {
            printf("Mais de 1 seculo.\n");
        }
    }
    
    return 0;
}