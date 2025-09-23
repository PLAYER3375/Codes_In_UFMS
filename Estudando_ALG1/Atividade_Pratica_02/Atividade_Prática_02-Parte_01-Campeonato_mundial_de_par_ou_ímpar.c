/*

Jonas é o presidente da confederação mundial de par ou ímpar e contratou você para criar um sistema de classificação automático.
Você deve escrever um programa que lê as pontuações de três competidores, A, B e C e calcula a classificação final.
As pontuações são valores reais e são informados em ordem, as pontuações do competidor A, depois do competidor B e por fim do competidor C.
A classificação pode ser primeiro, segundo e terceiro colocados. Também pode haver outras possibilidades onde há empates no primeiro e/ou no segundo colocados.
Antes de iniciar a classificação, o programa deve verificar se as três pontuações informadas são válidas (valores não negativos) e encerrar a execução com uma mensagem caso não sejam.
As possíveis mensagens de resposta do programa são (X, Y e Z devem ser substituídos pelos competidores e suas pontuações):
"Os três competidores empataram em 1º lugar (X.XX ponto(s))."
"1º colocado: X (X.XX ponto(s)) / 2º colocado Y (Y.YY ponto(s)) / 3º colocado Z (Z.ZZ ponto(s))."
"empatados em 1º: X e Y (X.XX ponto(s)) / 2º colocado: Z (Z.ZZ ponto(s))."
"1º colocado: X (X.XX ponto(s)) / empatados em segundo: Y e Z (Y.YY ponto(s))."
"Uma ou mais pontuações informadas é inválida."

Exemplo 1:

Entrada: 3 2 1
Saída: 1º colocado: A (3.00 ponto(s)) / 2º colocado B (2.00 ponto(s)) / 3º colocado C (1.00 ponto(s)).

Exemplo 2:

Entrada: -1 2 3
Saída: Uma ou mais pontuações informadas é inválida.

*/

#include <stdio.h>

int main (void)
{
    float A, B, C, Npri, Nult, Nseg;
    char pri, ult, seg;
    scanf("%f %f %f", &A, &B, &C);
    if(A<0 || B<0 || C<0)
    {
        printf("Uma ou mais pontuações informadas é inválida.");
    }
    else
    {
        if(A==B && B==C)
        {
            printf("Os três competidores empataram em 1º lugar (%0.2f ponto(s)).", A);
        }
        else
        {
            if(A==B && B>C)
            {
                printf("empatados em 1º: A e B (%0.2f ponto(s)) / 2º colocado: C (%0.2f ponto(s)).", B, C);
            }
            else
            {
                if(A==C && C>B)
                {
                    printf("empatados em 1º: A e C (%0.2f ponto(s)) / 2º colocado: B (%0.2f ponto(s)).", A, B);
                }
                else
                {
                    if(B==C && C>A)
                    {
                        printf("empatados em 1º: B e C (%0.2f ponto(s)) / 2º colocado: A (%0.2f ponto(s)).", B, A);
                    }
                    else
                    {
                        if(A==B && B<C)
                        {
                            printf("1º colocado: C (%0.2f ponto(s)) / empatados em segundo: A e B (%0.2f ponto(s)).", C, B);
                        }
                        else
                        {
                            if(A==C && C<B)
                            {
                                printf("1º colocado: B (%0.2f ponto(s)) / empatados em segundo: A e C (%0.2f ponto(s)).", B, A);
                            }
                            else
                            {
                                if(B==C && C<A)
                                {
                                    printf("1º colocado: A (%0.2f ponto(s)) / empatados em segundo: B e C (%0.2f ponto(s)).", A, B);
                                }
                                else
                                {
                                    if(A>B && B>C)
                                    {
                                        pri='A';
                                        Npri=A;
                                        seg='B';
                                        Nseg=B;
                                        ult='C';
                                        Nult=C;
                                    }
                                    if(A>B && A>C && B<C)
                                    {
                                        pri='A';
                                        Npri=A;
                                        seg='C';
                                        Nseg=C;
                                        ult='B';
                                        Nult=B;
                                    }
                                    if(B>A && A>C)
                                    {
                                        pri='B';
                                        Npri=B;
                                        seg='A';
                                        Nseg=A;
                                        ult='C';
                                        Nult=C;
                                    }
                                    if(B>A && B>C && A<C)
                                    {
                                        pri='B';
                                        Npri=B;
                                        seg='C';
                                        Nseg=C;
                                        ult='A';
                                        Nult=A;
                                    }
                                    if(C>A && A>B)
                                    {
                                        pri='C';
                                        Npri=C;
                                        seg='A';
                                        Nseg=A;
                                        ult='B';
                                        Nult=B;
                                    }
                                    if(C>A && C>B && A<B)
                                    {
                                    pri='C';
                                    Npri=C;
                                    seg='B';
                                    Nseg=B;
                                    ult='A';
                                    Nult=A;
                                    }
                                    printf("1º colocado: %c (%0.2f ponto(s)) / 2º colocado %c (%0.2f ponto(s)) / 3º colocado %c (%0.2f ponto(s)).", pri, Npri, seg, Nseg, ult, Nult);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return 0;