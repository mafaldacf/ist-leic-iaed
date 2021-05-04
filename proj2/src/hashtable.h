/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

/*----- Contém as funções e as estruturas da hashtable, sendo -----*/
/*- que cada nó guarda um ponteiro que aponta para um nó da lista -*/

#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <stdlib.h>
#include "lista.h"

/*Número de índices da hashtable*/
#define HTSIZE 997

/*Estrutura dos nós de uma hashtable*/
typedef struct ht_node{
    lst_link lst;
    struct ht_node *next; /*Ponteiro para o nó seguinte da hashtable no mesmo índice*/
} *ht_link;

/*Estrutura de uma hashtable*/
typedef struct hashtable_str{
    ht_link *heads; /*Link que aponta para um vetor de links definido pelo tamanho da hashtable*/
} *Hashtable;

/*Retorna o jogo da lista da hashtable*/
#define jogo_ht(a) (a->lst->jogo)

int hash(char*);
void ht_init(Hashtable*);
ht_link ht_cria(lst_link);
ht_link ht_verifica(char*, Hashtable, int, int);
ht_link ht_procura(char*, Hashtable);
void ht_insere(lst_link, Hashtable);
void ht_remove(ht_link, Lista lst, Hashtable);
void ht_free(Hashtable);

#endif