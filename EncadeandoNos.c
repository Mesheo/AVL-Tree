#include <stdio.h>
#include <stdlib.h>

typedef struct sNoA {
  int chave;
  struct sNoA* esq;
  struct sNoA* dir;
} Arv;

Arv* insere(Arv *no, int chave){
    // Se o no estiver vazio
    if (no == NULL)
    {
        no = (Arv *) malloc(sizeof(Arv));
        no->chave = chave;
        no->dir = NULL;
        no->esq = NULL;
    } 
    else if (chave < no->chave) {no->esq = insere(no->esq, chave);}
    else if (chave > no->chave) {no->dir = insere(no->dir, chave);}
    else
    {
        printf("Insercao Invalida!"); //Chave já existe
        exit(1);
    }
    
    return no;
}

int main(){

    //Exercício 1
    Arv *arvore1;
    arvore1 = NULL;

    arvore1 = insere(arvore1, 25);
    arvore1 = insere(arvore1, 22);
    arvore1 = insere(arvore1, 40);
    arvore1 = insere(arvore1, 30);
    arvore1 = insere(arvore1, 45);
  
    return 0;
}