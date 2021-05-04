#include "equipa.h"

/*Aloca memória para a equipa*/
pEquipa equipa_cria(char* nome){
    pEquipa equipa = (pEquipa) malloc(sizeof(struct str_equipa));
    equipa->nome = duplica(nome);
    equipa->ganhos = 0;
    return equipa;
}

/*Atualiza os jogos ganhos das equipas após adição ou remoção do jogo*/
/*Opção 1 : Adiciona ganho. Opção 0 : Remove ganho*/
void equipa_atualiza_ganhos(pEquipa equipas[], int score[], int opcao){
    int i, j;
    for(i = 0, j = 1; i < MAX_E; i++, j--){
        if(maior(score[i], score[j])){
            if(opcao == 1)
                inc(equipas[i]);
            else
                dec(equipas[i]);
        }
    }
}

/*Atualiza os jogos ganhos das equipas após alteração do score do jogo*/
void equipa_atualiza_ganhos_s(pEquipa equipas[], int score_antigo[], int score_novo[]){
    int i, j;
    if(igual(score_novo[0], score_novo[1])) /*Caso as equipas tenham empatado após alteração do score*/
        equipa_atualiza_ganhos(equipas, score_antigo, 0);
    if(igual(score_antigo[0], score_antigo[1])) /*Caso as equipas tenham empatado antes da alteração do score*/
        equipa_atualiza_ganhos(equipas, score_novo, 1);
    for(i = 0, j = 1; i < MAX_E; i++, j--){ /*Caso uma das equipas tenha ganho antes e perdido depois*/
        if(maior(score_antigo[i], score_antigo[j])){
            if(menor(score_novo[i], score_novo[j])){
                inc(equipas[j]);
                dec(equipas[i]);
                break;
            }
        }
    }
}


/*Print da equipa*/
void equipa_print(pEquipa equipa, int NL){
    printf("%d %s %d\n", NL, equipa->nome, equipa->ganhos);
}

/*Print da equipa que se encontra nas melhores*/
void equipa_print_melhor(pEquipa equipa, int NL){
    printf("%d * %s\n", NL, equipa->nome);
}

/*Liberta a memória associada à equipa*/
void equipa_free(pEquipa equipa){
    free(equipa->nome);
    free(equipa);
}

/*Aloca memória e copia string a duplicar para a memória alocada*/
char* duplica(char* str){
    char* dup = (char*) malloc(sizeof(char)*(strlen(str)+1));
    strcpy(dup, str);
    return dup;
}
