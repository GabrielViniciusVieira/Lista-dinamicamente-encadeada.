#include <iostream>
#include <vector>
using namespace std;
template <class T> class Lista {
private:
    template <class TT> class Celula {
    public:
        Celula<TT> *prox;
        TT valor;

        Celula(TT v) {
            this->valor = v;
            prox = nullptr;
        }
    };
    int tamanho;
    Celula<T> *inicio;
    Celula<T> *fim;
public:
    Lista () {
        inicio = fim = nullptr;
        tamanho = 0;
    }
    ~Lista () {
        Celula<T> *aux;
        while(inicio != nullptr) {
            aux=inicio;
            inicio = inicio->prox;
            delete aux;
        }
    }
    int getTamanho() {
        return tamanho;
    }
    bool inserir(const int& indice, const T &valor) {
        int i = 0;
        Celula<T>* aux = this->inicio;
        Celula<T>* anterior = nullptr;
        while(aux != nullptr && i != indice) {
            anterior = aux;
            aux = aux->prox;
            i++;
        }
        if(aux == nullptr) {
            if(i == indice) {
                return (this->inserirnofim(valor));
            } else {
                cout << "Posicao Invalida!" << endl;
                return false;
            }
        }
        Celula<T>* v = new Celula<T>(valor);
        v->prox = aux;
        ++tamanho;
        if(anterior == nullptr) {
            inicio = v;
        } else {
            anterior->prox = v;
        }
        return true;
    }
    bool inserirnoinicio(const T &valor) {
        if(this->inicio==nullptr) { // está vazia
            this->inicio = new Celula<T>(valor);
            this->fim = this->inicio;
        } else { // já tem elementos
            Celula<T> * aux = new Celula<T>(valor);
            aux->prox = inicio;
            this->inicio = aux;
        }
        ++tamanho;
        return true;
    }
    bool inserirnofim(const T &valor) {
        if(this->fim == nullptr ) {
            this->inicio = new Celula<T>(valor);
            this->fim = this->inicio;
        } else {
            this->fim->prox = new Celula<T>(valor);
            this->fim = this->fim->prox;
        }
        ++tamanho;
        return true;
    }
    bool excluir (const int& indice) {
        int i = 0;
        Celula<T>* anterior = nullptr;
        Celula<T>* aux = this->inicio;
        while(aux != nullptr && i != indice) {
            anterior = aux;
            aux = aux->prox;
            i++;
        }
        if(aux == nullptr) {
            cout << "Não existe elemento nessa posicao!" << endl;
            return false;
        }
        if(anterior == nullptr) {
            this->inicio = aux->prox;
        } else {
            anterior->prox = aux->prox;
            if(aux->prox == nullptr) {
                this->fim = anterior;
            }
        }
        delete aux;
        return true;
    }
    bool excluirdoinicio(void) {
        if(this->inicio==nullptr) {
            return false;
        } else {
            Celula<T> *aux;
            aux = this->inicio;
            this->inicio = this->inicio->prox;
            delete aux;
            this->tamanho--;
            return true;
        }
    }
    bool excluirdofim(void) {
        if(this->inicio == nullptr) {
            return false;
        } else {
            if(this->inicio->prox == nullptr) {//só tem um elemento!
                delete this->inicio;
                this->inicio = this->fim = nullptr;
            } else {
                Celula<T> *aux=this->inicio;
                while(aux->prox->prox!= nullptr){
                    // equivalente a: while(aux->prox!=this->fim) {
                    aux=aux->prox;
                }
                delete this->fim;
                this->fim = aux;
            }
            this->tamanho--;
            return true;
        }
    }
    void mostrar() {
        Celula<T> *aux = this->inicio;
        while(aux!=nullptr) {
            cout << aux->valor << " ";
            aux=aux->prox;
        }
        cout << endl;
    }
};

int main() {
    Lista<int> L1;
    L1.inserirnofim(10);
    L1.inserirnofim(4);
    L1.inserirnofim(22);
    L1.inserirnofim(13);
    L1.mostrar();
    L1.inserir(2, 7);
    L1.mostrar();
    int indice;
    while(indice > -1) {
        cout << "Digite o indice: ";
        cin >> indice;
        L1.excluir(indice);
        cout << "Lista: ";
        L1.mostrar();
    }
}