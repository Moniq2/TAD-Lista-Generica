#ifndef __LISTA_GEN__
#define __LISTA_GEN__
#include<stdlib.h>
#include<stdio.h>
typedef struct listagen ListaGen;
typedef struct ponto Ponto;

void lstgen_percorre(ListaGen* l, void (*processa)(void*));

ListaGen* lstgen_insere(ListaGen* l, void* info);

ListaGen* lstgen_cria();

int lstgen_vazia(ListaGen* l);

void* lstgen_busca(ListaGen* l, int (*compara)(void*, void*), void* dado);

ListaGen* lstgen_retira(ListaGen* l,  int (*compara)(void*, void*), void* dado);

ListaGen* lstgen_duplica(ListaGen* l, void* (*duplica)(void*));

void lstgen_libera(ListaGen* l);

ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*));

#include"lista_gen.c"
#endif