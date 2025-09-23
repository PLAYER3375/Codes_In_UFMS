/*

Um estudante do curso de Sistemas de Informação em Três Lagoas estava cansado de passar as férias sempre na mesma rotina e decidiu planejar uma viagem. Para tanto, começou a pesquisar horários
de voos de diversas companhias aéreas, buscando a melhor conexão entre diferentes cidades. Durante essa pesquisa, ele notou algo que chamou sua atenção: em alguns casos, voos diretos
entre duas cidades apresentavam durações distintas, dependendo se eram voos de ida ou de volta.
Refletindo sobre essa observação, o estudante percebeu que a única explicação plausível seria a diferença de fusos horários entre as cidades. Ele então compreendeu que seria possível deduzir a
diferença entre esses fusos horários baseando-se apenas nos horários de partida e chegada fornecidos pelas linhas aéreas.
Para exemplificar seu raciocínio, ele pensou num voo que partia de Três Lagoas às 8:00 e chegava à cidade destino às 20:00, enquanto o voo de retorno saía da cidade destino às 8:00 e
aterrissava em Três Lagoas às 16:00. Considerando que ambos os voos, ida e volta, são realizados com aeronaves iguais e na mesma rota, a conclusão foi que o voo tinha uma duração de 10 horas e
que a cidade destino estava em um fuso horário +2 horas adiantado em relação ao de Três Lagoas.
Empolgado com essa descoberta, o estudante montou uma tabela com horários de voos de várias companhias aéreas, mas com um descuido: ele se esqueceu de anotar as datas de partida e chegada.
Isso gerou uma dúvida: se um voo parte às 20:00 e chega às 16:00, poderia ser um voo de 20 horas entre cidades do mesmo fuso horário, com a chegada no dia seguinte, ou um voo de apenas
uma hora para uma cidade que está cinco horas atrasada em relação à cidade de origem, com chegada no mesmo dia.
Sua tarefa agora é ajudar esse estudante a descobrir a duração de cada voo e a diferença de fusos horários entre as cidades de origem e destino de cada par de voos (ida e volta) da tabela,
mesmo sem ter as datas das viagens.



Entrada
A entrada é composta por 4 horários de voos, representando os momentos de partida e chegada de um voo de ida e volta entre as cidades A e B. O primeiro horário refere-se ao momento de
decolagem do voo saindo da cidade A, com o tempo sendo indicado no fuso horário local dessa cidade. O segundo horário marca a hora de aterrissagem do mesmo voo na cidade B, segundo o fuso
horário local de B. O terceiro horário indica quando o voo de retorno parte da cidade B, novamente usando o fuso horário local de B. Por fim, o quarto e último horário sinaliza a hora de
chegada do voo de volta na cidade A, ajustado ao fuso horário local de A. Todos os horários estão na forma h:m, onde 0 ≤ h < 24 e 0 ≤ m < 60. Além disso, sabe-se que a duração de cada voo é
inferior a 12 horas e que a diferença entre os fusos horários é sempre um valor inteiro de horas no intervalo [-11, 12].
Saída
A saída consiste em dois valores inteiros indicando a duração do voo em minutos e a diferença de horas entre os fusos horários de B e A. Esses dois valores devem ser escritos em uma única
linha, separados por um espaço em branco.

Exemplo1
Entrada: 8:00 20:00 8:00 16:00
Saída: 600 2

Exemplo2
Entrada: 20:00 16:00 20:00 14:00
Saída: 420 -11

Exemplo3:
Entrada: 15:00 11:00 15:00 21:00
Saída: 60 -5

*/

#include <stdio.h>

int main(void)
{
    int minsaiA, horsaiA, horsaiB, minsaiB, horchegA, minchegA, minchegB, horchegB, duraAB, duraBA, fusomin, fusohor, dureal;
    
    scanf("%d:%d %d:%d %d:%d %d:%d", &horsaiA, &minsaiA, &horchegB, &minchegB, &horsaiB, &minsaiB, &horchegA, &minchegA);
    
    /*passa min*/
    minsaiA=minsaiA+(horsaiA*60);
    minsaiB=minsaiB+(horsaiB*60);
    minchegA=minchegA+(horchegA*60);
    minchegB=minchegB+(horchegB*60);
    
    /*duração*/
    duraAB=minchegB-minsaiA;
    if(duraAB<0)
    {
        duraAB=1440+duraAB;
    }
    duraBA=minchegA-minsaiB;
    if(duraBA<0)
    {
        duraBA=1440+duraBA;
    }
    
    
    /*fuso*/
    if(horsaiA>horchegB && horsaiB>horchegA)
    {
        fusomin=(duraBA-duraAB)/2;
        fusohor=fusomin/60;
        if(fusohor==12)
        {
            fusohor=0;
        }
        if(fusohor<0)
        {
            fusohor=-12+(fusohor*-1);
        }
        dureal=duraAB+(fusohor*60);
    }
    if(horsaiA<=horchegB || horsaiB<=horchegA)
    {  
        fusomin=(duraBA-duraAB)/2;
        fusohor=fusomin/60;
        if(fusohor<0)
        {
            fusohor=fusohor*-1;
        }
        if(fusohor==12)
        {
            fusohor=0;
        }
        dureal=duraAB-(fusohor*60);
    }
    
    /*tela*/
    printf("%d %d", dureal, fusohor);
    
    
    
    return 0;
}