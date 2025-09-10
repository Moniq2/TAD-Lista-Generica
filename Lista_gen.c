#include"Lista_gen.h"
struct listagen {
    void* info;
    ListaGen* prox;
};

void lstgen_percorre(ListaGen* l, void (*processa)(void*))
{
    ListaGen* p;
    for (p = l; p != NULL; p = p->prox) 
        processa(p->info);    
}

ListaGen* lstgen_insere(ListaGen* l, void* v)
{
    ListaGen* nova = (ListaGen*)malloc(sizeof(ListaGen));
    nova->info = v;
    nova->prox = l;
    return nova;
}

ListaGen* lstgen_cria_vazia(){
    ListaGen* l = NULL;
    return l;
}

int lstgen_vazia(ListaGen* l){
    return (l == NULL);
}

void* lstgen_busca(ListaGen* l, int (*compara)(void*, void*), void* dado){
    if (lstgen_vazia(l)) return NULL;

    ListaGen* p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (compara(p->info, dado))
            return p->info;
    }
    return NULL;
}

ListaGen* lstgen_retira(ListaGen* l,  int (*compara)(void*, void*), void* dado){
    if (lstgen_vazia(l)) exit(2);

    ListaGen* p = l;
    ListaGen* ant = NULL;

    while (p->prox != NULL && !compara(p->info, dado))
    {
        ant = p;
        p = p->prox;
    }
    if (p == NULL)
        return l;
    
    if (ant == NULL)
        l = p->prox;
    else
        ant->prox = p->prox;
    
    free(p);
    return l;
}


ListaGen* lst_cria_no(void* info)
{
    ListaGen* nova = (ListaGen*)malloc(sizeof(ListaGen));
    if(!nova) exit(1);
    nova->info = info;
    nova->prox = NULL;

    return nova;
}


ListaGen* lstgen_duplica(ListaGen* l, void* (*duplica)(void*))
{
    if (l == NULL) return NULL;
    ListaGen* nova = lstgen_cria_vazia();
    ListaGen* p = l;

    while (p != NULL)
    nova = lstgen_insere(nova, duplica(l->info));
    
    return nova;
}

void lstgen_libera(ListaGen* l)
{
    ListaGen* p = l;
    while (p != NULL)
    {
        ListaGen* next = p->prox;
        free(p->info);
        free(p);
        p = next;
    }  
}

/*
*   FILTRA ELEMENTOS DE UMA LISTA
*       Retorna uma lista contendo apenas os elementos filtrados pelo critério.
*       Esta função não copia as informações.
*       Retorna o ponteiro para uma lista contendo a referência aos elementos da lista original.
*/
ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*)){
    ListaGen* nova_lista = lstgen_cria_vazia();
    ListaGen* p = l;

    while(p != NULL){
        if(criterio(p->info))
            nova_lista = lstgen_insere(nova_lista, p->info);
        p = p->prox;
    }

    return nova_lista;
}