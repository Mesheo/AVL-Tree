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
        //  VAO GIRAR MEUS NOS 😥😣😣
        void RotacaoRR(No* no){
            No* novoNo;
            novoNo = no->esq;
            novoNo->dir = no;
            no->altura = maiorValor(altura(no->esq), altura(no->dir));
            no = novoNo;
        }

        void RotacaoLL(No* raiz){
            No* no;
            no = raiz->dir;
            raiz->dir = no->esq;
            no->esq = raiz;
            raiz->altura = maiorValor(altura(raiz->esq), altura(raiz->dir));
            raiz = no;
        }

        No* rotacaoDir(No* no){
            No* novoNo = no->esq;
            no->esq = novoNo->dir;
            novoNo->dir = no;
            no->altura = 1 + maiorValor(altura(no->esq), altura(no->dir));
            novoNo->altura = 1 + maiorValor(altura(novoNo->esq), altura(novoNo->dir));
            return novoNo;
        }

        No* rotacaoEsq(No * no){
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

        No* inserirNaArvore(No* raiz, int chave){
            // Se for NULO = arvore vazia crio um novo No
            if (raiz == NULL){raiz = new No(chave);}

            // Se for MENOR que a raiz atual, insiro (recursao) no filho a esquerda 
            else if (chave < raiz->chave){
                raiz->esq = inserirNaArvore(raiz->esq, chave);}

            // Se for MAIOR que a raiz atual, insiro (recursao) no filho a direita
            else if (chave > raiz->chave){
                raiz->dir = inserirNaArvore(raiz->dir, chave);}

        
            //  🔥🔥 AVLZAMENTO 🔥🔥
            // Para uma arovre ser AVL seus nós precisam ter fator de balanceamento entre -1 e 1
            
            // caso de ROTAÇAO SIMPLES A ESQUERDA
            if (fator_balanceamento(raiz) < -1){ //desbalanceamento pra direita
                if (fator_balanceamento(raiz->dir) <= -1){ //subArvore direita tambem desbalanceada nessa direcao
                    printf("\nReta tendendo ao lado direito... RSE executada no %d(%d)", raiz->chave, fator_balanceamento(raiz));
                    raiz = rotacaoEsq(raiz);
                } 
            }
                
            // CASO DE ROTACAO SIMPLES A DIREITA
            if (fator_balanceamento(raiz) > 1){ // desbalanceamento pra esquerda
                if (fator_balanceamento(raiz->esq) >= 1){ //subArvore esquerda tambem desbalanceada nessa direcao
                    printf("\nReta tendendo ao lado esquerdo... RSD executada no %d(%d)", raiz->chave, fator_balanceamento(raiz));
                    raiz = rotacaoDir(raiz);
                }
            }
            // else if (desequilibrio > 1){ //subArvore a esquerda ta maior
            //     if (fator_balanceamento(no->dir) > 0){ //subArvore esquerda tambem maior, portanto uma reta
            //         printf("\nReta tendendo ao lado esquerdo... RSD executada no %d(%d)", no->chave, fb(no));
            //         no = rotacaoDir(no);
            //     } 
            // }
            // if (desequilibrio > 1){
            //     if(chave < no->esq->chave){ // comparando com o descendente esquerdo
            //         printf("\nInsercao do %d causou desequilibrio... RSD executada.", chave);
            //         return rotacaoDir(no); // Rotação direita
            //     }else{
            //         printf("\nInsercao do %d causou desequilibrio... RDE executada.", chave);
            //         no->esq = rotacaoEsq(no->esq); // Rotacao dupla a esquerda
            //         return rotacaoDir(no);
            //     }
            // }else if (desequilibrio < -1){
            //     if (chave < no->dir->chave){ // comparando com o descendente a direita
            //         printf("\nInsercao do %d causou desequilibrio. RSE executada", chave);
            //         return rotacaoEsq(no);
            //     }else{
            //         printf("\nInsercao do %d causou desequilibrio. RDD executada", chave);
            //         no->dir = rotacaoDir(no); // Rotacao dupla a direita
            //         return rotacaoEsq(no);
            //     }
            // }
            return raiz;
        }

        void emOrdem(No* no){
            if(no!=NULL){
                emOrdem(no->esq);
                cout << no->chave << "(" << fator_balanceamento(no) << ")" << " ";
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
        
        int fator_balanceamento(No* no){
            if (no == NULL) return 0;
            else{
                return altura(no->esq) - altura(no->dir);
            }
        }
};

int main(){
    Arvore_AVL arv;
    arv.inserir(15);
    arv.inserir(27);
    arv.inserir(49);
    arv.inserir(10);
    arv.inserir(8);
    arv.inserir(49);

    cout << "\n\nPercorrendo em ordem" << endl;
    arv.emOrdem(arv.raiz);
}