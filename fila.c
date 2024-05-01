#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo nodo;

struct nodo
{
  void *dado;
  nodo *prox;
};

struct _fila
{
  int tam_dado;
  nodo *primeiro;
  nodo *ultimo;
  nodo *percurso;
};

nodo *aloca_nodo(Fila f, void *pdado);
// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado)
{
  Fila f = (Fila)malloc(sizeof(struct _fila));
  if (f == NULL)
  {
    printf("Erro ao alocar memoria para descritor!\n");
    exit(1);
  }
  f->tam_dado = tam_do_dado;
  f->primeiro = NULL;
  f->ultimo = NULL;
  f->percurso = NULL;
  return f;
}

void fila_destroi(Fila self)
{
  if (self != NULL && self->primeiro != NULL)
  {
    nodo *atual = self->primeiro;
    while (atual != NULL) // enquanto for diferente de NULL continua liberando
    {
      nodo *prox = atual->prox;
      free(atual);
      atual = prox;
    }
    free(self);
  }
}

// calcula o valor do ponteiro para o elemento na posição pos da fila
//   retorna NULL se não existir elemento nessa posição da fila
// static void *calcula_ponteiro(Fila self, int pos)
// {
//   // TODO: suporte a pos negativa

//   // se a posição fornecida não estiver dentro da fila, retorna NULL
//   // if (pos < 0 || pos >= self->n_elem) return NULL;

//   // não conhecemos o tipo do dado do usuário, só o tamanho em bytes.
//   // temos um ponteiro para void apontando para o início do vetor.
//   // o dado desejado está tantos bytes além do início do vetor.
//   // para calcular a posição do dado, temos que converter o ponteiro void
//   //   para um ponteiro para dados do tamanho de um byte (char).
//   // a posição do dado no vetor é a mesma posição do dado no vetor (isso não
//   //   será mais válido com vetor circular).
//   int deslocamento_em_bytes = pos * self->tam_dado;
//   //char *ptr_em_bytes_para_o_inicio = (char *)(self->espaco);
//   char *ptr_em_bytes_para_o_dado = ptr_em_bytes_para_o_inicio + deslocamento_em_bytes;
//   void *ptr = (void *)ptr_em_bytes_para_o_dado;
//   return ptr;
// }

bool fila_vazia(Fila self)
{
  return self->primeiro == NULL;
}

// remove do inicio
void fila_remove(Fila self, void *pdado)
{
  if (!fila_vazia(self)) // garante que a fila nao esta vazia antes de remover o nodo
  {
    
    nodo *primeiro = self->primeiro;
    if(pdado!=NULL)
    {
      pdado = primeiro->dado;
    }
    nodo *prox = primeiro->prox;
    free(primeiro);
    self->primeiro = prox;
  } else {
    printf("Fila vazia nao eh possivel remover!\n");
  }
}

// insere no final
void fila_insere(Fila self, void *pdado)
{
  nodo *novo_nodo = aloca_nodo(self, pdado);

  if (fila_vazia(self))
  { // se for o primeiro dado, deve ser o ultimo e o primeiro da fila
    self->primeiro = novo_nodo;
    novo_nodo->prox = NULL;
    self->ultimo = novo_nodo;
  }
  else
  {
    self->ultimo->prox = novo_nodo;
    self->ultimo = novo_nodo;
  }
}

nodo *aloca_nodo(Fila f, void *pdado)
{
  nodo *novo_nodo = (nodo *)malloc(sizeof(nodo));
  if (novo_nodo == NULL)
  {
    printf("Erro ao alocar novo nodo!\n");
    exit(1);
  }
  novo_nodo->prox = NULL;
  novo_nodo->dado = pdado;
  return novo_nodo;
}

void fila_imprime(Fila f, void (*cb)(void *))
{
  if (!fila_vazia(f))
  {
    nodo *atual = f->primeiro;
    while (atual != NULL)
    {
      cb(atual->dado);
      atual = atual->prox;
    }
  }
}

void fila_inicia_percurso(Fila self, int pos_inicial)
{
  if (pos_inicial < 0) {
    fprintf(stderr, "Sem suporte a percurso invertido na fila.\n");
    self->percurso = self->ultimo;
    return;
  }
  
  nodo* atual = self->primeiro;//0
  for(int i = 0; i < pos_inicial; i++)
  {
    atual = atual->prox;
  }
  self->percurso=atual;
}

bool fila_proximo(Fila self, void *pdado)
{
  if (self->percurso==NULL)
    return false;
  // copia o dado para o ponteiro do usuário
  if (pdado != NULL)
  {
    memmove(pdado, self->percurso->dado, self->tam_dado);
  }

  self->percurso = self->percurso->prox;

  return true;
}
