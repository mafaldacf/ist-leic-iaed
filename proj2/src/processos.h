/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

/*-------- Contém todas as funções que inicializam/limpam ---------*/
/*------------ a memória a utilizar e processam o input -----------*/

#ifndef _PROCESSOS_
#define _PROCESSOS_

#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"
#include "lista.h"
#include "AVL.h"
#include "jogo.h"
#include "equipa.h"

/*Número máximo de caracteres que uma string recebida pode ter*/
#define MAXCHARS 1024

/*Processamento geral*/

void processa(Avl, Hashtable, Lista);
void inicializa(Avl*, Hashtable*, Lista*);
void limpa(Avl, Hashtable, Lista);

/*Processamento do input*/

void obtem_nome(char*);
void obtem_score(int[]);
void obtem_equipas(char nomes[][MAXCHARS]);

/*Processamento dos comandos*/

void adiciona_jogo(Avl, Hashtable, Lista, int);
void adiciona_equipa(Avl, int);
void lista_jogos(Lista, int);
void procura_equipa(Avl, int);
void procura_jogo(Hashtable, int);
void remove_jogo(Hashtable, Lista, int);
void altera_score(Hashtable, int);
void lista_melhores(Avl, int);

#endif