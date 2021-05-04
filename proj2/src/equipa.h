/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

/*--------- Contém as funções e as estruturas das equipas ---------*/

#ifndef _EQUIPA_
#define _EQUIPA_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Máximo de equipas num par*/
#define MAX_E 2

/*Verifica se o item é nulo*/
#define NULLitem(a) (a == NULL)

/*Comparação de números*/

#define maior(a, b) (a > b)
#define menor(a, b) (maior(b, a))
#define igual(a, b) (a == b)

/*Comparação de strings*/

#define strmaior(a, b) (strcmp(a, b) > 0)
#define strmenor(a, b) (strmaior(b, a))
#define strigual(a, b) (strcmp(a, b) == 0)

/*Estrutura de uma equipa*/
typedef struct str_equipa{
    char* nome;
    int ganhos;
} *pEquipa;

/*Incrementa 1 aos jogos ganhos da equipa*/
#define inc(a) (a->ganhos++)

/*Decrementa 1 aos jogos ganhos da equipa*/
#define dec(a) (a->ganhos--)

pEquipa equipa_cria(char*);
void equipa_atualiza_ganhos(pEquipa[], int[], int);
void equipa_atualiza_ganhos_s(pEquipa[], int[], int[]);
void equipa_print(pEquipa, int);
void equipa_print_melhor(pEquipa, int);
void equipa_free(pEquipa);
char* duplica(char*);

#endif