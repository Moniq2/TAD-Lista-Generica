#include<stdio.h>
#include<stdlib.h>
#include"Lista_gen.h"

struct cliente {
    int id;
    char nome[81];
    char telefone[11];
};
typedef struct cliente Cliente;

void* cliente_duplica(void* v);

Cliente* cliente_cria(int id);

void cliente_imprime(void* v);


int main()
{
    ListaGen* clientes = lstgen_cria_vazia();
    for (int i = 0; i < 5; i++)
    {
        Cliente* c = cliente_cria(i);
        clientes = lstgen_insere(clientes, c);
    }
    lstgen_percorre(clientes, cliente_imprime);
    return 0;
}

Cliente* cliente_cria(int id)
{
    Cliente* n = (Cliente*)malloc(sizeof(Cliente));
    if(n ==  NULL) exit(1);
    n->id = id;

    printf("Digite o nome:\n");
    scanf("%s", &n->nome);
    printf("Digite o telefone:\n");
    scanf("%s", &n->telefone);

    return n;
}

void cliente_imprime(void* v)
{
    Cliente* c = (Cliente*)v;
    printf("\n\nID: %d \n\nNome: %s \n\nTelefone: %s\n\n", c->id, c->nome, c->telefone);
}

void* cliente_duplica(void* v){
    Cliente* copia = (Cliente*)malloc(sizeof(Cliente));
    *copia = *(Cliente*)v;

    return copia;
}