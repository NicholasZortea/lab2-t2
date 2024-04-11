#include "fila.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Fila filax = fila_cria(sizeof(int));
    int a,b,c,d,e,f,g,h,i,j;
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
    printa_fila_int(filax);
}
