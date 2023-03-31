//
//  Node.hpp
//  BFS
//
//  Created by Daniel Fishbein on 3/31/23.
//

#ifndef Node_h
#define Node_h
template<typename T>
class Node
{
public:
    Node<T>* next;
    T data;
    
    Node();
    Node(T);
};

template<typename T>
Node<T>::Node()
{
    next  = nullptr;
}

template<typename T>
Node<T>::Node(T d)
{
    this->data = d;
    next  = nullptr;
}

#endif /* Node_h */
