#include "../List.h"

template <class T> List<T>::~List() {
	Node<T>* destructor = this->first;
	while(this->get_size() > 0){
		this->first = this->first->next();
		delete destructor;
		destructor = this->first;
		this->size --;
	}
} 

template <class T> void List<T>::assign(T data){
	this->iterator->setNData(data);
}

template <class T> void List<T>::iterate(Iteration_type iteration){
    switch(iteration){
        case NEXT:
            do{
                if(this->iterator->next() != NULL){
                    this->iterator = this->iterator->next();
                    this->iteration++;
                }
            } while(iteration == END && this->iterator->next() != NULL);
            break;

        case PREV:
            if(this->iterator->prev() != NULL){
                this->iterator = this->iterator->prev();
                this->iteration--;
            }
            break;
    }
}

template <class T> void List<T>::reset_iterator() {
	this->iterator = this->first;
	this->iteration = 0;
}

template <class T> Node<T>* List<T>::get_node() {
	return this->iterator;
}

template <class T> T List<T>::get_list_data(int x) {
	go_to_node(x);
	return this->iterator->get_node_data();
}

template <class T> void List<T>::add(T data) {
	Node<T>* last_node = new Node<T>(data);
	iterate(END);
	if(this->get_size() == 0){
		this->first = last_node;
		this->iterator = this->first;
	} else {
		last_node->set_prev(this->iterator);
		this->iterator->set_next(last_node);
	}
	this->size++;
}

template <class T> int List<T>::get_iteration() {
	return this->iteration;
}

template <class T> int List<T>::get_size() {
	return this->size;
}

template <class T> void List<T>::go_to_node(int x){
    if(x >= this->get_size() || x < 0){
        std::cerr << "Node out of range" << std::endl;
        return;
    } else if (x != iteration){
        if(this->get_iteration() / 2 < x){
            this->reset_iterator();
        }

        Iteration_type direction = (x > this->get_iteration()) ? NEXT : PREV;

        for(int i = this->get_iteration(); (direction == NEXT) ? (i < x) : (i > x); (direction == NEXT) ? i++ : i--){
            this->iterate(direction);
        }
    }
}