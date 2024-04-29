#include "fila.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testa_percurso()
{
    Fila filax = fila_cria(sizeof(int));
    fila_inicia_percurso(filax, 0);
    int x;
    int i = 1;
    for (int j = 0; j < 5; j++)
    {
        fila_insere(filax, &i);
    }
    printf("Tamanho da fila: %d", fila_tamanho(filax));
    while (fila_proximo(filax, &x))
    {
        printf("Teste percurso\n");
    }
    fila_destroi(filax);
}
void testa_percurso2()
{
    Fila filax = fila_cria(sizeof(int));
    fila_inicia_percurso(filax, 0);
    int x;
    int i = 1;
    for (int j = 0; j < 5; j++)
    {
        fila_insere(filax, &i);
    }
    fila_remove(filax, &x);
    fila_insere(filax, &x);
    printf("Tamanho da fila: %d", fila_tamanho(filax));
    while (fila_proximo(filax, &x))
    {
        printf("Teste percurso\n");
    }
    fila_destroi(filax);
}

void testa_inserindo_removendo()
{
    Fila filax = fila_cria(sizeof(int));
    printf("Teste inserindo 10 elementos de 1 a 10!");
    int a, b, c, d, e, f, g, h, i, j;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    e = 5;
    f = 6;
    g = 7;
    h = 8;
    i = 9;
    j = 10;
    fila_insere(filax, &a);
    fila_insere(filax, &b);
    fila_insere(filax, &c);
    fila_insere(filax, &d);
    fila_insere(filax, &e);
    fila_insere(filax, &f);
    fila_insere(filax, &g);
    fila_insere(filax, &h);
    fila_insere(filax, &i);
    fila_insere(filax, &j);

    fila_remove(filax, NULL);
    fila_remove(filax, NULL);
    fila_remove(filax, NULL);
    fila_remove(filax, NULL);
    fila_remove(filax, NULL);

    fila_insere(filax, &d);
    fila_insere(filax, &e);
    fila_insere(filax, &f);
    fila_insere(filax, &g);
    fila_insere(filax, &h);
    fila_insere(filax, &i);
    fila_insere(filax, &j);
    fila_destroi(filax);
}

void teste_insere_cem(){
    Fila fila = fila_cria(sizeof(int));
    int x = 2;
    for(int i = 0; i < 100; i++){
        fila_insere(fila, &x);
    }
    fila_destroi(fila);
}

void teste_remove_otimizado(){
    Fila f = fila_cria(sizeof(int));
    for(int i = 0; i < 10; i++){
        fila_insere(f, &i);
    }
    printf("Tamanho cap: %d", fila_cap(f));
    for(int i = 0; i < 10; i++){
        fila_insere(f, &i);
    }
    printf("Tamanho cap: %d", fila_cap(f));
    for(int i = 0; i < 15; i++){
        fila_remove(f, NULL);
    }
    printf("Tamanho cap: %d", fila_cap(f));
    printa_fila_int(f);
    fila_destroi(f);
}

int main()
{
    testa_inserindo_removendo();
    teste_insere_cem();
    testa_percurso();
    testa_percurso2();
    teste_remove_otimizado();
}
