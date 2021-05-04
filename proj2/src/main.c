/*------------------------ Projeto 2 IAED -------------------------*/
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*              Sistema de Gestão de uma Base de Dados             */
/*                   de Jogos de Futebol Amigáveis                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                  Mafalda Ferreira - 92513                       */
/*-----------------------------------------------------------------*/

#include "processos.h"
#include "hashtable.h"
#include "lista.h"
#include "AVL.h"
#include "jogo.h"
#include "equipa.h"

int main(){
    Avl avl; /*Ponteiro para a AVL que guarda as equipas de acordo com o nome*/
    Hashtable ht; /*Ponteiro para a hashtable que guarda os jogos de acordo com a hash*/
    Lista lst; /*Ponteiro para a lista que guarda os jogos pela ordem de insercao*/
    inicializa(&avl, &ht, &lst);
    processa(avl,ht, lst);
    limpa(avl, ht, lst);
    return 0;
}