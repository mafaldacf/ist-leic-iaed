/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

/*---------- Contém as funções e as estruturas da lista, ----------*/
/*------- sendo que cada nó guarda um ponteiro para cada jogo -----*/

#ifndef _LISTA_
#define _LISTA_

#include <stdlib.h>
#include "jogo.h"

/*Estrutura dos nós de uma lista duplamente ligada*/
typedef struct lst_node{
    pJogo jogo;
    struct lst_node* next; /*Ponteiro para o nó do próximo jogo*/
    struct lst_node* prev; /*Ponteiro para o nó do jogo anterior*/
} *lst_link;

/*Estrutura da lista*/
typedef struct lista_str{
    lst_link head; /*link que aponta para o primeiro elemento da lista*/
    lst_link tail; /*link que aponta para o úliimo elemento da lista*/
} *Lista;

void lst_init(Lista*);
lst_link lst_cria(pJogo);
lst_link lst_insere(pJogo, Lista);
void lst_remove(lst_link, Lista);
void lst_print(Lista, int);
void lst_node_free(lst_link);
void lst_free(Lista);

#endif