#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <math.h>
#include <tgmath.h>
/******* Área dos protótipos ******/
void resultado(int i, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p);
/******* fim dos protótipos *******/


/******** FUNÇÃO PRINCIPAL *******/
int main()
{
    int x, s, n, i;
    float fkn, aco, f, tensao, beta, mi;
    float *comp, *ang, *vetorz, *D, *da, *dar, *e, *p;
    const double PI  = 3.141592653589793238463;

    // Etapa 01 - Definição de grandeza física a ser calculada
    printf("digite a grandeza fisica a ser utilizada:\n 1- Tensao MPa \n 2-Forca\n (kN)\n");
    scanf("%d",&x);

    while(x!=1&x!=2)
    {
        printf("Esta escolha nao existe \n \n Digite a unidade a ser utilizada: \n 1 - Tensao (MPa) \n 2 - Forca (kN)\n");
        scanf("%d",&x);
    }
    if(x==2)
    {
        printf("Digite o modulo da forca em kN: e a area do aco em centimetros quadrados\n");
        scanf("%f %f",&fkn, &aco);
        //printf("%f %f \n", fkn,aco); pto de controle "pce" 1
        f = (fkn/aco);
        printf(" F = %f kN\n ",f);
    }
    else{
        printf("Digite o valor da tensao de protensao em MPa:\n");
        scanf("%f", &tensao);
        f=tensao;
        //printf(" tensao = %f MPa\n ",tensao);pce2
    }

    // Etapa 02 - Definição da situação em que ocorre a perda tração (pré ou pós tração)
    printf("Como sera feita a protensao ? \n Digite: \n 1 - para PRE-TRACAO \n 2 - para POS-TRACAO \n");
    scanf("%d",&x);

     while(x!=1&x!=2){
    printf("Esta escolha nao existe \n \n Digite a unidade a ser utilizada: \n 1 - Tensao (MPa) \n 2 - Forca (kN)\n");
    scanf("%d",&x);
   }

   // Etapa 03 - Cálculo da situação de pré-tração
    if(x==1)
    {
        printf("entre com quantidade de secoes, valor de Beta, valor de coeficiente de atrito\n");
        scanf("%d%f%f",&s,&beta,&mi);
         printf("%d   %f   %f\n", s, beta, mi);
        n = s+1;
        //vetores de entrada de dados 
        comp = (float *) malloc(n * sizeof(float));     //comprimento da seção analisada
        ang = (float *) malloc(n * sizeof(float));      //ângulo alfa em graus
        vetorz = (float *) malloc(n * sizeof(float));   //????

        //vetores auxiliares
        D = (float *) malloc(n * sizeof(float));        //comprimento acumulado
        da = (float *) malloc(n * sizeof(float));       //alfa acumulado em graus
        dar = (float *) malloc(n * sizeof(float));      //alfa acumulado em radiano
        e = (float *) malloc(n * sizeof(float));        //fator redutor de tensão por perda de tensão
        p = (float *) malloc(n * sizeof(float));        //tensão resultante após a perda de tensão
    
        //inicialização dos vetores de operação
        D[0]=0;
        da[0]=0;
        dar[0]=0;
        e[0]=1;
        p[0]=f;
        comp[0]=0;
        ang[0]=0;
        // Etapa 04 - Definição da situação de pré-tração
        printf(" Escolha como ira calcular a perda por atrito\n Digite:\n 1 - para usar angulos \n 2 - para usar pontos \n");
        scanf("%d", &x);
        while(x!=1&x!=2)
        {
            printf("Esta escolha nao existe \n \n Escolha como ira calcular a perda por atrito\n Digite:\n 1 - para usar angulos \n 2 - para usar pontos\n");
            scanf("%d",&x);
        }

        switch(x)
        {
            case 1:
                for(i=1;i<n;i++)
                {
                    printf("Digite o comprimento da secao %i em metros (m):\n", i);
                    scanf("%f",&comp[i]); //intervalo de análise do 
                    printf("Digite o angulo da secaoo %i em graus (alpha):\n", i);
                    scanf("%f",&ang[i]);

                        D[i] = comp[i]+D[i-1]; //comprimento acumulado
                        da[i] = ang[i] + da[i-1]; //alfa acumulado
                        dar[i] = da[i]*PI/180; //alfa acumulado em radiano
                        e[i] = exp(-mi * (dar[i]+beta*(D[i]))); //fator redutor de tensão por perda de tensão
                        p[i] = f*e[i]; // tensão resultante após a perda de tensão
                }
                resultado(n, comp, D, ang, da, dar, e, p);
                printf("a protensao eh feita em ambos os lados?\n digite:\n 1- para SIM\n 2- para NAO");
                scanf("%d",&x);
                while(x!=1&x!=2)
                {
                    printf("Esta escolha nao existe \n \n a protensao eh feita em ambos os lados?\n digite:\n 1- para SIM\n 2- para NAO\n");
                    scanf("%d",&x);
                }
                if(x==1)
                {

                }
                else
                {
                    
                }
        }
    }//fechamento do if=1
    printf("fim\n");
    return 0;
}
/********* FIM DA FUNÇÃO PRINCIPAL *******/
/*--------- Corpo das funções --------- */
/*
***** Função resultado *****
Parâmetros de entrada: int n e os floats *comp, *D, *ang, *da, *dar, *e, *p
Objetivo: imprimir a tabela de resultados de perda de protenção na tela
Tipo de retorno: não tem (void)
*/
void resultado(int n, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p)
{
    int i;
    printf("secao \t comp. \t acum. \t alfa \t ang. acum. \t fator \t tens. resul. \n");
    for(i=0;i<n;i++)
    {
        printf("%d \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \n", i, comp[i], D[i], ang[i], da[i], dar[i], e[i], p[i]);
    }
  return; /* retorno de uma função void  */
}