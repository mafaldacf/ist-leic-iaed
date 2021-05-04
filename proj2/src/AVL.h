/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

/*-------- Contém as funções e as estruturas da AVL, sendo --------*/
/*-------- que cada nó guarda um ponteiro para cada equipa --------*/

#ifndef _AVL_
#define _AVL_

#include <stdlib.h>
#include "equipa.h"

typedef char* Chave;

/*A chave de uma equipa corresponde ao seu nome*/
#define chave(a) (a->nome)

/*Estrutura dos nós de uma AVL*/
typedef struct avl_node{
    pEquipa equipa;
    int altura;
    struct avl_node* l; /*Ponteiro para a parte da árvore à esquerda do nó*/
    struct avl_node* r; /*Ponteiro para a parte da árvore à direita do nó*/
} *avl_link;

/*Estrutura da AVL*/
typedef struct avl_str{
    avl_link head; /*Link que aponta para a raíz da AVL.*/
} *Avl;

void avl_init(Avl*);

/*Funções básicas da AVL*/

avl_link avl_cria(pEquipa);
avl_link avl_insere(avl_link, pEquipa);
avl_link avl_procura(avl_link, Chave);
avl_link avl_verifica(Avl, Chave, int, int);

/*Balanceamento da árvore*/

avl_link avl_balanco(avl_link);
avl_link avl_rotacao_L(avl_link);
avl_link avl_rotacao_R(avl_link);
avl_link avl_rotacao_LR(avl_link);
avl_link avl_rotacao_RL(avl_link);

int avl_obtem_fator(avl_link);
int avl_obtem_altura(avl_link);
int avl_atualiza_altura(avl_link);

/*Tratamento das melhores equipas*/

int avl_obtem_max_ganhos(avl_link, int);
void avl_print_melhores(avl_link, int, int);

/*Libertação de memória*/

void avl_free_h(avl_link);
void avl_free(Avl);

#endif