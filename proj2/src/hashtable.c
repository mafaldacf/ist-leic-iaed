#include "hashtable.h"

/*Funcao Hash que retorna o valor da chave*/
int hash(char* str){
    int chave;
    for(chave = 0; *str != '\0'; str++)
        chave = (((chave << 2) + chave) + *str) % HTSIZE;
    return chave;
}

/*Inicializa a hashtable, alocando memoria e colocando todos os heads a NULL*/
void ht_init(Hashtable* ht){
    int i;
    *ht = (Hashtable) malloc(sizeof(struct hashtable_str));
    (*ht)->heads = (ht_link*) malloc(sizeof(ht_link)*HTSIZE);
    for(i = 0; i < HTSIZE; i++)
        (*ht)->heads[i] = NULL;
}

/*Aloca memoria para o no da hashtable*/
ht_link ht_cria(lst_link lst){
    ht_link link = (ht_link) malloc(sizeof(struct ht_node));
    link->lst = lst;
    return link;
}

/*Verifica se o jogo existe na hashtable recorrendo a sua chave*/
/*Se o link recebido na ht_procura for NULL, entao retorna erro de acordo com a opcao*/
/* Opcao 0 = retorna erro se jogo nao existir. Opcao 1 = retorna erro se jogo existir*/
ht_link ht_verifica(char* nome, Hashtable ht, int opcao, int NL){
    ht_link link = ht_procura(nome, ht);
    if(igual(opcao, 0) && NULLitem(link))
        printf("%d Jogo inexistente.\n", NL);
    else if(igual(opcao, 1) && !NULLitem(link))
        printf("%d Jogo existente.\n", NL);
    return link;
}

/*Procura o jogo na hashtable, recorrendo a sua chave e ao seu nome. Se nao encontrar retorna NULL*/
ht_link ht_procura(char* nome, Hashtable ht){
    int i;
    ht_link link;
    i = hash(nome);
    link = ht->heads[i];
    while(link != NULL){ /*Percorre os nos do indice i da hashtable ate encontrar o jogo*/
        if(strigual(jogo_ht(link)->nome, nome))
            return link;
        link = link->next;
    }
    return link;
}

/*Insere o jogo na hashtable de acordo com a sua chave*/
void ht_insere(lst_link lst, Hashtable ht){
    int i;
    ht_link link;
    i = hash(lst->jogo->nome);
    link = ht_cria(lst);
    /*Insere no inicio do indice i da hashtable*/
    link->next = ht->heads[i];
    ht->heads[i] = link;
}

/*Remove o link (do jogo) da hashtable de acordo com a sua chave*/
void ht_remove(ht_link link, Lista lst, Hashtable ht){
    int i;
    ht_link x;
    i = hash(jogo_ht(link)->nome);
    if(igual(ht->heads[i], link)) /*Caso o jogo seja primeiro do indice i da hashtable*/
        ht->heads[i] = link->next;
    else{ /*Caso contrario...*/
        x = ht->heads[i];
        while(!igual(x->next, link)) /*Percorre os nos do indice i da hashtable ate encontrar o link*/
            x = x->next;
        x->next = link->next; /*O ponteiro next do no anterior passa a apontar para o no que sucede o link a ser eliminado*/
    }
    lst_remove(link->lst, lst);
    free(link);
}

/*Liberta toda a memoria associada a hashtable*/
void ht_free(Hashtable ht){
    int i;
    ht_link x;
    for(i = 0; i < HTSIZE; i++)
        /*Enquanto o indice i da hashtable nao for nulo, percorre todos os nos associados ao mesmo e liberta a memoria necessaria*/
        while(!NULLitem(ht->heads[i])){    
            x = ht->heads[i];
            ht->heads[i] = x->next;
            lst_node_free(x->lst);
            free(x);
        }
    free(ht->heads);
    free(ht);
}