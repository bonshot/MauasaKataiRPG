#include <iostream>
#include "Node.h"

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
	List():
        first(NULL),
        iterator(first),
        size(0),
        iteration(0)
    {}
        

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

#endif