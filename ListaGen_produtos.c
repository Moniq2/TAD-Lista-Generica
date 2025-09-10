#include <stdio.h>
#include <string.h>
#include "TAD_LISTA_GEN/Lista_gen.h"

struct produto {
    int pk;
    char* nome;
    float preco;
};
typedef struct produto Produto;

struct item {
    Produto* p;
    int quant;
};
typedef struct item Item;

void* prod_cria(int pk);

void prod_imprime(void* p);

void item_imprime(void* p);

int prod_criterio(void* v);

int prod_compara(void* prod, void* id);

int item_compara(void* item1, void* item2); 

Item* item_cria(ListaGen* shop);

ListaGen* carrinho_preenche(ListaGen* shop);

float carrinho_total(ListaGen* car);


int main() {
    
    ListaGen* shop = lstgen_cria_vazia();
    ListaGen* carrinho = lstgen_cria_vazia();
    ListaGen* tres_reais = lstgen_cria_vazia();

    for (int i = 3; i >= 1; i--)
    {
        Produto* p = (Produto*)prod_cria(i);
        shop = lstgen_insere(shop, p);
    }

    //Mostra os itens do shop.
    printf("\n--------------------\nOla, bem vindo ao Shop! \nEssas sao as opcoes de produtos e seus valores.\n\n");
    lstgen_percorre(shop, prod_imprime);

    //Filtra e mostra os itens que custam menos de 4 reais
    printf("\n\nOs itens do shop que custam menos de 4 reais sao: \n");
    tres_reais = lstgen_filtra(shop, prod_criterio);
    lstgen_percorre(tres_reais, prod_imprime);

    //Cria carrinho e mostra os itens na tela.
    carrinho = carrinho_preenche(shop);
    printf("\nCARRINHO:\n");
    lstgen_percorre(carrinho, item_imprime);
    
    printf("\nO valor total dos produtos do carrinho é: %.2f", carrinho_total(carrinho));
    return 0;
}

//Cria e preenche uma estrutura do tipo Produto.
void* prod_cria(int pk)
{
    Produto* novo = (Produto*)malloc(sizeof(Produto));
    if(!novo) exit(1);
    
    //Define a chave primaria do novo produto como a recebida como parâmetro na função 
    novo->pk = pk;

    //Cria uma char pra guardar os dados recebidos pelo usuário temporariamente, para poder alocar a quantidade certa de memória para o ponteiro
    char aux[21];

    printf("Digite o nome do produto:\n");
    scanf("%20s", aux);
    printf("Digite o preço do produto:\n");
    scanf("%f", &novo->preco);

    //Aloca a  quantidade certa de memória
    novo->nome = (char*)malloc(sizeof(char)* (strlen(aux) + 1));
    strcpy(novo->nome, aux);

    return novo;
}

//Imprime os dados de uma estrutura do tipo Produto.
void prod_imprime(void* p)
{
    Produto* a = (Produto*)p;
    printf("Produto %d\nNome: %s\nPreco: %.2f\n-------------------------------\n", a->pk, a->nome, a->preco);
}

//Imprime os dados de uma estrutura do tipo Item
void item_imprime(void* p)
{
    Item* a = (Item*)p;
    printf("\n\nProduto: %s\nQuantidade:%d\n-------------------------------\n", a->p->nome, a->quant);
}

//Critério para utilização na função lst_filtra para estruturas do tipo produto.
int prod_criterio(void* v)
{
    Produto* p = (Produto*)v;
    return (p->preco < 4);
}

//Função para comparar a chave primária de uma estrutura Produto e um inteiro.
int prod_compara(void* prod, void* id)
{
    Produto* p = (Produto*)prod;
    int i = *(int*)id;

    return (p->pk == i);
}

//Função para comparar as chaves primárias de duas estruturas do tipo produto, recebendo o ponteiro para as estruturas do tipo Item onde estão armazenadas.
int item_compara(void* item1, void* item2)
{
    Item* i = (Item*)item1;
    Item* j = (Item*)item2;

    return (i->p->pk == j->p->pk);
}

//Função para criar e preencher uma estrutura do tipo Item.
Item* item_cria(ListaGen* shop)
{

    // Aloca espaço para o ítem, dinamicamente. 
    Item* novo = (Item*)malloc(sizeof(Item));
    //Verifica se a alocação funcionou, se não, encerra o programa.
    if(!novo) exit(1);

    //Recebe o ID do produto e armazena na variavel 'id'.
    printf("Digite o ID do produto:\n"); 
    int id;
    scanf("%d", &id);

    //Utiliza a função de busca para verificar se existe algum produto com o ID recebido.
    novo->p = lstgen_busca(shop, prod_compara, &id);

    //Se não tiver nenhum produto com esse ID retorna NULL.
    if (novo->p == NULL)
    {
        printf("Nao existe um produto com esse ID!\nTente novamente. ");
        return NULL;
    }
    //Se houver, recebe a quantidade e retorna o endereço do Item.
    printf("Digite a quantidade do produto:\n");
    scanf("%d", &novo->quant);

    return novo;
}

//Lista para criar e preencher uma lista genérica com estruturas Item.
ListaGen* carrinho_preenche (ListaGen* shop){
    ListaGen* novo_carrinho = lstgen_cria_vazia();
    char c;

    //Pergunta se o usuário deseja adicionar itens no carrinho.
    printf("Deseja adicionar itens no carrinho?(S/N)\n");
    scanf(" %c", &c);

    //Loop para adicionar itens no carrinho enquanto o usuário confirmar.
    while ((c != 'N' && c != 'n' && c == 's') || c == 'S') 
    {
        Item* n = item_cria(shop);
        //Se n é NULL, significa que não foi possível criar o Item, então a função para aqui e é repetida novamente.
        if (n == NULL) continue;
    
        //Verifica se o item não já foi adicionado ao carrinho.
        if(lstgen_busca(novo_carrinho, item_compara, n))
            printf("Esse item ja existe no carrinho!!");  
        else
            novo_carrinho = lstgen_insere(novo_carrinho, n);

        printf("\nDeseja adicionar outro item no carrinho? (S/N)\n\n");
        scanf(" %c", &c);
    }
    return novo_carrinho;
}

//Função para calcular o valor total dos itens de um carrinho
float carrinho_total(ListaGen* car){
    float total = 0;
    for (ListaGen* p = car; p != NULL; p = p->prox)
    {
        Item* i = (Item*)p->info;
        total += (i->p->preco) * i->quant;
    }
    return total;
}