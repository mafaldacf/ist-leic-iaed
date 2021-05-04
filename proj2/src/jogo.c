#include "jogo.h"

/*Aloca memoria para o jogo*/
pJogo jogo_cria(char* nome, pEquipa* equipas, int* score){
    int i;
    pJogo jogo = (pJogo) malloc(sizeof(struct str_jogo));
    jogo->nome = duplica(nome);
    for(i = 0; i < MAX_E; i++){
        jogo->equipas[i] = equipas[i];
        jogo->score[i] = score[i];
    }
    return jogo;
}

/*Atualiza o score do jogo após alteração do mesmo*/
void jogo_atualiza_score(pJogo jogo, int *score){
    int i;
    for(i = 0; i < MAX_E; i++)
        jogo->score[i] = score[i];
}

/*Print do jogo*/
void jogo_print(pJogo jogo, int NL){
    printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipas[0]->nome, jogo->equipas[1]->nome, jogo->score[0], jogo->score[1]);
}

/*Liberta a memória associada ao jogo*/
void jogo_free(pJogo jogo){
    free(jogo->nome);
    free(jogo);
}