#ifndef __NODE_H__
#define __NODE_H__

template <class T> class Node{
    private:
        T data;
        Node<T>* next;
        Node<T>* prev;

    public:

        /**
         *  @brief  Constructor of the Node class
         *  @param  data the data to be assigned to the node -> T
         *  @return the node itself -> Node<T> object
        **/
        Node(T data):
            data(data),
            next(nullptr),
            prev(nullptr)
        {}

        /**
         *  @brief  A function that gives the data of the node
         *  @return The data of the node -> T
        **/
        T get_node_data();

        /**
         *  @brief  Assigns the data to the node
         *  @param  data the data to be assigned -> T
        **/
        void set_node_data(T data);

        /**
         *  @brief  A function that gives the next node
         *  @return A pointer to the next node -> Node<T>*
        **/
        Node<T>* get_next();

        /**
         *  @brief  A function that gives the previous node
         *  @return A pointer to the previous node -> Node<T>*
        **/
        Node<T>* get_prev();

        /**
         *  @brief  Assigns the next node
         *  @param  sig the next node -> Node<T>*
        **/
        void set_next(Node<T>* sig);

        /**
         *  @brief  Assigns the previous node
         *  @param  prev the previous node -> Node<T>*
        **/
        void set_prev(Node<T>* prev);
};


#endif