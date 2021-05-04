#include "AVL.h"

/*Inicializa a AVL, alocando memória e colocando a head a NULL*/
void avl_init(Avl* avl){
    *avl = (Avl) malloc(sizeof(struct avl_str));
    (*avl)->head = NULL;
}

/*Aloca memória para o no da AVL*/
avl_link avl_cria(pEquipa equipa){
    avl_link link = (avl_link) malloc(sizeof(struct avl_node));
    link->equipa = equipa;
    link->l = NULL;
    link->r = NULL;
    link->altura = 1;
    return link;
}

/*Insere equipa na AVL de acordo com a sua chave*/
avl_link avl_insere(avl_link h, pEquipa equipa){
    if(NULLitem(h))
        return avl_cria(equipa);
    if(strmenor(chave(equipa), chave(h->equipa))) /*Se a chave for menor que a de h, insere à esquerda*/
        h->l = avl_insere(h->l, equipa);
    else /*Se a chave for maior que a de h, insere à direita*/
        h->r = avl_insere(h->r, equipa);
    h = avl_balanco(h);
    return h;
}

/*Procura a equipa na AVL. Se a equipa não existir, retorna NULL*/
avl_link avl_procura(avl_link h, Chave nome){
    if(NULLitem(h))
        return NULL;
    if(strigual(nome, chave(h->equipa)))
        return h;
    if(strmenor(nome, chave(h->equipa)))
        return avl_procura(h->l, nome);
    else
        return avl_procura(h->r, nome);
    
}

/*Verifica se a equipa existe na AVL. Se não existir retorna erro de acordo com a opcao*/
/*Opcao 0 : retorna erro se equipa não existir. Opcao 1 : retorna erro se equipa existir*/
avl_link avl_verifica(Avl avl, Chave nome, int opcao, int NL){
    avl_link link = avl_procura(avl->head, nome);
    if(igual(opcao, 0) && NULLitem(link))
        printf("%d Equipa inexistente.\n", NL);
    else if(igual(opcao, 1) && !NULLitem(link))
        printf("%d Equipa existente.\n", NL);
    return link;
}

/*Equilibra a árvore mantendo o módulo da diferenca de nós irmãos menor que 2*/
avl_link avl_balanco(avl_link h){
    int fator;
    if(NULLitem(h))
        return h;
    fator = avl_obtem_fator(h);
    if(fator < -1){ /*Caso haja mais peso à esquerda*/
        if(avl_obtem_fator(h->l) <= 0) /*Caso haja mais peso à esquerda (da esquerda)*/
            h = avl_rotacao_R(h);
        else /*Caso haja mais peso à direita (da esquerda)*/
            h = avl_rotacao_LR(h);
    }
    else if(fator > 1){ /*Caso haja mais peso para à direita*/
        if(avl_obtem_fator(h->r) >= 0) /*Caso haja mais peso para à direita (da direita)*/
            h = avl_rotacao_L(h);
        else /*Caso haja mais peso para à esquerda (da direita)*/
            h = avl_rotacao_RL(h);
    }
    else /*Atualiza a altura de h*/
        h->altura = avl_atualiza_altura(h);
    return h;
}

/*Rotação à esquerda*/
avl_link avl_rotacao_L(avl_link h){
    avl_link x;
    x = h->r;
    h->r = x->l;
    x->l = h;
    /*Atualização das alturas de h e x apos suas alteracoes*/
    h->altura = avl_atualiza_altura(h);
    x->altura = avl_atualiza_altura(x);
    return x;
}

/*Rotação à direita*/
avl_link avl_rotacao_R(avl_link h){
    avl_link x;
    x = h->l;
    h->l = x->r;
    x->r = h;
    /*Atualização das alturas de h e x após suas alteracoes*/
    h->altura = avl_atualiza_altura(h);
    x->altura = avl_atualiza_altura(x);
    return x;
}

/*Rotação dupla esquerda-direita*/
avl_link avl_rotacao_LR(avl_link h){
    if(NULLitem(h))
        return h;
    h->l = avl_rotacao_L(h->l);
    return avl_rotacao_R(h);
}

/*Rotação dupla direita-esquerda*/
avl_link avl_rotacao_RL(avl_link h){
    if(NULLitem(h))
        return h;
    h->r = avl_rotacao_R(h->r);
    return avl_rotacao_L(h);
}

/* Retorna o fator de balanceamento (diferenca entre o nós da direita e da esquerda) do nó*/
/* Se o nó for nulo então retorna 0*/
int avl_obtem_fator(avl_link link){
    if(NULLitem(link))
        return 0;
    return avl_obtem_altura(link->r) - avl_obtem_altura(link->l);
}

/*Retorna a altura do nó. Se este for nulo então retorna 0*/
int avl_obtem_altura(avl_link h){
    if(NULLitem(h))
        return 0;
    return h->altura;
}

/*Retorna a maior altura entre a altura dos nós da esquerda e da direita*/
int avl_atualiza_altura(avl_link link){
    int altura_l, altura_r;
    altura_l = avl_obtem_altura(link->l);
    altura_r = avl_obtem_altura(link->r);
    if(maior(altura_l, altura_r))
        return altura_l + 1;
    return altura_r + 1;
}

/*Percorre os nós por ordem das chaves e retorna o número máximo de jogos ganhos*/
int avl_obtem_max_ganhos(avl_link h, int max_ganhos){
    if(NULLitem(h))
        return max_ganhos;
    max_ganhos = avl_obtem_max_ganhos(h->l, max_ganhos); /*Consulta o nó da esquerda*/
    /*Se o nímero de  jogos ganhos da equipa for maior que o número máximo, então atualiza-o*/
    if(maior(h->equipa->ganhos, max_ganhos))
        max_ganhos = h->equipa->ganhos;
    max_ganhos = avl_obtem_max_ganhos(h->r, max_ganhos); /*Consulta o nó da direita*/
    return max_ganhos;
}

/*Print das equipas por ordem de chave, ou seja, ordem alfabética*/
void avl_print_melhores(avl_link h, int max_ganhos, int NL){
    if(NULLitem(h))
        return;
    avl_print_melhores(h->l, max_ganhos, NL);
    if(igual(h->equipa->ganhos, max_ganhos))
        equipa_print_melhor(h->equipa, NL);
    avl_print_melhores(h->r, max_ganhos, NL);
}

/*Liberta a memória associada ao nó*/
void avl_free_h(avl_link h){
    if(!NULLitem(h)){
        avl_free_h(h->l);
        avl_free_h(h->r);
        equipa_free(h->equipa);
        free(h);
    }
}

/*Liberta a memória restante associada à lista*/
void avl_free(Avl avl){
    avl_free_h(avl->head);
    free(avl);
}