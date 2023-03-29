#include <iostream>

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
    void createLink(T, T);
    void print(T, T, T, T);
    void BFS(T, int[], int[], int[]);
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
    delete adj;
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
    Node<T>* first_node;
    
    if (temp1->data == temp2->data)
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
        last_node->next = temp2;
        last_node = last_node->next;
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

//Breadth-first search to find the shortest path from a
//user-defined source node to a destination node...
template<typename T>
void Graph<T>::BFS(T src, int pathTo[], int destTo[], int pred[])
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
    
    //three array declrations
    int pathTo[numOfVertices];
    int distTo[numOfVertices];
    int pred[numOfVertices];
    
    for (int i = 0; i < numOfVertices; ++i) //init of the three arrays
    {
        pathTo[i] = 0;
        distTo[i] = 0;
        pred[i] = 0;
    }
    BFS(src, pathTo, distTo, pred);
    
    for (int i = 0; i < numOfVertices; ++i)
    {
        if (pathTo[i] == dest_one || pathTo[i] == dest_two || pathTo[i] == dest_three)
        {
            std::cout << pathTo[i] << ' ';
            int node = pred[i];
            
            for (int j = i; j >= 0; --j)
            {
                if (pathTo[j] == node)
                {
                    std::cout << pathTo[j] << ' ';
                    node = pred[j];
                }
            }
            std::cout << '\n';
        }
    }
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
    G.createLink(27, 2);
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

    /*All the information stated below is going to change to member objects along with the use of overloaded fucntions >> and <<*/
//    std::cout << "Enter three starting integers to see there shortest path to three destination nodes\n";
//    int src_one, src_two, src_three;
//    std::cin >> src_one >> src_two >> src_three;
//    std::cout << "Enter three destination nodes as integers\n";
//    int dest_one, dest_two, dest_three;
//    std::cin >> dest_one >> dest_two >> dest_three;
    
//    G.print(src_one, dest_one, dest_two, dest_three);
    G.print(7, 32, 22, 3);
    return 0;
}

