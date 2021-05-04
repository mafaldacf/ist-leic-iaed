#include "lista.h"

/*Inicia a lista, alocando memória e colocando o head e tail a NULL*/
void lst_init(Lista* lst){
    *lst = (Lista) malloc(sizeof(struct lista_str));
    (*lst)->head = NULL;
    (*lst)->tail = NULL;
}

/*Cria um nó*/
lst_link lst_cria(pJogo jogo){
    lst_link link = (lst_link) malloc(sizeof(struct lst_node));
    link->jogo = jogo;
    link->next = NULL;
    return link;
}


/*Insere o jogo na lista*/
lst_link lst_insere(pJogo jogo, Lista lst){
    lst_link link = lst_cria(jogo);
    if(NULLitem(lst->head)){ /*Se a lista ainda for fazia, o jogo passa a ser o primeiro elemento*/
        lst->head = link;
        link->prev = NULL;
    }
    else{ /*Se a lista não for vazia, adiciona o jogo ao fim da mesma*/
        link->prev = lst->tail; 
        lst->tail->next = link;
    }
    lst->tail = link; /*A tail da lista passa a apontar para o novo nó*/
    return link;
}

/*Remove o jogo da lista*/
void lst_remove(lst_link link, Lista lst){
    lst_link l, r;
    l = link->prev;
    r = link->next;
    if(igual(lst->head, lst->tail)){ /*Se o jogo for o único da lista*/
        lst->head = NULL;
        lst->tail = NULL;
    }
    else if(igual(lst->head, link)){ /*Se o jogo for o primeiro a lista*/
        r->prev = NULL;
        lst->head = r;
    }
    else if(igual(lst->tail, link)){ /*Se o jogo for o último da lista*/
        l->next = NULL;
        lst->tail = l;
    }
    else{ /*Se o jogo não estiver nas extremidades da lista*/
        l->next = r;
        r->prev = l;
    }
    jogo_free(link->jogo);
    free(link);
}

/*Print dos jogos na lista por ordem de inserçao*/
void lst_print(Lista lst, int NL){
    lst_link link;
    for(link = lst->head; link != NULL; link = link->next)
        jogo_print(link->jogo, NL);
}

/*Liberta a memória associada a um nó*/
void lst_node_free(lst_link link){
    jogo_free(link->jogo);
    free(link);
}

/*Liberta a memória associada à lista*/
void lst_free(Lista lst){
    free(lst);
}