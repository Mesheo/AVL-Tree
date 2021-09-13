#include <iostream>
using namespace std;

int maiorValor(int a, int b){
    if (a > b) return a;
    else return b;
}

class Arvore_AVL{
    private:
        int numero_secreto = 3;
    public:
        int numero_exposto = 3;

        class No{
            public:
                int altura;
                int chave;
                No *esq;
                No *dir;

                No(int chave){
                    this->chave=chave;
                    altura = 1;
                    esq=NULL;
                    dir=NULL;
                }
        };

        No* raiz = NULL;
        void inserir(int chave){
            raiz = inserirNaArvore(raiz, chave);
        };

        No* inserirNaArvore(No* no, int chave){
            // Se for NULO = arvore vazia crio um novo No
            if (no == NULL){no = new No(chave);}
            // Se for MENOR que o no atual, insiro (recursao) no filho a esquerda 
            else if (chave < no->chave){
                no->esq = inserirNaArvore(no->esq, chave);}
            // Se for MAIOR que o no atual, insiro (recursao) no filho a direita
            else if (chave > no->chave){
                no->dir = inserirNaArvore(no->dir, chave);}

            // Armazenando a altura do No e o balanceamento da arvore
            no->altura = 1 + maiorValor(altura(no->esq), altura(no->dir));
            int desequilibrio = altura(no->esq) - altura(no->dir);

            // 🔥🔥 AVLZAMENTO - BALANCEIAÇÃO 🔥🔥
            // Correção do desiquilibrio para balancear a arvore (deseq entre -1 e 1)
            if (desequilibrio>1){
                if(chave < no->esq->chave){
                    return rotacaoDir(no); // Rotação direita
                }else{
                    no->esq = rotacaoEsq(no->esq); // Rotacao dupla a esquerda
                    return rotacaoDir(no);
                }
            }

            return no;
        }

        void emOrdem(No* no){
            if(no!=NULL){
                emOrdem(no->esq);
                cout << no->chave << " ";
                emOrdem(no->dir);
            }
        };

        int altura(No* no){
            if (no == NULL) return 0;;
                int altura_esq = altura(no->esq);
                int altura_dir = altura(no->dir);
            if (altura_esq > altura_dir){
                return altura_esq + 1;}
            else{
                return altura_dir + 1;}
        }
};

int main(){
    Arvore_AVL arv;
    arv.inserir(6);
    arv.inserir(4);
    arv.inserir(9);
    arv.inserir(1);
    arv.inserir(7);
    cout << "Percorrendo em ordem" << endl;
    arv.emOrdem(arv.raiz);
}