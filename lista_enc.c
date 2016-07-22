#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"
#include "task.h"

// #define DEBUG

struct listas_enc {
    no_t *cabeca;
    no_t *cauda;
    int tamanho;
};

//cria uma lista vazia
lista_enc_t *cria_lista_enc (void) {
    lista_enc_t *p = malloc(sizeof(lista_enc_t));

    if (p == NULL){
        perror("cria_lista_enc:");
        exit(EXIT_FAILURE);
    }

    p->cabeca = NULL;
    p->cauda = NULL;
    p->tamanho = 0;

    return p;
}

void add_cauda(lista_enc_t *lista, no_t* elemento)
{
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

   //lista vazia
   if (lista->tamanho == 0)
   {
        #ifdef DEBUG
        printf("add_cauda: add primeiro elemento: %p\n", elemento);
        #endif // DEBUG

        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;

        desliga_no(elemento);
   }
   else {
        // Remove qualquer ligacao antiga
        desliga_no(elemento);
        // Liga cauda da lista com novo elemento
        liga_nos(lista->cauda, elemento);

        lista->cauda = elemento;
        lista->tamanho++;
   }

    #ifdef DEBUG
   printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
   #endif // DEBUG
}

void imprimi_lista (lista_enc_t *lista)
{
    no_t *no = NULL;

    if (lista == NULL){
        fprintf(stderr,"imprimi_lista: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no = lista->cabeca;

    while (no){
        printf("Dados: %p\n", obtem_dado(no));

        no = obtem_proximo(no);
    }
}

void imprimi_lista_tras (lista_enc_t *lista)
{
    no_t *no = NULL;

    if (lista == NULL){
        fprintf(stderr,"imprimi_lista: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no = lista->cauda;

    while (no){
        printf("Dados: %p\n", obtem_dado(no));

        no = obtem_anterior(no);
    }
}

no_t *obter_cabeca(lista_enc_t *list)
{
    if (list == NULL) {
        fprintf(stderr, "get_head: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    return list->cabeca;
}

no_t *obter_cauda(lista_enc_t *list)
{
    if (list == NULL) {
        fprintf(stderr, "get_head: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    return list->cauda;
}

int get_size(lista_enc_t *list)
{
    if (list == NULL) {
        fprintf(stderr, "get_size: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    return list->tamanho;
}

void * get_data_index(lista_enc_t *list, int index)
{
    int i = 0;
    no_t * no;

    if (list == NULL) {
        fprintf(stderr, "get_data_index: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    if (index == 0)
        return obtem_dado(list->cabeca);

    if (index == list->tamanho -1)
        return obtem_dado(list->cauda);

    no = list->cabeca;

    while (no && i <= index){
        no = obtem_proximo(no);
        i++;
    }

    return obtem_dado(obtem_anterior(no));
}



void swap_list(lista_enc_t *list, no_t *fonte, no_t *destino)
{
    if (list == NULL) {
        fprintf(stderr, "swap_list: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    if (list->cabeca == fonte)
        list->cabeca = destino;

    if (list->cauda == destino)
        list->cauda = fonte;


    swap_nos(fonte, destino);

}
