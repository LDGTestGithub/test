#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>

//! Classe LinkedList
/*! A classe implementa a estrutura de lista encadeada, onde o tamanho é dinâmico, e cada elemento (ou node) possui um dado e um ponteiro para o próximo elemento. */
class LinkedList {
public:

    //! Construtor da Classe
    /*! Método construtor padrão da classe LinkedList. */
    LinkedList() {
        size_ = 0;
        head = new Node(0u);
       // head->next(NULL);
    }

    //! Destrutor
    ~LinkedList() {
        clear();
        delete(head);
    }

    //! Clear
    /*! Remove todos os elementos da lista encadeada. */
    void clear(){
        while (!empty()) {
            pop_front();
        }
    }

    //! Push Back
    /*! Insere elementos no fim da lista encadeada.
        \param data um dado para ser inserido na lista.
    */
    void push_back(const T& data){
        insert(data, size());
    }

    //! Push Front
    /*! Insere elementos no início da lista encadeada;
        \param data um dado para ser inserido na lista.
    */
    void push_front(const T& data) { // inserir no início
        Node* novo;
        novo = new Node(data);

        if (novo == NULL) {
            throw std::out_of_range("Erro Lista Cheia!");
        } else {
            if(size() == 0) {
                head->next(novo);
                size_++;
            } else {
                novo->next(head->next());
                head->next(novo);
                size_++;
            }
        }
    }

    //! Insert
    /*! Insere elementos na posição index da lista encadeada.
        \param data o dado para ser inserido na lista.
        \param index a posição da lista que deve ser inserido o dado.
    */
    void insert(const T& data, std::size_t index) {
        Node *novo;
        Node *anterior;

        if (index < 0 || index > size_) {
            throw std::out_of_range("Erro Posição!");
        } else {

            if (index == 0) {
                push_front(data);
            } else {
                novo = new Node(data);

                if (novo == NULL) {
                    throw std::out_of_range("Erro Lista Cheia!");

                } else {
                    anterior = head->next();

                    for (auto i = 0u; i < index - 1; ++i) {
                        anterior = anterior->next();
                    }

                    novo->next(anterior->next());
                    anterior->next(novo);
                    size_++;
                }
            }
        }
    }

    //! Insert Sorted
    /*! Insere um elemento em uma posição ordenada na lista.
        /param data o dado a ser inserido na lista.
    */
    void insert_sorted(const T& data) {
        Node* atual;
        auto posicao = 0;

        if (empty()) {
            push_front(data);
        } else {
            atual = head->next();

            while (atual->next() != NULL && data->getIncidencia() > atual->data()->getIncidencia()) {
                atual = atual->next();
                posicao++;
            }

            if (data->getIncidencia() > atual->data()->getIncidencia()) {
                insert(data, posicao+1);
            } else {
                insert(data, posicao);
            }
        }
    }

    //! At
    /*! Retorna o elemento de posição informada pelo parâmetro index, verificando se o parâmetro está dentro dos limites da lista.
        /param index a posição do elemento que será retornado.
        /return um dado do tipo T que está na posição index da lista.
    */
    T& at(std::size_t index) {
        Node* anterior = head;

        if (empty()) {
            throw std::out_of_range("Erro Lista Vazia!");
        } else {
            if (index < 0 || index > size_) {
                throw std::out_of_range("ERRO");
            } else {

                anterior = head->next();

                for (auto i = 0; i < index; ++i) {
                    anterior = anterior->next();
                }

                return anterior->data();
            }
        }
    }

    //! Pop
    /*! Retira o elemento da posição informada pelo parâmetro index.
        /param index a posição na lista do elemento a ser retirado.
        /return o elemento que foi removido, do tipo T.
    */
    T pop(std::size_t index) {// retirar da posição
        Node *atual;
        Node *eliminar;
        T volta = 0;

        if (index < 0 || index > size_ -1) {
            throw std::out_of_range("Erro Posição!");
        } else {
            if (index == 0) {
                pop_front();
            } else {
                atual = head->next();

                for (auto i = 0u; i < index - 1; ++i) {
                    atual = atual->next();
                }

                eliminar = atual->next();
                volta = eliminar->data();

                if (index < size() - 1) {
                    atual->next(eliminar->next());
                }

                size_--;
                delete(eliminar);
                return volta;
            }
        }

        return volta;
    }

    //! Pop Back
    /*! Remove um elemento do final da lista.
        /return o elemento que foi removido, do tipo T.
    */
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Erro Lista Vazia!");
        }
        return pop(size()-1);
    }

    //! Pop Front
    /*! Remove um elemento do início da lista.
        /return o elemento que foi removido, do tipo T.
    */
    T pop_front() {
        Node* saiu;
        T volta;

        if (empty()) {
            throw std::out_of_range("Erro Lista Vazia!");
        } else {
            saiu = head->next();
            volta = saiu->data();
            if (size_ > 0) {
                head->next(saiu->next());
            }
            size_--;
            delete(saiu);
            return volta;
        }
    }

    //! Remove
    /*! Remove um elemento específico.
        /param data conteúdo do elemento a ser removido.
    */
    void remove(const T& data) {
        Node *atual = head->next();
        Node *anterior = head;

        while (atual->data() != data) {
            anterior = anterior->next();
            atual = atual->next();
        }

        anterior->next(atual->next());
        delete(atual);
        size_--;
     }

    //! Empty
    /*! Verifica se a lista está vazia.
        /return um valor do tipo bool.
    */
    bool empty() const { // lista vazia
        return (size_ == 0);
    }

    //! Contains
    /*! Verifica se o parâmetro data está na lista.
        /param data o dado que será verificado se está contido na lista.
        /return um valor do tipo bool.
    */
    bool contains(const T& data) const {
        Node *anterior = head;

        for (auto i = 0u; i < size_; ++i) {
            anterior = anterior->next();
            if (anterior->data() == data) {
                return true;
            }
        }

        return false;
    }

    //! Find
    /*! Procura o dado dentro da lista, e retorna sua posição caso esteja.
        /param data dado a ser procurado.
        /return a posição deste dado dentro da lista.
    */
    std::size_t find(const T& data) const {
        auto i = 0u;
        Node* anterior = head->next();

        while (anterior->data() != data && i < size()) {
            ++i;

            if (i < size())
                anterior = anterior->next();
        }
        return i;
    }

    //! Size
    /*! Retorna o tamanho da lista. */
    std::size_t size() const {
        return size_;
    }

private:

    //! Classe Node
    /*! A classe implementa o elemento da lista encadeada, onde cada node
    possui um atributo de dado e um ponteiro para o próximo elemento. */
    class Node { // Elemento
    public:

        //! Construtor
        /*! Método construtor da classe Node com um parâmetro de dados.
            /param data dado a ser inserido no Node.
        */
        Node(const T& data):
            data_{data}
        {}

        //! Construtor
        /*! Método construtor da classe Node com dois parâmetros.
            /param data dado a ser inserido no Node.
            /param next ponteiro para o próximo Node.
        */
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        //! Data
        /*! Método getter de um Node.
            /return o dado do elemento.
        */
        T& data() {
            return data_;
        }

        //! Data Const
        /*! Método getter de um Node, onde o dado retornado não será alterado.
            /return o dado do elemento.
        */
        const T& data() const {
            return data_;
        }

        //! Next
        /*! Método getter de um Node.
            /return o ponteiro para o próximo elemento.
        */
        Node* next() { // getter: próximo
            return next_;
        }

        //! Next
        /*! Método getter de um Node, onde o ponteiro retornado não será alterado.
            /return o ponteiro para o próximo elemento.
        */
        const Node* next() const {
            return next_;
        }

        //! Next
        /*! Método setter de um Node.
            /param um ponteiro, que será o indicador do próximo elemento.
        */
        void next(Node* node) { // setter: próximo
            next_ = node;
        }

    private:
        T data_; /**< Declaração do dado, do tipo T. */
        Node* next_{nullptr}; /**< Declaração do ponteiro para o próximo Node. */
    };

    //! End
    /*! Retorna o último elemento da lista.
        /return o ponteiro do último Node da lista.
    */
    Node* end() { // último nodo da lista
        auto it = head;
        for (auto i = 0u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }


    Node* head{nullptr}; /**< Declaração da cabeça da lista. */
    std::size_t size_{0u}; /**< Declaração do tamanho da lista. */

};

}

#endif
