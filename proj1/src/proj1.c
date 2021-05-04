/*---------------------- Projeto IAED ----------------------*/
/*                                                          */
/*                         proj1.c                          */
/*                  Mafalda Ferreira - 92513                */
/*----------------------------------------------------------*/

/************************ Bibliotecas ***********************/

#include <stdio.h>
#include <string.h>

/************************ Constantes ************************/

/*Numero maximo de caracteres da descricao de um produto.*/
#define MAXCHAR 63
 /*Numero maximo do peso e, consequentemente, numero maximo de produtos na encomenda.*/
#define MAXP 200
 /*Numero maximo de encomendas.*/
#define MAXENC 500
/*Numero maximo de produtos.*/
#define MAXPRODS 10000
/*Numero de dados de um produto na lista de uma encomenda: id do produto e quantidade.*/
#define DADOS 2

/********************* Outras Definicoes ********************/

#define copia(A, B) {A[0] = B[0]; A[1] = B[1];}

/******************* Estruturas de Dados ********************/

typedef struct {
    char desc[MAXCHAR];
    int preco, peso, qtd;
} Produtos;

typedef struct {
    int lista[MAXP][DADOS], peso, num_prods;
    } Encomendas;
/*A matriz lista guarda os id's dos produtos em [x][0] e as respetivas quantidades na encomenda em [x][1].*/

/******************** Variaveis Globais *********************/

/*Vetor onde sao guardados os elementos do tipo Produtos. Cada indice corresponde ao seu id.*/
Produtos prod[MAXPRODS];
/*Vetor onde sao guardados os elementos do tipo Encomendas. Cada indice corresponde ao seu id.*/
Encomendas enc[MAXENC];
/*Numero total de produtos.*/
int pcount;
/*Numero total de encomendas.*/
int ecount;
/*Vetor que contem os indices dos produtos ordenados por ordem crescente de preco.*/
int idps_ord[MAXPRODS];

/*********************** Prototipos *************************/

void adiciona_prod();
void adiciona_stock_prod();
void cria_enc();
void adiciona_prod_enc();
void remove_stock_prod();
void remove_prod_enc();
void custo_enc();
void altera_preco();
void mostra_prod_enc();
void maior_ocorrencia();
void lista_prods();
void lista_enc();

/*funcoes auxiliares*/

void mostra_prod(int, int);

int obtem_preco_prod(int);
int obtem_peso_prod(int);
int obtem_qtd_prod(int);
int* obtem_prod_enc(int, int);
int obtem_idp_enc(int, int);
int obtem_qtd_prod_enc(int, int);
int obtem_num_prods_enc(int);
int obtem_peso_enc(int);

void altera_qtd_prod(int, int);
void altera_idp_enc(int, int, int);
void altera_qtd_prod_enc(int, int, int);
void altera_peso_enc(int, int, int);
void altera_num_prods_enc(int, int);

int cria_prod_enc(int, int);
int procura_prod_enc(int, int);
void limpa_prod_enc(int, int);

void copia_idps();
void ordena_idps();
int menor_preco(int, int);
void ordena_enc(int);
int menor_desc(int, int);

int verifica_ide_idp(int, int, char);
int verifica_quantidades(int, int, int, char);

/*************************** Codigo *************************/

int main(){
    char cmd;
    while ((cmd = getchar()) != 'x'){
        switch (cmd){
            case 'a':
                adiciona_prod();
                break;
            case 'q':
                adiciona_stock_prod();
                break;
            case 'N':
                cria_enc();
                break;
            case 'A':
                adiciona_prod_enc();
                break;
            case 'r':
                remove_stock_prod();
                break;
            case 'R':
                remove_prod_enc();
                break;
            case 'C':
                custo_enc();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                mostra_prod_enc();
                break;
            case 'm':
                maior_ocorrencia();
                break;
            case 'l':
                lista_prods();
                break;
            case 'L':
                lista_enc();
                break;
        }
    }
    return 0;
}

/*Comando a.*/
void adiciona_prod(){
    scanf(" %[^:]:%d:%d:%d",  prod[pcount].desc, &prod[pcount].preco, &prod[pcount].peso, &prod[pcount].qtd);
    printf("Novo produto %d.\n", pcount);
    pcount++;
}

/*Comando q.*/
void adiciona_stock_prod(){
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if ((verifica_ide_idp(-1, idp, 'q')) == 1)
        altera_qtd_prod(idp, qtd);
}

/*Comando N.*/
void cria_enc(){
    printf("Nova encomenda %d.\n", ecount);
    ecount++;
}

/*Comando A.*/
void adiciona_prod_enc(){
    int ide,idp,qtd, i; 
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if ((verifica_ide_idp(ide, idp, 'A')) == 1 && (verifica_quantidades(ide, idp, qtd, 'A')) == 1){
        i = procura_prod_enc(ide, idp);
        if (i == -1) /*Adiciona-se o produto a encomenda caso este ainda nao exista na mesma.*/
            i = cria_prod_enc(ide, idp);
        altera_qtd_prod(idp, -qtd);
        altera_qtd_prod_enc(ide, i, qtd);
        altera_peso_enc(ide, idp, qtd);
    }
}

/*Comando r.*/
void remove_stock_prod(){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if ((verifica_ide_idp(-1, idp, 'r')) == 1 && (verifica_quantidades(0, idp, qtd, 'r')) == 1){
        altera_qtd_prod(idp, -qtd);
    }
}

/*Comando R.*/
void remove_prod_enc(){
    int ide, idp, i, i_max, qtd;
    scanf("%d:%d", &ide, &idp);
    if ((verifica_ide_idp(ide, idp, 'R')) == 1){
        i = procura_prod_enc(ide, idp);
        if (i == -1) /*Se o produto nao existir na encomenda entao nao se faz nada e sai-se da funcao.*/
            return;
        qtd = obtem_qtd_prod_enc(ide, i);
        altera_qtd_prod(idp, qtd);
        altera_peso_enc(ide, idp, -qtd);
        i_max = obtem_num_prods_enc(ide) - 1; /*Obtem o indice do ultimo produto na lista da encomenda.*/
        /*Se o produto a remover nao for o ultimo na encomenda entao o ultimo e copiado para a posicao i.*/
        if (i != i_max)
            copia(obtem_prod_enc(ide, i), obtem_prod_enc(ide, i_max));
        limpa_prod_enc(ide, i_max);
    }
}

/*Comando C.*/
void custo_enc(){
    int ide, i, num_prods;
    long int custo = 0;
    scanf("%d", &ide);
    if ((verifica_ide_idp(ide, -1, 'C')) == 1)
    {
        num_prods = obtem_num_prods_enc(ide);
        /*Soma progressiva de (preco do produto * quantidade) ao custo da encomenda.*/
        for (i = 0; i < num_prods; i++)
            custo += obtem_preco_prod(obtem_idp_enc(ide, i)) * obtem_qtd_prod_enc(ide, i);
        printf("Custo da encomenda %d %ld.\n", ide, custo);
    }
}

/*Comando p.*/
void altera_preco(){
    int idp, preco;
    scanf("%d:%d", &idp, &preco);
    if ((verifica_ide_idp(-1, idp, 'p')) == 1)
        prod[idp].preco = preco;
}

/*Comando E.*/
void mostra_prod_enc(){
    int ide, idp, i, qtd = 0;
    scanf("%d:%d", &ide, &idp);
    if ((verifica_ide_idp(ide, idp, 'E')) == 0)
        return;
    i = procura_prod_enc(ide, idp);
    /*Obtem-se a quantidade presente caso o produto exista na encomenda. 
    Caso contrario, a quantidade mantem-se 0.*/
    if (i >= 0)
        qtd = obtem_qtd_prod_enc(ide, i);
    printf("%s %d.\n", prod[idp].desc, qtd);
}

/*Comando m.*/
void maior_ocorrencia(){
    int idp, ide, i, ide_final, qtd_max, qtd;
    ide_final = -1;
    qtd_max = 0;
    scanf("%d", &idp);
    if ((verifica_ide_idp(-1, idp, 'm')) == 0)
        return;
    for (ide = 0; ide < ecount; ide++) /*Percorre todas as encomendas.*/
        if ((i = procura_prod_enc(ide, idp)) >= 0)
            /*Caso a quantidade do produto na encomenda seja superior a quantidade maxima, 
            entao a quantidade maxima toma um novo valor.*/
            if ((qtd = obtem_qtd_prod_enc(ide, i)) > qtd_max){
                qtd_max = qtd;
                ide_final = ide;
            }
    if (ide_final >= 0) /*Verifica se o produto se encontra em alguma encomenda.*/
        printf("Maximo produto %d %d %d.\n", idp, ide_final, qtd_max);
}

/*Comando l.*/
void lista_prods(){
    int i;
    printf("Produtos\n");
    if (pcount > 0){
        copia_idps();
        ordena_idps();
        for(i = 0; i < pcount; i++)
             mostra_prod(idps_ord[i], obtem_qtd_prod(idps_ord[i]));
    }
}

/*Comando L.*/
void lista_enc(){
    int ide, i, num_prods;
    scanf("%d", &ide);
    if ((verifica_ide_idp(ide, -1, 'L')) == 1){
        printf("Encomenda %d\n", ide);
        ordena_enc(ide);
        num_prods = obtem_num_prods_enc(ide);
        for (i = 0; i < num_prods; i++)
            mostra_prod(obtem_idp_enc(ide, i), obtem_qtd_prod_enc(ide, i));
    }
}

/****************** Funcoes Auxiliares **********************/

/*Print do produto para o output.*/
void mostra_prod(int i, int qtd){
    printf("* %s %d %d\n", prod[i].desc, obtem_preco_prod(i), qtd);
}

/*Retorna o preco do produto.*/
int obtem_preco_prod(int idp){
    return prod[idp].preco;
}

/*Retorna o peso do produto.*/
int obtem_peso_prod(int idp){
    return prod[idp].peso;
}

/*Retorna a quantidade de produto existente em stock.*/
int obtem_qtd_prod(int idp){
    return prod[idp].qtd;
}

/*Retorna o ponteiro para o vetor que armazena as informacoes do produto na encomenda.*/
int* obtem_prod_enc(int ide, int i){
    return enc[ide].lista[i];
}

/*Retorna o id do produto que se encontra na lista da encomenda.*/
int obtem_idp_enc(int ide, int i){
    return obtem_prod_enc(ide, i)[0];
}

/*Retorna a quantidade de produto que se encontra na lista da encomenda.*/
int obtem_qtd_prod_enc(int ide, int i){
    return obtem_prod_enc(ide, i)[1];
}

/* Retorna o peso total da encomenda.*/
int obtem_peso_enc(int ide){
    return enc[ide].peso;
}

/*Retorna a quantidade total de produtos na encomenda.*/
int obtem_num_prods_enc(int ide){
    return enc[ide].num_prods;
}

/*Altera a quantidade do produto em stock.*/
void altera_qtd_prod(int idp, int qtd){
    prod[idp].qtd += qtd;
}

/*Altera o id do produto na lista da encomenda.*/
void altera_idp_enc(int ide, int i, int idp){
    enc[ide].lista[i][0] = idp;
}

/*Altera a quantidade do produto na lista da encomenda.*/
void altera_qtd_prod_enc(int ide, int i, int qtd){
    if(qtd == 0)
        enc[ide].lista[i][1] = 0;
    else
        enc[ide].lista[i][1] += qtd;
}

/*Altera peso o total da encomenda*/
void altera_peso_enc(int ide, int idp, int qtd){
    enc[ide].peso += obtem_peso_prod(idp) * qtd;
}

/*Altera o numero total de produtos na encomenda.*/
void altera_num_prods_enc(int ide, int qtd){
    enc[ide].num_prods += qtd;
}

/*Adiciona um produto a lista da encomenda e retorna a sua posicao na mesma*/
int cria_prod_enc(int ide, int idp){
    int i = obtem_num_prods_enc(ide); /*Obtem o indice vazio.*/
    altera_idp_enc(ide, i, idp); /*Copia o idp do produto para o indice vazio.*/
    altera_num_prods_enc(ide, 1); /*Aumenta por 1 o numero de produtos na encomenda.*/
    return i;
}

/*Pesquisa o indice na lista da encomenda onde se encontra o id do produto. 
Se encontrar retorna i, caso contrario retorna -1.*/
int procura_prod_enc(int ide, int idp){
    int i, num_prods = obtem_num_prods_enc(ide);
    /*Percorre todos os id's dos produtos ate encontrar (se encontrar) o idp.*/
    for(i = 0; obtem_idp_enc(ide, i) != idp && i < num_prods; i++);
    /*Se i for igual ao numero de produtos entao significa que percorreu todos e nao encontrou o produto.*/
    if (i == num_prods)
        return -1;
    return i;
}

/*Limpa os dados do produto na encomenda.*/
void limpa_prod_enc(int ide, int i){
    altera_idp_enc(ide, i, 0);
    altera_qtd_prod_enc(ide, i, 0);
    altera_num_prods_enc(ide, -1);
}

/*Adiciona a idps_ord os novos produtos que foram adicionados a lista de produtos desde a ultima ordenacao de lista.*/
void copia_idps(){
    static int i; /*Guarda sempre o primeiro indice a partir do qual os produtos nao estao organizados.*/
    for(;i < pcount; i++) /*Copia todos os id's dos novos produtos.*/
        idps_ord[i] = i;
}

/*Ordena os id's dos produtos em <idps_ord> pela ordem crescente de preco, recorrendo ao Insertion Sort.*/
void ordena_idps(){
    int i, j, id_aux, ultimo = pcount - 1;
    for (i = 1; i <= ultimo; i++)
        if (menor_preco(idps_ord[i], idps_ord[i-1])){ /*Compara o preco do produto i com o produto anterior.*/
            id_aux = idps_ord[i]; /*Guarda, em id_aux, o id do produto*/
            j = i - 1;
            /*Empurra a lista para a direita enquanto o preco do produto id_aux for menor que o de j.*/
            do{
                idps_ord[j+1] = idps_ord[j];
                j--;
            } while (j >= 0 && menor_preco(id_aux, idps_ord[j]));
            idps_ord[j+1] = id_aux; /*No final, guarda o id_aux no indice organizado correspondente*/
        }
}

/*Compara os precos de dois produtos. Se o primeiro for menor retorna 1.
Se o preco de ambos for igual mas o  id do primeiro for menor que o do segundo, retorna 1.
Se nao for nenhum dos anteriores, retorna 0.*/
int menor_preco(int i, int j){
    if (obtem_preco_prod(i) < obtem_preco_prod(j))
        return 1;
    if (obtem_preco_prod(i) == obtem_preco_prod(j))
        return i < j;
    return 0;
}

/*Ordena-se, os produtos da lista da encomenda por ordem alfabetica. Recorre-se ao Insertion Sort*/
void ordena_enc(int ide){
    /* O primeiro indice de aux guarda o id do produto e o segundo guarda a sua quantidade.*/
    int i, j, aux[DADOS], ultimo = obtem_num_prods_enc(ide) - 1;
    for (i = 1; i <= ultimo; i++)
        /**Verificacao que previne fazer copia para aux, desnecessariamente*/
        if (menor_desc(obtem_idp_enc(ide, i), obtem_idp_enc(ide, i - 1)) < 0){
            copia(aux, obtem_prod_enc(ide, i)); /*Guarda, em aux, o id e a quantidade do produto.*/
            j = i - 1;
            /*Empurra a lista da encomenda para a direita enquanto a descricao 
            do produto guardado em aux for menor do que a do produto em j.*/
            do{
                copia(obtem_prod_enc(ide, j+1), obtem_prod_enc(ide, j));
                j--;
            } while(j >= 0 && menor_desc(aux[0], obtem_idp_enc(ide, j)) < 0);
            copia(obtem_prod_enc(ide, j+1), aux);
        }
}

/*Compara a descricao dos dois produtos. 
Se a primeira for alfabeticamente menor entao retorna 1. Caso contrario retorna 0.*/
int menor_desc(int i, int j){
    return strcmp(prod[i].desc, prod[j].desc);
}

/*Verifica se as quantidades de produto a adicionar (A) ou remover (r) sao validas.
Se alguma das condicoes nao for respeitada entao retorna 0 e o erro correspondente. Caso contrario retorna 1.*/
int verifica_quantidades(int ide, int idp, int qtd, char cmd){
    /*Se a quantidade a remover ao produto for menor do que a ja existente entao retorna o erro correspondente ao comando.*/
    if (obtem_qtd_prod(idp) < qtd){
        switch (cmd){
            case 'A':
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                break;
            case 'r':
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
                break;
        }
        return 0;
    }
    /*Se, no caso de 'A', a soma do produto a encomenda resulta no peso superior ao limite (200), entao retorna o erro*/
    if (cmd == 'A' && (obtem_peso_enc(ide) + qtd * obtem_peso_prod(idp)) > MAXP){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return 0;
    }
    return 1;
} 

/*Verifica se id's dos produtos e das encomendas existem. Cada comando tem a sua mensagem de erro especifica.
Caso algum id nao existor entao retorna 0 e o erro correspondente. Caso contrario retorna 1.*/
int verifica_ide_idp(int ide, int idp, char cmd){
    if (ide >= ecount){ /*Se o id da encomenda nao existir entao retorna o erro correspondente ao comando.*/
        switch (cmd){
            case 'A':
                printf("Impossivel adicionar produto %d a encomenda %d.", idp, ide);
                break;
            case 'R':
                printf("Impossivel remover produto %d a encomenda %d.", idp, ide);
                break;
            case 'C':
                printf("Impossivel calcular custo da encomenda %d.", ide);
                break;
            case 'E': /*mensagem do comando E e L sao iguais*/
            case 'L':
                printf("Impossivel listar encomenda %d.", ide);
                break;
        }
        printf(" Encomenda inexistente.\n");
        return 0;
    }
    if (idp >= pcount){ /*Se o id do produto nao existir entao retorna o erro correspondente ao comando.*/
        switch (cmd){
            case 'q':
                printf("Impossivel adicionar produto %d ao stock.", idp);
                break;
            case 'A':
                printf("Impossivel adicionar produto %d a encomenda %d.", idp, ide);
                break;
            case 'r':
                printf("Impossivel remover stock do produto %d.", idp);
                break;
            case 'R':
                printf("Impossivel remover produto %d a encomenda %d.", idp, ide);
                break;
            case 'p':
                printf("Impossivel alterar preco do produto %d.", idp);
                break;
            case 'E':
                printf("Impossivel listar produto %d.", idp);
                break;
            case 'm':
                printf("Impossivel listar maximo do produto %d.", idp);
                break;
        }
        printf(" Produto inexistente.\n");
        return 0;
    }
    return 1;
}