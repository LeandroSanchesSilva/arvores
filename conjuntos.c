#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>                               // utilizar o clock do pc para gerar os numeros aleatoriamente

# define TAM 10                                 // n�mero de conjuntos a serem gerados          


int main() {
    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));                          // seed para a gera��o dos n�meros aleat�rios;

    int *conjunto, *medias;
    int i, j, igual, valor, tam;

    // Caso M�dio -> CHAVES ALEAT�RIAS

    printf("\n CONJUNTOS DE CHAVES ALEAT�RIAS:\n");

    for( tam = 1; tam <= TAM; tam++ ){           // neste FOR definimos o n�mero de conjuntos a serem criados
        conjunto = malloc(tam * sizeof(int));   // aloca��o de mem�ria para o vetor, conforme o n�mero de elementos

        for( i=0; i<tam; i++ ){
            *(conjunto + i) = rand() % 10;     // aritm�tica de ponteiros

            igual = 0;                         
            for( j = 0; j < i; j++ ){          // este FOR garante que nenhuma chave se repetir�
                if( conjunto[j] == conjunto[i] )
                    igual = 1;
            }

            if (igual == 1)
                i--;            
        }

        printf("\n Conjunto %d: \n", tam);
        for(i = 0; i < tam; i++)
            printf("%d ", *(conjunto + i));     // imprime o conte�do desta regi�o de mem�ria
        printf("\n");

        void free (void *conjunto);             // desalocando a mem�ria
    }

    // Pior Caso -> CHAVES ORDENADAS DECRESCENTEMENTE

    printf("\n CONJUNTOS DE CHAVES ORDENADAS DECRESCENTEMENTE:\n");

    for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o n�mero de conjuntos a serem criados
        conjunto = malloc(tam * sizeof(int));   // aloca��o de mem�ria para o vetor, conforme o n�mero de elementos
        
        valor = tam;
        for( i=0; i<tam; i++ ){
            *(conjunto + i) = valor;            // aritm�tica de ponteiros
            valor--;
                      
        }

        printf("\n Conjunto %d: \n", tam);
        for(i = 0; i < tam; i++)
            printf("%d ", *(conjunto + i));     // imprime o conte�do desta regi�o de mem�ria
        printf("\n");

        void free (void *conjunto);             // desalocando a mem�ria
    }

return 0;
}