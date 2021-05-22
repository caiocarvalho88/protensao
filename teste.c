#include<stdio.h>
#include<stdlib.h>
#include <conio.h>

int main()
{
   int x;
   float fkn, aco, f, tensao, s, beta, mi, n;

    // Etapa 01 - Definição de grandeza física a ser calculada
    printf("digite a grandeza física a ser utilizada:\n 1- Tensao MPa \n 2-Forca\n (kN)\n");
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
        scanf("%f%f%f",&s,&beta,&mi);
        n = s+1;
        float *comp, *ang, *vetorz;
    
        comp = (float *) malloc(n * sizeof(float));
        ang = (float *) malloc(n * sizeof(float));
        vetorz = (float *) malloc(n * sizeof(float));

        int i;
    
        // Etapa 04 - Definição da situação de pré-tração
        printf(" Escolha como ira calcular a perda por atrito\n Digite:\n 1 - para usar angulos \n 2 - para usar pontos ");
        scanf("%d", &x);
        while(x!=1&x!=2)
        {
            printf("Esta escolha nao existe \n \n Escolha como ira calcular a perda por atrito\n Digite:\n 1 - para usar angulos \n 2 - para usar pontos");
            scanf("%d",&x);
        }
        switch(x)
        {
            case    '1':
                for(i=1;i<n;i++)
                {
                    printf("Digite o comprimento da secao em metros (m):\n");
                    scanf("%f",&comp[i]);
                    printf("Digite o angulo da secaoo em graus (�):\n");
                    scanf("%f",&ang[i]);

                        j=i-1;
                        D[i] = comp[i]+D[j];
                        da[i] = a[i] + da[j];
                        dar[i] = da[i]*pi/180;
                        e[i] = exp(-mi * (dar[i]+b*(D[i])));
                        p[i] = F*e[i];
                        i = i+1;
                }
                printf("a protensao eh feita em ambos os lados?\n digite:\n 1- para SIM\n 2- para NAO");
                scanf("%d",&x);
                while(x!=1&x!=2)
                {
                    printf("Esta escolha nao existe \n \n a protensao eh feita em ambos os lados?\n digite:\n 1- para SIM\n 2- para NAO");
                    scanf("%d",&x);
                    if(x==1)
                    {

                    }
                }
        }
    }//fechamento do if=1
return 0;
}

