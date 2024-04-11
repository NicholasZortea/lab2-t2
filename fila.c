#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_MALLOC 10

struct _fila {
  int primeiro;
  int ultimo;
  int n_elem;
  int tam_dado;
  int pos_percurso;
  int cap;
  void *espaco;
};

// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado) {
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL) {
    self->espaco = malloc(MIN_MALLOC * tam_do_dado);
    if (self->espaco != NULL) {
      self->primeiro = 0;
      self->ultimo = 0;
      self->n_elem = 0;
      self->cap = 10;
      self->tam_dado = tam_do_dado;
    } else {
      free(self);
      self = NULL;
    }
  }
  return self;
}

void fila_destroi(Fila self) {
  free(self->espaco);
  free(self);
}

// calcula o valor do ponteiro para o elemento na posição pos da fila
static void *calcula_ponteiro(Fila self, int pos)
{
  // TODO: suporte a pos negativa
  if (pos < 0 || pos >= self->n_elem) return NULL;
  // calcula a posição convertendo para char *, porque dá para somar em
  //   bytes. tem que fazer essa conversão porque não conhecemos o tipo
  //   do dado do usuário, só o tamanho.
  void *ptr = (char *)self->espaco + pos * self->tam_dado;
  return ptr;
}

bool fila_vazia(Fila self) { return self->n_elem == 0; }

//remove da primeira posição
void fila_remove(Fila self, void *pdado) {
  void *ptr = calcula_ponteiro(self, 0);
  assert(ptr != NULL);
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  ptr = calcula_ponteiro(self, 1);
  if (ptr != NULL) {
    // ptr aponta para o segundo elemento da fila
    //   (que vira o primeiro)
    // copia os dados que sobraram para o início do espaço
    //   (não precisaria fazer isso com vetor circular)
    memmove(self->espaco, ptr, self->tam_dado * (self->n_elem - 1));
  }
  self->n_elem--;
}

//insere no final
void fila_insere(Fila self, void *pdado)
{
  if (self->n_elem < self->cap)
  {
    if(self->n_elem != 0) self->ultimo++;
    self->n_elem++;
    void *ptr = calcula_ponteiro(self, self->ultimo);
    memmove(ptr, pdado, self->tam_dado);
  }
}

void fila_inicia_percurso(Fila self, int pos_inicial)
{
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado)
{
  void *ptr = calcula_ponteiro(self, self->pos_percurso);
  if (ptr == NULL) return false;
  memmove(pdado, ptr, self->tam_dado);
  if (self->pos_percurso < 0) {
    self->pos_percurso--;
  } else {
    self->pos_percurso++;
  }
  return true;
}

void printa_fila_int(Fila fila){
  for(int i = 0; i < fila->n_elem; i++){
    int pos;
    if(fila->primeiro+i > fila->cap-1){
      pos = fila->primeiro+i - fila->cap;
    } else {
      pos = fila->primeiro + i;
    }
    int* val = (int*)calcula_ponteiro(fila, pos);
    printf("Valor: %d\n", *(val));

  }
}
