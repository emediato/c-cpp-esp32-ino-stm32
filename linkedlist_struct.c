/*

auto reference structure

pointer to the next structure

*/
#include <stdio.h>

struct lista {
 int info;
 struct lista* prox;
};


/*  O tipo Lista representa um nó da lista e a estrutura de lista encadeada
   é representada pelo ponteiro para seu primeiro elemento (tipo Lista*). */

typedef struct lista Lista;


/* função de inicialização: retorna uma lista vazia */
Lista* inicializa (void)
{
 return NULL;
}

/* inserção no início: retorna a lista atualizada 
o aloca dinamicamente o espaço para armazenar o novo nó da lista
*/
Lista* insere (Lista* l, int i)
{
 Lista* novo = (Lista*) malloc(sizeof(Lista));
 novo->info = i;
 novo->prox = l;
 return novo;
}

/* função imprime: imprime valores dos elementos */
void imprime (Lista* l)
{
 Lista* p; /* variável auxiliar para percorrer a lista */
 for (p = l; p != NULL; p = p->prox)
 printf("info = %d\n”, p->info");
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int vazia (Lista* l)
{
 if (l == NULL)
    return 1;
else
    return 0;
}


/* função busca: busca um elemento na lista */
Lista* busca (Lista* l, int v)
{
 Lista* p;
 for (p=l; p!=NULL; p=p->prox)
 if (p->info == v)
 return p;
 return NULL; /* não achou o elemento */
}


/* função retira: retira elemento da lista */
Lista* retira (Lista* l, int v) {
 Lista* ant = NULL; /* ponteiro para elemento anterior */
 Lista* p = l; /* ponteiro para percorrer a lista*/
 /* procura elemento na lista, guardando anterior */
 while (p != NULL && p->info != v) {
   ant = p;
   p = p->prox;
 }
 /* verifica se achou elemento */
 if (p == NULL)
    return l; /* não achou: retorna lista original */
 /* retira elemento */
 if (ant == NULL) {
 /* retira elemento do inicio */
   l = p->prox;
 }
 else {
 /* retira elemento do meio da lista */
    ant->prox = p->prox;
 }
 free(p);
 return l;
}

void libera (Lista* l)
{
 Lista* p = l;
 while (p != NULL) {
 Lista* t = p->prox; /* guarda referência para o próximo elemento
*/
 free(p); /* libera a memória apontada por p */
 p = t; /* faz p apontar para o próximo */
 }
}

/* função auxiliar: cria e inicializa um nó */
Lista* cria (int v)
{
 Lista* p = (Lista*) malloc(sizeof(Lista));
 p->info = v;
 return p;
}
/* função insere_ordenado: insere elemento em ordem */
Lista* insere_ordenado (Lista* l, int v)
{
 Lista* novo = cria(v); /* cria novo nó */
 Lista* ant = NULL; /* ponteiro para elemento anterior */
 Lista* p = l; /* ponteiro para percorrer a lista*/
 /* procura posição de inserção */
 while (p != NULL && p->info < v) {
 ant = p;
 p = p->prox;
 }
 /* insere elemento */
 if (ant == NULL) { /* insere elemento no início */
 novo->prox = l;
 l = novo;
 }
 else { /* insere elemento no meio da lista */
 novo->prox = ant->prox;
 ant->prox = novo;
 }
 return l;
}

/* Função retira recursiva */
Lista* retira_rec (Lista* l, int v)
{
 if (vazia(l))
 return l; /* lista vazia: retorna valor original */
 /* verifica se elemento a ser retirado é o primeiro */
 if (l->info == v) {
 Lista* t = l; /* temporário para poder liberar */
 l = l->prox;
 free(t);
 }
 else {
 /* retira de sub-lista */
 l->prox = retira_rec(l->prox,v);
 }
 return l;
}

/* Função imprime recursiva */
void imprime_rec (Lista* l)
{
 if (vazia(l))
 return;
 /* imprime primeiro elemento */
 printf("“info: %d\n”",l->info);
 /* imprime sub-lista */
 imprime_rec(l->prox);
}

/* Função imprime recursiva ordem inversa */
void imprime_rec_inversa (Lista* l)
{
 if (vazia(l))
    return;
 /* imprime sub-lista */
 imprime_rec(l->prox);
  /* imprime primeiro elemento */
 printf("“info: %d\n”",l->info);

}

void libera_rec (Lista* l)
{
 if (!vazia(l))
 {
 libera_rec(l->prox);
 free(l);
 }
}


int main (void) {
 Lista* l; /* declara uma lista não iniciada */
 l = inicializa(); /* inicia lista vazia */
 l = insere(l, 23); /* insere na lista o elemento 23 */
 l = insere(l, 45); /* insere na lista o elemento 45 */
 l = insere(l, 56); /* insere na lista o elemento 56 */
 l = insere(l, 78); /* insere na lista o elemento 78 */
 imprime(l); /* imprimirá: 78 56 45 23 */
 l = retira(l, 78);
 imprime(l); /* imprimirá: 56 45 23 */
 l = retira(l, 45);
 imprime(l); /* imprimirá: 56 23 */
 libera(l);
 return 0;
}

/*

Exercício: Implemente uma função que verifique se duas listas encadeadas são iguais.
Duas listas são consideradas iguais se têm a mesma seqüência de elementos. O
protótipo da função deve ser dado por:
int igual (Lista* l1, Lista* l2);


Exercício: Implemente uma função que crie uma cópia de uma lista encadeada. O
protótipo da função deve ser dado por:
Lista* copia (Lista* l);

*/
