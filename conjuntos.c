#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>                               // utilizar o clock do pc para gerar os numeros aleatoriamente

# define TAM 10                                 // número de conjuntos a serem gerados          


int main() {
    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));                          // seed para a geração dos números aleatórios;

    int *conjunto, *medias;
    int i, j, igual, valor, tam;

    // Caso Médio -> CHAVES ALEATÓRIAS

    printf("\n CONJUNTOS DE CHAVES ALEATÓRIAS:\n");

    for( tam = 1; tam <= TAM; tam++ ){           // neste FOR definimos o número de conjuntos a serem criados
        conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos

        for( i=0; i<tam; i++ ){
            *(conjunto + i) = rand() % 10;     // aritmética de ponteiros

            igual = 0;                         
            for( j = 0; j < i; j++ ){          // este FOR garante que nenhuma chave se repetirá
                if( conjunto[j] == conjunto[i] )
                    igual = 1;
            }

            if (igual == 1)
                i--;            
        }

        printf("\n Conjunto %d: \n", tam);
        for(i = 0; i < tam; i++)
            printf("%d ", *(conjunto + i));     // imprime o conteúdo desta região de memória
        printf("\n");

        void free (void *conjunto);             // desalocando a memória
    }

    // Pior Caso -> CHAVES ORDENADAS DECRESCENTEMENTE

    printf("\n CONJUNTOS DE CHAVES ORDENADAS DECRESCENTEMENTE:\n");

    for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
        conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos
        
        valor = tam;
        for( i=0; i<tam; i++ ){
            *(conjunto + i) = valor;            // aritmética de ponteiros
            valor--;
                      
        }

        printf("\n Conjunto %d: \n", tam);
        for(i = 0; i < tam; i++)
            printf("%d ", *(conjunto + i));     // imprime o conteúdo desta região de memória
        printf("\n");

        void free (void *conjunto);             // desalocando a memória
    }

return 0;
}