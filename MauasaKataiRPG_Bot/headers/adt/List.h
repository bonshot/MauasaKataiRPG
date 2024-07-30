#include <iostream>
#include "Nodo.h"
#include "Enums.h"

#ifndef __LIST_H__
#define __LIST_H__

enum Iteration_type {NEXT, PREV, END};

template <class T> class List {
private:
	Node<T>* first;
	Node<T>* iterator;
	int size;
	int iteration;
	
public: 

    /**
     *  @brief  Constructor of the List class
     *  @return List<T> object
    **/
	List();

    /**
     *  @brief  Destructor of the List class
    **/
	~List();

    /**
     *  @brief  moves the iterator to the selected node
     *  @param  x the node number -> int
    **/
	void go_to_node(int x);

    /**
     *  @brief  Iterates in the direction specified, if the direction is END it will iterate until the end of the list
     *  @param  iteration the direction of the iteration that can be NEXT, PREV, END -> Iteration_type
    **/
	void iterate(Iteration_type iteration);

    /**
     *  @brief  Resets the iterator to the first node
    **/
	void reset_iterator();

    /**
     *  @brief  Assigns the data to the node where the iterator is
     *  @param  data the data to be assigned -> T
    **/
	void assign(T data);

    /**
     *  @brief  A function that gives the node in the current iterator position
     *  @return A pointer to the node in the current iterator position -> Node<T>*
    **/
	Node<T>* get_node();

    /**
     *  @brief  A function that gives the data of the node in the current iterator position
     *  @param  x the node number -> int
     *  @return The data of the node in the current iterator position -> T
    **/
	T get_list_data(int x);

    /**
     *  @brief  Adds a new node to the list
     *  @param  data the data inside the node to be added -> T
    **/
	void add(T data);

    /**
     *  @brief  A function that gives the current iteration of the iterator
     *  @return The current iteration of the iterator -> int
    **/
	int get_iteration();

    /**
     *  @brief  A function that gives the size of the list
     *  @return The size of the list -> int
    **/
	int get_size();
};


template <class T> List<T>::List() {
	this->first = NULL;
	this->iterator = this->first;
	this->iteration = 0;
	this->size = 0;
}

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

template <class T> Nodo<T>* List<T>::get_node() {
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
    } else if (x != current_iteration){
        if(this->get_iteration() / 2 < x){
            this->reset_iterator();
        }

        Iteration_type direction = (x > this->get_iteration()) ? NEXT : PREV;

        for(int i = this->get_iteration(); (direction == NEXT) ? (i < x) : (i > x); (direction == NEXT) ? i++ : i--){
            this->iterate(direction);
        }
    }
}

#endif