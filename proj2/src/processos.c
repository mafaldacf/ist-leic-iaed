#include "processos.h"

void processa(Avl avl, Hashtable ht, Lista lst){
    char cmd;
    int NL = 0; /*Número da linha de cada comando*/
    while(((cmd = getchar()) != 'x')){
        if(cmd >= 'A') /*Incrementa NL sempre que for recebido um comando novo válido*/
            NL++;
        switch(cmd){
            case 'a': adiciona_jogo(avl, ht, lst, NL); break;
            case 'A': adiciona_equipa(avl, NL);        break;
            case 'l': lista_jogos(lst, NL);            break;
            case 'P': procura_equipa(avl, NL);         break;
            case 'p': procura_jogo(ht, NL);            break;
            case 'r': remove_jogo(ht, lst, NL);        break;
            case 's': altera_score(ht, NL);            break;
            case 'g': lista_melhores(avl, NL);         break;
        }
    }
}

/*Inicializa toda a memória necessária para o programa*/
void inicializa(Avl* avl, Hashtable* ht, Lista* lst){
    avl_init(avl);
    ht_init(ht);
    lst_init(lst);
}

/*Limpa toda a memória alocada dinamicamente antes de sair do programa*/
void limpa(Avl avl, Hashtable ht, Lista lst){
    avl_free(avl);
    ht_free(ht);
    lst_free(lst);
}

/*Obtém o nome a partir do input*/
void obtem_nome(char* nome){
    scanf(" %[^:\n]", nome);
}

/*Obtém o score a partir do input*/
void obtem_score(int score[]){
    scanf(":%d:%d", &score[0], &score[1]);
}

/*Obtém o nome das equipas a partir do input*/
void obtem_equipas(char nomes[][MAXCHARS]){
    scanf(":%[^:\n]:%[^:\n]", nomes[0], nomes[1]);
}

/*Comando a*/
void adiciona_jogo(Avl avl, Hashtable ht, Lista lst, int NL){
    int i, score[MAX_E];
    char nome_jogo[MAXCHARS], nome_equipas[MAX_E][MAXCHARS];
    avl_link link_avl[MAX_E];
    ht_link link_ht;
    lst_link link_lst;
    pJogo jogo;
    pEquipa equipas[MAX_E];

    /*Obtém input*/
    obtem_nome(nome_jogo);
    obtem_equipas(nome_equipas);
    obtem_score(score);

    link_ht = ht_verifica(nome_jogo, ht, 1, NL);

    /*Se o jogo ainda não existir, procede com a verificacao das equipas e posterior criação do jogo*/
    if(NULLitem(link_ht)){
        for(i = 0; i < MAX_E; i++){
            link_avl[i] = avl_verifica(avl, nome_equipas[i], 0, NL);
            if(NULLitem(link_avl[i])) /*Sai da função se alguma das equipas não existir*/
                return;
            equipas[i] = link_avl[i]->equipa; /*Insere a equipa no nó da AVL criado para a equipa*/
        }
        jogo = jogo_cria(nome_jogo, equipas, score);
        link_lst = lst_insere(jogo, lst);
        ht_insere(link_lst, ht);
        equipa_atualiza_ganhos(equipas, score, 1);
    }
}

/*Comando A*/
void adiciona_equipa(Avl avl, int NL){
    char nome[MAXCHARS];
    pEquipa equipa;
    avl_link link;
    obtem_nome(nome);
    link = avl_verifica(avl, nome, 1, NL);

    /*Se a equipa ainda não existir, então cria espaco para a mesma e insere-a na AVL*/
    if(NULLitem(link)){
        equipa = equipa_cria(nome);
        avl->head = avl_insere(avl->head, equipa);
    }
}

/*Comando l*/
void lista_jogos(Lista lst, int NL){
    lst_print(lst, NL);
}

/*Comando P*/
void procura_equipa(Avl avl, int NL){
    char nome[MAXCHARS];
    avl_link link;
    obtem_nome(nome);
    link = avl_verifica(avl, nome, 0, NL);
    if(!NULLitem(link)) /*Caso a equipa exista*/
        equipa_print(link->equipa, NL);
}

/*Comando p*/
void procura_jogo(Hashtable ht, int NL){
    char nome[MAXCHARS];
    ht_link link;
    obtem_nome(nome);
    link = ht_verifica(nome, ht, 0, NL);
    if(!NULLitem(link)) /*Caso o jogo exista*/
        jogo_print(jogo_ht(link), NL);
}

/*Comando r*/
void remove_jogo(Hashtable ht, Lista lst, int NL){
    char nome[MAXCHARS];
    ht_link link;
    obtem_nome(nome);
    link = ht_verifica(nome, ht, 0, NL);
    if(!NULLitem(link)){ /*Caso o jogo exista*/
        equipa_atualiza_ganhos(jogo_ht(link)->equipas, jogo_ht(link)->score, 0);
        ht_remove(link, lst, ht);
    }
}

/*Comando s*/
void altera_score(Hashtable ht, int NL){
    char nome[MAXCHARS];
    int score[MAX_E];
    ht_link link;

    /*Obtém input*/
    obtem_nome(nome);
    obtem_score(score);

    link = ht_verifica(nome, ht, 0, NL);
    if(!NULLitem(link)){ /*Caso o jogo exista*/
        equipa_atualiza_ganhos_s(jogo_ht(link)->equipas, jogo_ht(link)->score, score);
        jogo_atualiza_score(jogo_ht(link), score);
    }
}

/*Comando g*/
void lista_melhores(Avl avl, int NL){
    int max_ganhos = avl_obtem_max_ganhos(avl->head, 0);
    if(!NULLitem(avl->head)){ /*Caso a AVL não esteja vazia, ou seja, caso existirem equipas*/
        printf("%d Melhores %d\n", NL, max_ganhos);
        avl_print_melhores(avl->head, max_ganhos, NL);
    }
}