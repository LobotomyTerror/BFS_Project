#include <iostream>

template<typename T>
class Node
{
public:
    Node<T>* next;
    Node<T>* prev;
    T data;
    
    Node();
    Node(T);
};

template<typename T>
Node<T>::Node()
{
    next = prev = nullptr;
}

template<typename T>
Node<T>::Node(T d)
{
    this->data = d;
    next = prev = nullptr;
}

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
    void initGraph(int V);
    void createLink(T src, T dest);
    void print();
    void BFS(Graph, T, T);
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
    adj = new Node<T>*[V];
    for (int i = 0; i < numOfVertices; ++i)
    {
        adj[i] = new Node<T>();
        adj[i] = nullptr;
    }
}

template<typename T>
void Graph<T>::createLink(T v, T e)
{
    Node<T>* temp1 = new Node<T>(v);
    Node<T>* temp2 = new Node<T>(e);
    Node<T>* last_node;
    
    if (temp1->data == temp2->data)
    {
        adj[v] = temp1;
        last_node = temp2;
        adj[v] = last_node;
    }
    else if (adj[v] == nullptr)
    {
        adj[v] = temp1;
        last_node = temp2;
        adj[v]->next = last_node;
        last_node->prev = adj[v];
    }
    else
    {
        last_node->next = temp2;
        last_node = last_node->next;
        last_node->prev = adj[v];
    }
    ++numOfEdges;
}

template<typename T>
int Graph<T>::getSize()
{
    return size;
}

template<typename T>
void Graph<T>::enqueue(T d)
{
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
}

template<typename T>
void Graph<T>::dequeue()
{
    Node<T>* temp = head;
    
    if (head == nullptr)
        return;
    
    head = head->next;
    head->prev = nullptr;
    
    if (head == nullptr)
        tail = nullptr;
    
    --size;
    delete temp;
}

template<typename T>
Node<T>* Graph<T>::getData()
{
    return this->head;
}

template<typename T>
void Graph<T>::BFS(Graph G, T src, T dest)
{
    bool vistedV[numOfVertices];
    Node<T>* next_node;
    
    for (int i = 0; i < numOfVertices; ++i)
        vistedV[i] = false;
    
    vistedV[src] = true;
    G.enqueue(src);
    next_node = adj[src];
    next_node = next_node->next;
    
    while (G.getSize() != 0)
    {
       if (next_node == nullptr || vistedV[next_node->data] == false)
        {
            if (next_node != nullptr)
            {
                vistedV[next_node->data] = true;
                G.enqueue(next_node->data);
                next_node = next_node->next;
            }
            else
            {
                G.dequeue();
                next_node = G.getData();
                next_node = adj[next_node->data];
                next_node = next_node->next;
            }
        }
        else
            next_node = next_node->next;
}

template<typename T>
void Graph<T>::print()
{
    for (int i = 0; i < numOfVertices; ++i)
    {
        std::cout << i << "->";
        for (int j = 0; adj[i]->next != nullptr; ++j)
        {
            std::cout << adj[i]->next->data << "->";
            adj[i] = adj[i]->next;
        }
        std::cout << "NULL";
        std::cout << '\n';
    }
    std::cout << numOfEdges << '\n';
}

int main(int argc, const char * argv[])
{
    int V;
    Graph<int> G;
    std::cout << "Enter the total amount of vertices: ";
    std::cin >> V;

    G.initGraph(V);
    
    G.createLink(0, 8);
    G.createLink(1, 3);
    G.createLink(2, 0);
    G.createLink(3, 1);
    G.createLink(3, 22);
    G.createLink(3, 27);
    G.createLink(4, 21);
    G.createLink(5, 4);
    G.createLink(5, 21);
    G.createLink(5, 6);
    G.createLink(6, 4);
    G.createLink(6, 7);
    G.createLink(7, 1);
    G.createLink(7, 8);
    G.createLink(7, 6);
    G.createLink(8, 7);
    G.createLink(8, 12);
    G.createLink(9, 12);
    G.createLink(10, 12);
    G.createLink(11, 10);
    G.createLink(12, 9);
    G.createLink(12, 10);
    G.createLink(13, 11);
    G.createLink(13, 24);
    G.createLink(13, 0);
    G.createLink(14, 17);
    G.createLink(14, 19);
    G.createLink(15, 17);
    G.createLink(15, 28);
    G.createLink(16, 17);
    G.createLink(16, 27);
    G.createLink(17, 16);
    G.createLink(17, 15);
    G.createLink(17, 14);
    G.createLink(18, 16);
    G.createLink(19, 14);
    G.createLink(19, 20);
    G.createLink(20, 18);
    G.createLink(20, 31);
    G.createLink(21, 5);
    G.createLink(22, 4);
    G.createLink(22, 17);
    G.createLink(23, 30);
    G.createLink(24, 13);
    G.createLink(24, 26);
    G.createLink(25, 28);
    G.createLink(25, 32);
    G.createLink(26, 30);
    G.createLink(26, 24);
    G.createLink(27, 3);
    G.createLink(27, 16);
    G.createLink(27, 26);
    G.createLink(28, 25);
    G.createLink(28, 15);
    G.createLink(28, 29);
    G.createLink(29, 29);
    G.createLink(30, 26);
    G.createLink(30, 29);
    G.createLink(31, 32);
    G.createLink(32, 31);
    G.createLink(32, 23);
    G.createLink(32, 25);
    
    //G.print();
    
    std::cout << "Enter a source node and a destiniation node to see the shortest path\n";
    int src, dest;
    std::cin >> src >> dest;
    
    G.BFS(G, src, dest);
    
    return 0;
}

