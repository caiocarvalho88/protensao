#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <math.h>
#include <tgmath.h>
//Definições
#define PI 3.141592653589793238463;
/******* Área dos protótipos ******/
void resultado(int n, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p, int cond);
void perdatensao(int n, float f, float mi, float beta, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p);
void verificar_arq(FILE *pont_arq);
void plot(float *a, float *b, float *c, int n, int cond);
void convertepemf(float *p, float aco, int n);
void ancoragem(int n, int lados, int cond, float aco, float *comp, float *p, float *pa, float *D);
/******* fim dos protótipos *******/


/******** FUNÇÃO PRINCIPAL *******/
int main()
{
    int x, s, n, i, ref, cond, lados;
    float fkn, aco, f, tensao, beta, mi;
    float *comp, *ang, *vetore, *D, *da, *dar, *e, *p, *pa;
    float  *compi, *angi, *Di, *dai, *dari, *ei, *pinv;
    char var_arq_aux;
    FILE *pont_arq;
    FILE *arq;
    pont_arq = fopen("entrada.txt", "r");
    verificar_arq(pont_arq);

    // Etapa 01 - Definição de grandeza física a ser calculada
    printf("digite a grandeza fisica a ser utilizada:\n 1- Tensao MPa \n 2-Forca\n (kN)\n");
    scanf("%d",&cond);

    while(cond!=1&cond!=2)
    {
        printf("Esta escolha nao existe \n \n Digite a unidade a ser utilizada: \n 1 - Tensao (MPa) \n 2 - Forca (kN)\n");
        scanf("%d",&cond);
    }
    if(cond==2)
    {
        var_arq_aux = fscanf(pont_arq, "%f %f", &fkn, &aco);
        f = (fkn/aco);
        printf(" Força: %.2f kN\n ", fkn);
        printf(" Área de aço: %.2f cm2\n ", aco);
        printf(" Tensao: %.2f MPa\n", f);
    }
    else
    {
        var_arq_aux = fscanf(pont_arq, "%f", &f);
        n = s+1;
        printf(" Tensao: %.2f MPa\n", f);
    }
   
    

    // Etapa 02 - Definição da situação em que ocorre a perda tração (pré ou pós tração)
    printf("Como sera feita a protensao ? \n Digite: \n 1 - para POS-TRACAO \n 2 - para PRE-TRACAO \n");
    scanf("%d",&x);

     while(x!=1&x!=2){
    printf("Esta escolha nao existe \n \n Digite a unidade a ser utilizada: \n 1 - POS-TRACAO \n 2 - PRE-TRACAO\n");
    scanf("%d",&x);
   }

   // Etapa 03 - Cálculo da situação de pós-tração
    if(x==1)
    {
        var_arq_aux = fscanf(pont_arq, "%f %f %d", &mi, &beta, &s);
        n = s+1;
        printf(" Coef. Perda: %.2f\n Beta: %.2f\n Qtd. Secoes: %d\n", mi, beta, s);
    //vetores de entrada de dados 
        comp = (float *) malloc(n * sizeof(float));     //comprimento da seção analisada
        ang = (float *) malloc(n * sizeof(float));      //ângulo alfa em graus
        vetore = (float *) malloc(n * sizeof(float));   //????
    //vetores auxiliares da esquerda para direita
        D = (float *) malloc(n * sizeof(float));        //comprimento acumulado
        da = (float *) malloc(n * sizeof(float));       //alfa acumulado em graus
        dar = (float *) malloc(n * sizeof(float));      //alfa acumulado em radiano
        e = (float *) malloc(n * sizeof(float));        //fator redutor de tensão por perda de tensão
        p = (float *) malloc(n * sizeof(float));        //tensão resultante após a perda de tensão
        pa = (float *) malloc(n * sizeof(float));        //tensão resultante após a perda de ancoragem
    //vetores auxiliares da esquerda para direita
        Di = (float *) malloc(n * sizeof(float));        //comprimento acumulado
        dai = (float *) malloc(n * sizeof(float));       //alfa acumulado em graus
        dari = (float *) malloc(n * sizeof(float));      //alfa acumulado em radiano
        ei = (float *) malloc(n * sizeof(float));        //fator redutor de tensão por perda de tensão
        pinv = (float *) malloc(n * sizeof(float));        //tensão resultante após a perda de tensão
        compi = (float *) malloc(n * sizeof(float));     //comprimento da seção analisada
        angi = (float *) malloc(n * sizeof(float));      //ângulo alfa em graus
    //inicialização dos vetores de operação
        comp[0]=0;
        ang[0]=0;
        compi[0]=0;
        angi[0]=0;
        vetore[0]=0;
    //Definição da situação de pré-tração
        printf(" Escolha como ira calcular a perda por atrito\n Digite:\n 1 - para usar angulos \n 2 - para usar pontos \n");
        scanf("%d", &x);
        while(x!=1&x!=2)
        {
            printf("Esta escolha nao existe \n \n Escolha como ira calcular a perda por atrito\n Digite:\n 1 - para usar angulos \n 2 - para usar pontos\n");
            scanf("%d",&x);
        }
        
        switch(x)
        {
    // Etapa 03.01 - Cálculo da situação de pré-tração por angulos
            case 1:
                for(i=1;i<n;i++)
                {
                    var_arq_aux = fscanf(pont_arq, "%f",&comp[i]); //vertor de armazenamento dos comprmentos da seção em análise
                    var_arq_aux = fscanf(pont_arq, "%f",&ang[i]); //vertor de armazenamento dos ângulos em grau da seção em análise
                }
                for(i=1;i<n;i++)
                {
                    compi[i]=comp[n-i];
                    angi[i]=ang[n-i];
                }
                printf("Vetor comprimento\n");
                for(i=0;i<n;i++)
                {
                    printf("%.2f \t", comp[i]);
                }
                printf("\n");
                printf("Vetor angulo\n");
                for(i=0;i<n;i++)
                {
                    printf("%.2f \t", ang[i]);
                }  
                printf("\n");
                perdatensao(n, f, mi, beta, comp, D, ang, da, dar, e, p);
                perdatensao(n, f, mi, beta, compi, Di, angi, dai, dari, ei, pinv);
                printf("a protensao eh feita em ambos os lados?\n digite:\n 1- para NAO\n 2- para SIM\n");
                scanf("%d",&lados);
                while(lados!=1&lados!=2)
                {
                    printf("Esta escolha nao existe \n \n a protensao eh feita em ambos os lados?\n digite:\n 1- para NAO\n 2- para SIM\n");
                    scanf("%d",&lados);
                }
                if(lados==2)
                {
                    printf("Resultado da esquerda para a direita\n");
                    resultado(n, comp, D, ang, da, dar, e, p, cond);
                    printf("Resultado da direita para a esquerda\n");
                    resultado(n, compi, Di, angi, dai, dari, ei, pinv, cond);
                }
                else
                {
                    printf("Resultado da esquerda para a direita\n");
                    resultado(n, comp, D, ang, da, dar, e, p, cond);
                    //resultado(n, comp, D, ang, da, dar, e, p, cond);
                }
                break;
    // Etapa 03.02 - Cálculo da situação de pós-tração por pontos
            case 2:
                for(i=1;i<n;i++)
                {
                    var_arq_aux = fscanf(pont_arq, "%f",&comp[i]); //vertor de armazenamento dos comprmentos da seção em análise 
                    var_arq_aux = fscanf(pont_arq, "%f",&vetore[i]); //vertor de armazenamento dos ângulos em grau da seção
                    ang[i] = atan(2*vetore[i]/comp[i]/100)*180/PI;
                }
                for(i=1;i<n;i++)
                {
                    compi[i]=comp[n-i];
                    angi[i]=ang[n-i];
                }
                printf("Vetor comprimento\n");
                for(i=0;i<n;i++)
                {
                    printf("%.2f \t", comp[i]);
                }
                printf("\n");
                printf("Vetor angulo\n");
                for(i=0;i<n;i++)
                {
                    printf("%.2f \t", ang[i]);
                }  
                printf("\n");
                perdatensao(n, f, mi, beta, comp, D, ang, da, dar, e, p);
                perdatensao(n, f, mi, beta, compi, Di, angi, dai, dari, ei, pinv);
                printf("a protensao eh feita em ambos os lados?\n digite:\n 1- para NAO\n 2- para SIM\n");
                scanf("%d",&lados);
                while(lados!=1&lados!=2)
                {
                    printf("Esta escolha nao existe \n \n a protensao eh feita em ambos os lados?\n digite:\n 1- para NAO\n 2- para SIM\n");
                    scanf("%d",&lados);
                }
                if(lados==2)
                {
                    printf("Resultado da esquerda para a direita\n");
                    resultado(n, comp, D, ang, da, dar, e, p, cond);
                    printf("Resultado da direita para a esquerda\n");
                    resultado(n, compi, Di, angi, dai, dari, ei, pinv, cond);
                }
                else
                {
                    printf("Resultado da esquerda para a direita\n");
                    resultado(n, comp, D, ang, da, dar, e, p, cond);
                }
                break;
        }
    }//fechamento do if=1
    //Etapa 04 - Cálculo da situação de pré-tração
    /*else //pré-tração
    {
        printf("número de cabos:");
        printf("número de cabos:");
    }*/
    ancoragem(n, lados, cond, aco, comp, p, pa, D);
    fclose(pont_arq);
    printf("fim\n");
    system("pause");
    return 0;
}
/********* FIM DA FUNÇÃO PRINCIPAL *******/
/*--------- Corpo das funções --------- */
/****** Função resultado *****
Parâmetros de entrada: int n e os floats *comp, *D, *ang, *da, *dar, *e, *p
Objetivo: imprimir a tabela de resultados de perda de protenção na tela
Tipo de retorno: não tem (void)
*/
void resultado(int n, float *comp, float *D, float *ang, float *da, float *dar, float *e, float *p, int cond)
{
    int i;
    if (cond == 1)
    {
        printf("Variacao da tensao ao longo do cabo de protensao considerando atrito\n");
    }
    else
    {
        printf("Variacao da forca ao longo do cabo de protensao considerando atrito\n");
    }
    printf("secao \t comp. \t acum. \t alfa \t acum. \t rad. \t fator \t tens. resul. \n");
    for(i=0;i<n;i++)
    {
        printf("%d \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \n", i, comp[i], D[i], ang[i], da[i], dar[i], e[i], p[i]);
    }
    printf("\n");
  return; /* retorno de uma função void  */
}
/****** Função perdatensao *****
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
/****** Função verificar_arq *****
Parâmetros de entrada: int n e os floats f, mi, beta, *comp, *D, *ang, *da, *dar, *e, *p
Objetivo: calcular a tabela de resultados de perda de protenção
Tipo de retorno: não tem (void)
*/
void verificar_arq(FILE *pont_arq)
{
    if(pont_arq==NULL)
    {
        printf("ERRO! O arquivo não foi aberto!\n");
    }
    else
    {
        printf("O arquivo foi aberto com sucesso!\n");
    }
    return; /* retorno de uma função void  */
}
/****** Função ancoragem *****
Parâmetros de entrada: int n e os floats f, mi, beta, *comp, *D, *ang, *da, *dar, *e, *p
Objetivo: calcular a tabela de resultados de perda de protenção
Tipo de retorno: não tem (void)
*/
void ancoragem(int n, int lados, int cond, float aco, float *comp, float *p, float *pa, float *D)
{
    /* Pré-tracionado*/
    int indesloc=0, z, t = 1, j = 0, k = j+1, i=0;
    float A, B, C, raiz1, raiz2, LO;
    float omegatotal, omega;
    float areamax, Ep=200000, deltaL=6, deltat=0;
    areamax = Ep*deltaL/10;
    //printf("Areamax: %.2f\n", areamax);
    //printf("N: %d\n", n);
    pa[0] = 0;
    omega = 0; //área do gráfico de uma seção calculada
    omegatotal = 0; //área acumulada do gráfico das seções calculadas
    
    //ancoragem para situação pós-tracionado
    i=0;
    //printf("Omegatotal: %f\n", omegatotal);
    while((omegatotal <= areamax) && (i < (n-1))) //encontrar o ponto indeslocável (enquanto )
    {
        omega = (p[i] - p[i+1])*(D[i+1]+D[i])*100; //área do trapézio da seção (ou triângulo quando i=0, pois D(0)=0)
        omegatotal = omega + omegatotal;
        printf("Omegatotal: %f\n", omegatotal);
        i=i+1;
    }
    indesloc = i;
    printf("Ponto indeslocavel: no %d\n", indesloc);
    if(indesloc == (n-1))
    {
        deltat = (areamax-omegatotal)/(D[n-1]*100);
        i=0;
        while(i < n);
        {
        pa[i] = p[i]-(2*(p[i]-p[n-1])+deltat);
        i=i++;
        }
        if(lados == 2) //protensão nos dois lados
        {
            printf ("Não é recomendado usar ancoragem em ambos os lados devido a grande perda por ancoragem \n");
        }
        if ((cond == 2) && (lados == 1)) // (condição em que a unidade é Força e há apenas um lado protendido)
        {
            convertepemf(p, aco, n);
            convertepemf(pa, aco, n);
            plot(D, p, pa, n, cond);
        }
        if ((cond == 1) && (lados == 1)) // (condição em que a unidade é Tensão e há apenas um lado protendido)
        {
            plot(D, p, pa, n, cond);
        }
    }
    if(indesloc < (n-1))
    {
        z = indesloc+1;
        A = comp[z]*100/(4*(p[indesloc]-p[z]));
        B = D[t]*100;
        C = -areamax+omegatotal;
        raiz1 = ((-1)*B + sqrt((B*B-4*A*C)))/(2*A);
        raiz2 = ((-1)*B - sqrt((B*B-4*A*C)))/(2*A);
        if (raiz1 > 0)
        {
            deltat = raiz1;
        }
        if(raiz2 > 0)
        {
            deltat = raiz2;
        }
        LO = 2*A*deltat;
        i=0;
        while (i<=indesloc)
        {
            pa[i] = p[i]-(2*(p[i]-p[indesloc])+deltat);
            i=i+1;
        }
        while ((i>indesloc) && (i < n))
        {   
            pa[i] = p[i];
            i=i+1;
        }
        if (cond == 2) // (condição em que a unidade é Força)
        {
            convertepemf(p, aco, n);
            convertepemf(pa, aco, n);
            plot(D, p, pa, n, cond);
        }
        else
        {
            plot(D, p, pa, n, cond);
        }
    }
    return; /* retorno de uma função void  */
}
/****** Função verificar_arq *****
Parâmetros de entrada: int n e os floats f, mi, beta, *comp, *D, *ang, *da, *dar, *e, *p
Objetivo: calcular a tabela de resultados de perda de protenção
Tipo de retorno: não tem (void)
*/
void plot(float *a, float *b, float *c, int n, int cond)
{
    int i;
    if (cond == 1)
    {
        printf("Variacao da tensao ao longo do cabo de protensao considerando atrito e a perda por ancoragem\n");
    }
    else
    {
        printf("Variacao da forca ao longo do cabo de protensao considerando atrito e a perda por ancoragem\n");
    }
    printf("Desl. \t Atrito \t Ancoragem \n");
    for (i = 0; i < n; i++)
    {
        printf("%.2f \t %.2f \t %.2f \n", a[i], b[i], c[i]);
    }
    printf("\n");
    return; /* retorno de uma função void  */
}
/****** Função convertepemf *****
Parâmetros de entrada: int n e os floats *p, aco
Objetivo: converte o vetor tensão em força
Tipo de retorno: não tem (void)
*/
void convertepemf(float *p, float aco, int n)
{
    int i;
    i = 0;
    while (i < n)
    {
        p[i] = p[i] * aco / 10;
        i = i++;
    }
    return; /* retorno de uma função void  */
}