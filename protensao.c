#include<stdio.h>
#include<stdlib.h>
int main(){
    int x,i;
    float s,beta,mi,n;

    printf("entre com a unidade a ser utilizada:\n 1- tensao(MPa) ou 2- forca(kN)\n");
    scanf("%d",&x);
    if(x!=1&x!=2){
        printf("esta escolha nao existe\n digite unidade a ser utilizada:\n 1- tensao(MPa) ou 2- forca(kN)\n");
        scanf("%d",&x); }

    printf("informe se a viga sera:\n 1- pre-tracionada ou 2- pos-tracionada\n");
    scanf("%d",&x);
    if(x!=1&x!=2){
        printf("esta escolha nao existe\n nforme se a viga sera:\n 1- pre-tracionada ou 2- pos-tracionada\n");
        scanf("%d",&x);}
   /* switch(x){

        case '2':

            printf("o programa ira calcular a perda imediata devido ao atrito\n");
            printf("entre com o nr de secoes\n o valor de beta\n valor de mi\n");
            scanf("%f%f%f", &s,&beta,&mi);
            printf("escolha se a perda imediata devido ao atrito sera calculado por:\n 1-angulos ou 2- pontos\n");
            scanf("%d",&x);
            if(x!=1&x!=2){
                printf("esta escolha nao existe\n escolha se a perda imediata devido ao atrito sera calculado por:\n 1-angulos ou 2- pontos\n");
                scanf("%d",&x);}
            if(x==1){
               n=s+1;
               float comp[n];
               comp[0]=0;
               for(i=1;i<n;i++){
                    printf("entre com o comprimento das secoes(m)\n");
                    scanf("%f",&comp[i]);
                    printf("entre com os valores dos angulos de cada uma das secoes em angulos\n");
                    scanf("%f",&ang[i]);


               }

            }

    }

     */

return 0;
            }


