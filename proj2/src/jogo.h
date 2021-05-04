/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

/*---------- Contém as funções e as estruturas dos jogos ----------*/

#ifndef _JOGO_
#define _JOGO_

#include <stdio.h>
#include <stdlib.h>
#include "equipa.h"

/*Estrutura de um jogo*/
typedef struct str_jogo{
    char* nome;
    int score[MAX_E];
    pEquipa equipas[MAX_E];
} *pJogo;

pJogo jogo_cria(char*, pEquipa*, int*);
void jogo_atualiza_ganhos(pEquipa*, int*, int*);
void jogo_atualiza_score(pJogo, int*);
void jogo_print(pJogo, int);
void jogo_free(pJogo);

#endif