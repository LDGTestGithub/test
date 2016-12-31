#include <stdio.h>
#include <stdlib.h>
#define TAM 7

int main()
{
    int vetor[TAM], x = 0, y = 0, aux = 0;

    /* Coloca em ordem crescente */
    for (x = 0; x < TAM; x++) {
        for (y = x+1; y < TAM; y++) { /* Sempre 1 elemento a frente */
            if (vetor[x] > vetor[y]) {
                aux = vetor[x];
                vetor[x] = vetor[y];
                vetor[y] = aux;
            }
        }
    }
    /* Fim da ordenação */
}
