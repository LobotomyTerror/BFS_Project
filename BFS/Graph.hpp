//
//  Graph.hpp
//  BFS
//
//  Created by Daniel Fishbein on 3/31/23.
//
#include "Node.hpp"
#include <iostream>
#include <chrono>
#ifndef Graph_h
#define Graph_h

using namespace std::chrono;

template<typename T>
class Graph : public Node<T>
{
private:
    int numOfVertices, numOfEdges, size;
    Node<T>* head;
    Node<T>* tail;
    Node<T>** adj;
    
public:
    Graph();
    ~Graph();
    void initGraph(int);
    void createLink(T, T);
    void print(T, T, T, T);
    void BFS(T, int*, int*, int*);
    void enqueue(T);
    void dequeue();
    int getSize();
    Node<T>* getData();
};

template<typename T>
Graph<T>::Graph()
{
    head = tail = nullptr;
    size = 0;
}

template<typename T>
Graph<T>::~Graph()
{
    for (int i = 0; i < numOfVertices; ++i)
        delete adj[i];
    delete[] adj;
}

template<typename T>
void Graph<T>::initGraph(int V)
{
    numOfVertices = V;
    numOfEdges = 0;
    try
    {
        adj = new Node<T>*[V];
        for (int i = 0; i < numOfVertices; ++i)
        {
            adj[i] = new Node<T>();
            adj[i] = nullptr;
        }
    } catch (std::bad_alloc) {
        std::cerr << "Error handling dynamic allocation on line 56 thru 61 in Graph.hpp." << std::endl;
        throw;
    }
}

template<typename T>
void Graph<T>::createLink(T v, T e)
{
    try {
        Node<T>* temp1 = new Node<T>(v);
        Node<T>* temp2 = new Node<T>(e);
        Node<T>* last_node;
        Node<T>* first_node;
        
        if (temp1 == temp2)
        {
            temp1 = temp2;
            adj[v] = temp1;
        }
        else if (adj[v] == nullptr)
        {
            first_node = temp1;
            last_node = temp2;
            first_node->next = last_node;
            adj[v] = first_node;
        }
        else
        {
            first_node = adj[v];
            last_node = first_node->next;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            last_node->next = temp2;
            adj[v] = first_node;
        }
        ++numOfEdges;
    } catch (std::bad_alloc) {
        std::cerr << "Error handling dynamic allocation on lines 74 and 75 in Graph.hpp." << std::endl;
        throw;
    }
}

template<typename T>
Node<T>* Graph<T>::getData()
{
    return this->head;
}

template<typename T>
int Graph<T>::getSize()
{
    return size;
}

template<typename T>
void Graph<T>::enqueue(T d)
{
    try {
        Node<T>* new_node = new Node(d);
        if (tail == nullptr)
        {
            tail = head = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
        ++size;
    } catch (std::bad_alloc) {
        std::cerr << "Error handling dynamic allocation on line 148 in Graph.hpp." << std::endl;
        throw;
    }
    
}

template<typename T>
void Graph<T>::dequeue()
{
    Node<T>* temp = head;
    
    if (head == nullptr)
        return;
    
    head = head->next;
    
    if (head == nullptr)
        tail = nullptr;
    
    --size;
    delete temp;
}

//Breadth-first search to find the shortest path from a
//user-defined source node to a destination node...
template<typename T>
void Graph<T>::BFS(T src, int *pathTo, int *destTo, int *pred)
/*For this to work we need to set a pathTo array, distTo array and an index array
 to store the path from the source node to the destination node
 along with the dist to array to store the edges from the two nodes
 then an index to have the starting node and destination node in the same array to
 loop back through and find the path from dest to src, then we flip it to show the details.*/
{
    int i = 0;
    bool vistedV[numOfVertices];
    Node<T>* next_node;
    Node<T>* curr;
    Node<T>* tempArr[numOfVertices];
    
    for (int i = 0; i < numOfVertices; ++i)
    {
        vistedV[i] = false;
        tempArr[i] = adj[i];
    }
    
    vistedV[src] = true;
    next_node = curr = tempArr[src];
    next_node = next_node->next;
    pathTo[i] = curr->data;
    destTo[curr->data] = 0;
    pred[i] = -1;
    enqueue(curr->data);
    
    while (getSize() != 0)
    {
        while (next_node != nullptr)
        {
            if (vistedV[next_node->data] == false)
            {
                ++i;
                pathTo[i] = next_node->data;                                   //stores the node we are currently at
                pred[i] = curr->data;                                               //predecessor to the node we are currently at
                destTo[next_node->data] = destTo[curr->data] + 1; //sets the arr element to the number edges from the src node
                vistedV[next_node->data] = true;                           //just a check if the node has already been visted
                enqueue(next_node->data);
            }
            next_node = next_node->next;  //advance the node keeping it moving so we
            //can check the if there is any more links to the curr node
        }
        dequeue();
        if ((next_node = getData()) != nullptr) //this gets the data from the head element such that if
            //it is not NULL then we can advance the pointers
        {
            next_node = curr = tempArr[next_node->data];  //as mentioned above also it stops from any bad_access issues
            //if the element in the array goes out of bounds
            next_node = next_node->next;
        }
    }
}


template<typename T>
void Graph<T>::print(T src, T dest_one, T dest_two, T dest_three)
{
    //three arrays pathTo, pred, and distTo
    //these three will be used to store each node,
    //which node is a predecessor of that node, and
    //the number of edges from the src node
    int index = 0;
    //three array declrations
    int pathTo[numOfVertices];
    int distTo[numOfVertices];
    int pred[numOfVertices];
    int tempArr[numOfVertices];
    int Indexone[numOfVertices];
    
    
    for (int i = 0; i < numOfVertices; ++i) //init of the three arrays
    {
        pathTo[i] = 0;
        distTo[i] = 0;
        pred[i] = 0;
        tempArr[i] = 0;
        Indexone[i] = 0;
    }
    
    auto start = high_resolution_clock::now();
    BFS(src, pathTo, distTo, pred);
    auto stop = high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::nanoseconds>(stop - start);
    
    std::cout << "Finding the shortest path took from source: " << src << " took " << duration1.count() << " nanoseconds";
    
    for (int i = 0; i < numOfVertices; ++i)
    {
        if (pathTo[i] == dest_one || pathTo[i] == dest_two || pathTo[i] == dest_three)
        {
            tempArr[index] = pathTo[i];
            index++;
            int pnode = pred[i];
            
            for (int j = i; j >= 0; --j)
            {
                if (pathTo[j] == pnode)
                {
                    if(j == 0) {
                        tempArr[index] = pathTo[j];
                        tempArr[index+1] = -1;
                        index += 2;
                    } else {
                        tempArr[index] = pathTo[j];
                        index++;
                    }
                    pnode = pred[j];
                }
            }
        }
    }
    
    for(int i = 0; i < numOfVertices; i++) {
        if(tempArr[i+1] == 0 && tempArr[i+2] == 0 && tempArr[i+3] == 0) {
            for(int j = i; j >= 0; j--) {
                if(tempArr[j] == -1) {
                    std::cout << '\n';
                    std::cout << "Source: " << tempArr[i-1] << ' ';
                    for (int k = j - 1; k >= 0; --k){
                        if (tempArr[k] == -1 || k == 0){
                            if (tempArr[k + 1] == dest_one || tempArr[k] == dest_one){
                                std::cout << "Destination: " << dest_one << ' ';
                                std::cout << "Distance from source " << distTo[dest_one] << std::endl;
                                break;
                            }
                            if (tempArr[k + 1] == dest_two || tempArr[k] == dest_two){
                                std::cout << "Destination: " << dest_two << ' ';
                                std::cout << "Distance from source " << distTo[dest_two] << std::endl;
                                break;
                            }
                                
                            if (tempArr[k] == dest_three || tempArr[k + 1] == dest_three){
                                std::cout << "Destination: " << dest_three << ' ';
                                std::cout << "Distance from source " << distTo[dest_three] << std::endl;
                                break;
                            }
                        }
                    }
                } else {
                    std::cout << tempArr[j] << ' ';
                }
            }
            break;
        }
    }
    std::cout << '\n';
}

#endif /* Graph_h */
