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
                int fator_balanceamento;
                int chave;
                No *esq;
                No *dir;

                No(int chave){
                    this->chave=chave;
                    altura = 1;
                    this->fator_balanceamento = (this->esq->altura) - (this->dir->altura);
                    esq=NULL;
                    dir=NULL;
                }
        };
        //  VAO GIRAR MEUS NOS 😥😣😣
        No* rotacaoDir(No* no){
            No* novoNo = no->esq;
            no->esq = novoNo->dir;
            novoNo->dir = no;
            no->altura = 1 + maiorValor(altura(no->esq), altura(no->dir));
            novoNo->altura = 1 + maiorValor(altura(novoNo->esq), altura(novoNo->dir));
            return novoNo;
        }

        No * rotacaoEsq(No * no){
            No * novoNo = no->dir;
            no->dir = novoNo->esq;
            novoNo->esq = no;
            no->altura = 1 + maiorValor(altura(no->esq), altura(no->dir));
            novoNo->altura = 1+maiorValor(altura(novoNo->esq), altura(novoNo->dir));
            return novoNo;
        }

        No* raiz = NULL;
        void inserir(int chave){
            printf("\nVoce inseriu %d na arvore", chave);
            raiz = inserirNaArvore(raiz, chave);
        };

        No* inserirNaArvore(No* no, int chave){
            // Se for NULO = arvore vazia crio um novo No
            if (no == NULL){
                no = new No(chave);
                }

            // Se for MENOR qssue o no atual, insiro (recursao) no filho a esquerda 
            else if (chave < no->chave){
                no->esq = inserirNaArvore(no->esq, chave);}

            // Se for MAIOR que o no atual, insiro (recursao) no filho a direita
            else if (chave > no->chave){
                no->dir = inserirNaArvore(no->dir, chave);}

            // Armazenando Altura e Fator de Desequilibrio da inserção atual
            no->altura = 1 + maiorValor(altura(no->esq), altura(no->dir));
            int fator_balanceamento = (no->esq->altura) - (no->dir->altura);
            printf("\nAltura do no %d = %d", no->chave, no->altura);
            printf("\nFB do %d: %d", no->chave, no->fator_balanceamento);
            //  🔥🔥 AVLZAMENTO 🔥🔥
            //  Correção do desiquilibrio através de rotacoes para balancear a arvore (deseq entre -1 e 1)
            if (fator_balanceamento > 1){
                if(chave < no->esq->chave){ // comparando com o descendente esquerdo
                    printf("\nInsercao do %d causou desequilibrio... RSD executada.", chave);
                    return rotacaoDir(no); // Rotação direita
                }else{
                    printf("\nInsercao do %d causou desequilibrio... RDE executada.", chave);
                    no->esq = rotacaoEsq(no->esq); // Rotacao dupla a esquerda
                    return rotacaoDir(no);
                }
            }else if (fator_balanceamento < -1){
                if (chave < no->dir->chave){ // comparando com o descendente a direita
                    printf("\nInsercao do %d causou fator_balanceamento. RSE executada", chave);
                    return rotacaoEsq(no);
                }else{
                    printf("\nInsercao do %d causou desequilibrio. RDD executada", chave);
                    no->dir = rotacaoDir(no); // Rotacao dupla a direita
                    return rotacaoEsq(no);
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
    arv.inserir(15);
    arv.inserir(27);
    arv.inserir(49);
    cout << "\nPercorrendo em ordem: ";
    arv.emOrdem(arv.raiz);
}