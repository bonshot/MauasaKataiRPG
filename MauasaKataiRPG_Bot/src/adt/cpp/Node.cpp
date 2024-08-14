#include "../Node.h"

template <class T> T Node<T>::get_node_data(){
    return this->data;
}

template <class T> void Node<T>::set_node_data(T data){
    this->data = data;
}

template <class T> Node<T>* Node<T>::get_next(){
    return this->next;
}

template <class T> Node<T>* Node<T>::get_prev(){
    return this->prev;
}

template <class T> void Node<T>::set_next(Node<T>* next) {
    this->next = next;
}

template <class T> void Node<T>::set_prev(Node<T>* prev) {
    this->prev = prev;
}