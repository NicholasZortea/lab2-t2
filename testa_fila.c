#include "fila.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void imprime_int(void *dado) // imprime inteiros
{
    int *i = (int *)dado;
    //printf("%d\n", *i);
}

void insere(Fila f, int v[], int qntd)
{
    for (int i = 0; i < qntd; i++)
    {
        fila_insere(f, &v[i]);
    }
}

void test_fila_insere()
{
    printf("Teste fila insere: \n\n");
    Fila f = fila_cria(sizeof(int));
    int v[] = {1, 2, 3, 4, 5};
    insere(f, v, 5);
    fila_imprime(f, imprime_int);
    fila_destroi(f);
}

void test_fila_percurso()
{
    printf("Teste fila percurso: \n\n");
    Fila f = fila_cria(4);
    int v[] = {5,2};
    insere(f, v, 2);
    fila_inicia_percurso(f, 1);
    int valor;
    while (fila_proximo(f, &valor, imprime_int))
    {
        printf("Valor: %d\n", valor);
    }
    fila_destroi(f);
}

int main()
{
    test_fila_insere();
    test_fila_percurso();
    return 0;
}
