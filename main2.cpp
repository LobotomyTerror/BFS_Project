#include <iostream>
#include <fstream>
#include <cstring>

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
        ++numOfVertices;
    }
    else if (adj[v] == nullptr)
    {
        first_node = temp1;
        last_node = temp2;
        first_node->next = last_node;
        adj[v] = first_node;
        ++numOfVertices;
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
    int *p = 0;
    
    for (int i = 0; i < numOfVertices; ++i)
    {
        if (pathTo[i] == dest_one || pathTo[i] == dest_two || pathTo[i] == dest_three)
        {
            //std::cout << pathTo[i] << ' ';
            int pnode = pred[i];
            int cnode = pathTo[i];
            p[i] = cnode;
            std::cout << p[i] << ' ';
//            int tempArr[distTo[i] + 1];
            
            for (int j = i - 1; j >= 0; --j)
            {
//                tempArr[j - 1] = cnode;
                if (pathTo[j] == pnode)
                {
                    if (pnode != -1)
                        p[j] = pnode;
                    pnode = pred[j];
                    std::cout << p[j] << ' ';
                }
            }
            std::cout << '\n';
            for (int k = 0; k < sizeof(*p) - 1; ++k)
                std::cout << p[k] << ' ';
//            for (int k = 0; k < sizeof(tempArr) / sizeof(int); ++k)
//            {
//                std::cout << tempArr[k] << ' ';
//            }
//            //tempArr[0];
        }
    }
}


//This function reads in ordered pairs and populates our graph
//Because we can't use the string library, I had to find some creative ways to make a sub-Cstring
//It's kind of ugly but it works
void readData(Graph<int>& G) {
    G.initGraph(0);
    int node1 = 0;
    int node2 = 0;
    int comma = 0;
    char fileline[10] = "6, 9";
    //char nodes for sub-Cstrings
    char cnode1[10] = "   ";
    char cnode2[10] = "   ";

    // strncpy (cnode1, fileline, sizeof(cnode1));

    //read in from file
    std::ifstream fin;
    fin.open("/Users/danielfishbein/Documents/computerProjects/Xcode/Test/Test/data.txt");
    if (!fin)
    {
        std::cerr << "Error opening file\n";
        return;
    }
    //store data in fileline
    while(fin.getline(fileline, 100)) {
        for(int i = 0; i < 10; i++) {
            //Find where the comma is in the pair
            if(fileline[i] == ',') {
                comma = i;
                break;
            }
        }

        //Make a substring for the first node based on where the comma is
        strncpy(cnode1, fileline, comma);

        //Convert that substring to an int
        node1 = atoi(cnode1);
        
        for(int i = 0; i < 10; i++) {
            //Remove all values before and including the comma
            if(i == comma) {
                fileline[i] = ' ';
                break;
            }
            fileline[i] = ' ';
        }

        //Make substring for second node
        strncpy(cnode2, fileline, 10);

        //Convert substring to an int
        node2 = atoi(cnode2);

        //std::cout << node1 << ", " << node2 << std::endl;
        G.createLink(node1, node2);
    }
    fin.close();
}

int main(int argc, const char * argv[])
{
    Graph<int> G;
    readData(G);
    
    std::cout << "Enter three sources:\n";
    int src_o, src_t, src_th;
    std::cin >> src_o >> src_t >> src_th;
    std::cout << "Enter three destinations:\n";
    int dest_o, dest_t, dest_th;
    std::cin >> dest_o >> dest_t >> dest_th;
    G.print(src_o, dest_o, dest_t, dest_th);
    G.print(src_t, dest_o, dest_t, dest_th);
    G.print(src_th, dest_o, dest_t, dest_th);
    
    return 0;
}

