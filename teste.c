#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <math.h>
#include <tgmath.h>
//Definições
#define PI 3.141592653589793238463;
/******* Área dos protótipos ******/
void resultado(int n, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p);
void perdatensao(int n, float f, float mi, float beta, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p);
/******* fim dos protótipos *******/


/******** FUNÇÃO PRINCIPAL *******/
int main()
{
    int x, s, n, i;
    float fkn, aco, f, tensao, beta, mi;
    float *comp, *ang, *vetorz, *D, *da, *dar, *e, *p;
    float  *compi, *angi, *Di, *dai, *dari, *ei, *pinv;


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

        //vetores auxiliares da esquerda para direita
        D = (float *) malloc(n * sizeof(float));        //comprimento acumulado
        da = (float *) malloc(n * sizeof(float));       //alfa acumulado em graus
        dar = (float *) malloc(n * sizeof(float));      //alfa acumulado em radiano
        e = (float *) malloc(n * sizeof(float));        //fator redutor de tensão por perda de tensão
        p = (float *) malloc(n * sizeof(float));        //tensão resultante após a perda de tensão

        //vetores auxiliares da esquerda para direita
        Di = (float *) malloc(n * sizeof(float));        //comprimento acumulado
        dai = (float *) malloc(n * sizeof(float));       //alfa acumulado em graus
        dari = (float *) malloc(n * sizeof(float));      //alfa acumulado em radiano
        ei = (float *) malloc(n * sizeof(float));        //fator redutor de tensão por perda de tensão
        pinv = (float *) malloc(n * sizeof(float));        //tensão resultante após a perda de tensão
        compi = (float *) malloc(n * sizeof(float));     //comprimento da seção analisada
        angi = (float *) malloc(n * sizeof(float));      //ângulo alfa em graus
        
        //inicialização dos vetores de operação
        D[0]=0;
        da[0]=0;
        dar[0]=0;
        e[0]=1;
        p[0]=f;
        comp[0]=0;
        ang[0]=0;

        Di[0]=0;
        dai[0]=0;
        dari[0]=0;
        ei[0]=1;
        pinv[0]=f;
        compi[0]=0;
        angi[0]=0;

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
            // Etapa 05 - Cálculo da situação de pré-tração por angulos
            case 1:
                for(i=1;i<n;i++)
                {
                    printf("Digite o comprimento da secao %i em metros (m):\n", i);
                    scanf("%f",&comp[i]); //intervalo de análise do 
                    printf("Digite o angulo da secaoo %i em graus (alpha):\n", i);
                    scanf("%f",&ang[i]);
                }
                for(i=1;i<n;i++)
                {
                    compi[i]=comp[n-i];
                    angi[i]=ang[n-i];
                }
                for(i=0;i<n;i++)
                {
                    printf("%.2f \t", comp[i]);
                }
                printf("\n");
                for(i=0;i<n;i++)
                {
                    printf("%.2f \t", compi[i]);
                }
                printf("\n");
                perdatensao(n, f, mi, beta, comp, D, ang, da, dar, e, p);
                printf("Resultado da esquerda para a direita\n");
                resultado(n, comp, D, ang, da, dar, e, p);
                printf("a protensao eh feita em ambos os lados?\n digite:\n 1- para SIM\n 2- para NAO\n");
                scanf("%d",&x);
                while(x!=1&x!=2)
                {
                    printf("Esta escolha nao existe \n \n a protensao eh feita em ambos os lados?\n digite:\n 1- para SIM\n 2- para NAO\n");
                    scanf("%d",&x);
                }
                if(x==1)
                {
                    perdatensao(n, f, mi, beta, compi, Di, angi, dai, dari, ei, pinv);
                    /*for(i=1;i<n;i++)
                    {
                        compi[i]=comp[n-i];
                        angi[i]=ang[n-i];
                        Di[i] = compi[i]+Di[i-1]; //comprimento acumulado
                        dai[i] = angi[i] + dai[i-1]; //alfa acumulado
                        dari[i] = dai[i]/180*PI; //alfa acumulado em radiano
                        ei[i] = exp(-mi * (dari[i]+beta*(Di[i]))); //fator redutor de tensão por perda de tensão
                        pinv[i] = f*ei[i]; // tensão resultante após a perda de tensão
                    }*/
                    printf("Resultado da esquerda para a direita\n");
                    resultado(n, comp, D, ang, da, dar, e, p);
                    printf("Resultado da direita para a esquerda\n");
                    resultado(n, compi, Di, angi, dai, dari, ei, pinv);
                }
                else
                {
                    printf("Resultado da esquerda para a direita\n");
                    resultado(n, comp, D, ang, da, dar, e, p);
                }
            // Etapa 06 - Cálculo da situação de pré-tração por pontos
            //case 2:
        }
    }//fechamento do if=1
    printf("fim\n");
    system("pause");
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
    printf("secao \t comp. \t acum. \t alfa \t ang. \t acum. \t fator \t tens. resul. \n");
    for(i=0;i<n;i++)
    {
        printf("%d \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \n", i, comp[i], D[i], ang[i], da[i], dar[i], e[i], p[i]);
    }
    printf("\n");
  return; /* retorno de uma função void  */
}
/*
***** Função resultado *****
Parâmetros de entrada: int n e os floats f, mi, beta, *comp, *D, *ang, *da, *dar, *e, *p
Objetivo: calcular a tabela de resultados de perda de protenção
Tipo de retorno: não tem (void)
*/
void perdatensao(int n, float f, float mi, float beta, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p)
{
    int i;
    D[0]=0;
    da[0]=0;
    dar[0]=0;
    e[0]=1;
    p[0]=f;
    comp[0]=0;
    ang[0]=0;
    for(i=1;i<n;i++)
    {
        D[i] = comp[i]+D[i-1]; //comprimento acumulado
        da[i] = ang[i] + da[i-1]; //alfa acumulado
        dar[i] = da[i]/180*PI; //alfa acumulado em radiano
        e[i] = exp(-mi * (dar[i]+beta*(D[i]))); //fator redutor de tensão por perda de tensão
        p[i] = f*e[i]; // tensão resultante após a perda de tensão
    }
  return; /* retorno de uma função void  */
}