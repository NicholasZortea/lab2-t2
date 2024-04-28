#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_MALLOC 10

struct _fila
{
  int primeiro;
  int ultimo;
  int n_elem;
  int tam_dado;
  int pos_percurso;
  int cap;
  void *espaco;
};

int fila_tamanho(Fila self)
{
  return self->n_elem;
}

// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado)
{
  printf("Criando a fila!");
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL)
  {
    printf("Tamanho do dado: %d Tamanho do MIN_Malloc: %d\n", tam_do_dado, MIN_MALLOC);
    self->espaco = malloc(MIN_MALLOC * tam_do_dado);
    if (self->espaco != NULL)
    {
      self->primeiro = 0;
      self->ultimo = 0;
      self->n_elem = 0;
      self->cap = 5;
      self->tam_dado = tam_do_dado;
    }
    else
    {
      free(self);
      self = NULL;
    }
  }
  return self;
}

void fila_destroi(Fila self)
{
  free(self->espaco);
  free(self);
}

// calcula o valor do ponteiro para o elemento na posição pos da fila
static void *calcula_ponteiro(Fila self, int pos, bool converte)
{
  // TODO: suporte a pos negativa
  // printf("pos: %d, self->n_elem: %d \n", pos, self->n_elem);

  if (self->n_elem == 0)
    return NULL;
  if (pos < 0)
  {
    pos = self->n_elem + pos;
  }

  if (converte)
  {
    if (pos >= self->cap)
      return NULL;
    pos += self->primeiro;
    if (pos >= self->cap)
    {
      pos = pos - self->cap;
    }
  }

  if (!ehUmaPosValida(self, pos))
    return NULL;

  // calcula a posição convertendo para char *, porque dá para somar em
  //   bytes. tem que fazer essa conversão porque não conhecemos o tipo
  //   do dado do usuário, só o tamanho.
  void *ptr = (char *)self->espaco + pos * self->tam_dado;
  return ptr;
}

bool ehUmaPosValida(Fila f, int p)
{
  if (f->primeiro == 0 && f->ultimo < p)
    return false;

  if (p < f->primeiro && p > f->ultimo)
    return false;
  if (f->primeiro == f->ultimo && p > f->ultimo)
    return false;

  if ((f->primeiro <= f->ultimo && (p < f->primeiro || p > f->ultimo)) ||
      (f->ultimo < f->primeiro && (p < f->primeiro && p > f->ultimo)))
  {
    return false;
  }

  return true;
}

bool fila_vazia(Fila self) { return self->n_elem == 0; }

// remove da primeira posição
void fila_remove(Fila self, void *pdado)
{
  void *ptr = calcula_ponteiro(self, self->primeiro, false);
  assert(ptr != NULL);
  if (pdado != NULL)
  {
    memmove(pdado, ptr, self->tam_dado);
  }
  self->primeiro++;
  if (self->primeiro >= self->cap)
  {
    self->primeiro = self->cap - self->primeiro;
  }
  self->n_elem--;
}

// insere no final
void fila_insere(Fila self, void *pdado)
{
  if (self->n_elem < self->cap)
  {
    if (self->n_elem != 0)
      self->ultimo++;
    self->n_elem++;
    if (self->ultimo >= self->cap)
    {
      self->ultimo = self->cap - self->ultimo;
    }
    void *ptr = calcula_ponteiro(self, self->ultimo, false);
    memmove(ptr, pdado, self->tam_dado);
  }
  else
  {
    alocaMaisEspaco(self);
    fila_insere(self, pdado);
  }
}

void alocaMaisEspaco(Fila self)
{
  self->espaco = (void *)realloc(self->espaco, (self->tam_dado * (self->cap + MIN_MALLOC)));

  if (self->primeiro != 0) // nenhum elemento foi removido e
  {
    int novoPrimeiro = self->primeiro + MIN_MALLOC;
    int qntsMover = self->cap - self->primeiro;

    int oldPrimeiro = self->primeiro;
    for (int i = 0; i < qntsMover; i++)
    {
      void *dado_a_mover = calcula_ponteiro(self, oldPrimeiro + i, false);
      void *endereco_destino = calcula_ponteiro(self, novoPrimeiro + i, false);
      memmove(endereco_destino, dado_a_mover, self->tam_dado);
    }
    self->primeiro = novoPrimeiro;
  }

  self->cap += MIN_MALLOC;
}

void fila_inicia_percurso(Fila self, int pos_inicial)
{
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado)
{
  // printf("fila_proximo!\n");
  void *ptr = calcula_ponteiro(self, self->pos_percurso, true);
  if (ptr == NULL)
    return false;
  memmove(pdado, ptr, self->tam_dado);
  if (self->pos_percurso < 0)
  {
    self->pos_percurso--;
  }
  else
  {
    self->pos_percurso++;
  }
  return true;
}

void printa_fila_int(Fila fila)
{
  printf("\n");
  for (int i = 0; i < fila->n_elem; i++)
  {
    int pos;
    if (fila->primeiro + i > fila->cap - 1)
    {
      pos = fila->primeiro + i - fila->cap;
    }
    else
    {
      pos = fila->primeiro + i;
    }
    int *val = (int *)calcula_ponteiro(fila, pos, false);
    printf("Valor: %d\n", *(val));
  }
}
