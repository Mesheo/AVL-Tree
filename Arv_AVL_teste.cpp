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
            
            // CASOS DE ROTACOES A ESQUERDA ↩
            if (fator_balanceamento(raiz) < -1){ //desbalanceamento pra direita
                // caso de ROTACAO SIMPLES a ESQUERDA
                if (fator_balanceamento(raiz->dir) <= -1){ //subArvore direita desbalanceada pra direita = RETA
                    printf("\n***DESEQUILIBRIO (reta a direita) encontrado em %d(%d). RSE executada***", raiz->chave, fator_balanceamento(raiz));
                    raiz = rotacaoEsq(raiz);
                }
                // caso de ROTACAO DUPLA a ESQUERDA
                if (fator_balanceamento(raiz->dir) > 0){ // subArvore direita desbalanceada pra esquerda = JOELHO
                    printf("\n***DESEQUILIBRIO (joelho direita-esquerda) encontrado em %d(%d) RDE executada***", raiz->dir->chave, fator_balanceamento(raiz->dir)); 
                    raiz->dir = rotacaoDir(raiz->dir); // rotacao simples a direita
                    raiz = rotacaoEsq(raiz);
                } 
            }   

            // CASOS DE ROTACOES A DIREITA ↪
            if (fator_balanceamento(raiz) > 1){ // desbalanceamento pra esquerda
                // caso de ROTACAO SIMPLES a DIREITA
                if (fator_balanceamento(raiz->esq) >= 1){ //subArvore esquerda desbalanceada pra esquerda = RETA
                    printf("\n***DESEQUILIBRIO (reta a esquerda) encontrado em %d(%d). RSD executada***", raiz->chave, fator_balanceamento(raiz));
                    raiz = rotacaoDir(raiz);
                }
                // caso de rotacao DUPLA A DIREITA
                if (fator_balanceamento(raiz->esq) < 0){ //subArvore esquerda desbalanceada pra direita = JOELHO
                    printf("\n***DESEQUILIBRIO (joelho esquerda-direita) detectado em %d(%d). RDD executada***", raiz->esq->chave, fator_balanceamento(raiz->esq));
                    raiz->esq = rotacaoEsq(raiz->esq);
                    raiz = rotacaoDir(raiz);
                    // raiz->esq = rotacaoEsq(raiz->esq); // rotacao simples a esquerda no filho
                    // raiz = rotacaoDir(raiz); // rotacao simples a direita no pai
                }
            }
            return raiz;
        };

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
    // deu ruim = RSE
    arv.inserir(10);
    arv.inserir(8);
    // deu ruim = RSD
    arv.inserir(67);
    arv.inserir(59);
    // deu ruim = RDE
    arv.inserir(9);
    arv.inserir(13);
    arv.inserir(20);
    arv.inserir(14);
    // deu ruim = RDD

    cout << "\n\nPercurso em ordem da Árvore" << endl;
    arv.emOrdem(arv.raiz);
}