/*
 * Trabalho M3-1 - QuickSort recursivo + leitura de arquivo
 *
 * Compilar: gcc -o trabalho trabalho_simples.c
 * Executar: ./trabalho
 * (o arquivo numeros.txt precisa estar na mesma pasta)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Troca o valor de duas variaveis */
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Escolhe o ultimo elemento como pivo, coloca os menores
   a esquerda e os maiores a direita. Devolve a posicao final do pivo. */
int particiona(int v[], int inicio, int fim) {
    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j] <= pivo) {
            i++;
            troca(&v[i], &v[j]);
        }
    }
    troca(&v[i + 1], &v[fim]);
    return i + 1;
}

/* QuickSort recursivo */
void quicksort(int v[], int inicio, int fim) {
    if (inicio < fim) {                      
        int p = particiona(v, inicio, fim);
        quicksort(v, inicio, p - 1);         /* ordena a parte da esquerda */
        quicksort(v, p + 1, fim);            /* ordena a parte da direita  */
    }
}

/* Mostra o vetor na tela */
void imprimir(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    printf("=== PARTE 1: numeros aleatorios ===\n");

    int n = 20;
    int *vetor = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 100 + 1;
    }

    printf("Antes:  ");
    imprimir(vetor, n);

    quicksort(vetor, 0, n - 1);

    printf("Depois: ");
    imprimir(vetor, n);

    free(vetor);

    printf("\n=== PARTE 2: numeros do arquivo ===\n");

    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir numeros.txt\n");
        return 1;
    }

    /* 1o passo: contar quantos numeros tem no arquivo */
    int quantidade = 0;
    int numero;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        quantidade++;
    }

    /* 2o passo: voltar ao inicio do arquivo e guardar os numeros */
    rewind(arquivo);
    int *vetor2 = (int *) malloc(quantidade * sizeof(int));

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%d", &vetor2[i]);
    }
    fclose(arquivo);

    printf("Antes:  ");
    imprimir(vetor2, quantidade);

    quicksort(vetor2, 0, quantidade - 1);

    printf("Depois: ");
    imprimir(vetor2, quantidade);

    free(vetor2);

    return 0;
}