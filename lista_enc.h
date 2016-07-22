#ifndef LISTA_ENC_H_INCLUDED
#define LISTA_ENC_H_INCLUDED

#include "no.h"

typedef struct listas_enc lista_enc_t;

lista_enc_t *cria_lista_enc(void);
void add_cauda(lista_enc_t *lista, no_t* elemento);

void imprimi_lista (lista_enc_t *lista);
void imprimi_lista_tras (lista_enc_t *lista);


no_t *obter_cabeca(lista_enc_t *list);
no_t *obter_cauda(lista_enc_t *list);
int get_size(lista_enc_t *list);
void * get_data_index(lista_enc_t *list, int index);

void swap_list(lista_enc_t *list, no_t *fonte, no_t *destino);

#endif // LISTA_ENC_H_INCLUDED
