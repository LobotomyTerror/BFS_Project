#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <format>
#include "Graph.hpp"
#include "Node.hpp"

using namespace std::chrono;
//This function reads in ordered pairs and populates our graph
//Because we can't use the string library, I had to find some creative ways to make a sub-Cstring
//It's kind of ugly but it works
void getTime()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::chrono::milliseconds now2 = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    struct tm currentLocalTime;
    localtime_r(&currentTime, &currentLocalTime);
    char timeBuffer[80];
    std::size_t charCount { std::strftime( timeBuffer, 80, "%D %T", &currentLocalTime)};
    if (charCount == 0) return;
    std::cout << "Date and time of code execution ";
    std::cout << timeBuffer << "." << std::setfill('0') << std::setw(3) << now2.count() % 1000 << std::endl;
}
void readData(Graph<int>& G, std::ifstream &fin) {
    int node1 = 0;
    int node2 = 0;
    int comma = 0;
    int initNum = 0;
    char fileline[10] = "6, 9";
    char initiziler[10] = " ";
    char cinit[10] = " ";
    //char nodes for sub-Cstrings
    char cnode1[10] = "   ";
    char cnode2[10] = "   ";
    
    // strncpy (cnode1, fileline, sizeof(cnode1));
    
    //read in from file
    try
    {
        fin.open("/Users/danielfishbein/Documents/computerProjects/Xcode/BFS/BFS/data.txt");
        if (!fin)
        {
            throw;
        }
    }
    catch (std::fstream::failure)
    {
        std::cerr << "Error with opening file on line 28" << std::endl;
        throw;
    }
    //Grabs the total amount of vertices from the text file
    fin.getline(initiziler, 100, '\n');
    strncpy(cinit, initiziler, '\n');
    initNum = atoi(cinit);
    G.initGraph(initNum);
    
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
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream outf;
    std::ifstream inf;
    int src_o, src_t, src_th;
    int dest_o, dest_t, dest_th;
    
    std::streambuf* stream_buffer_cerr = std::cerr.rdbuf();
    std::streambuf* stream_buffer_outf = outf.rdbuf();
    std::cerr.rdbuf(stream_buffer_outf);
    
    try
    {
        Graph<int> G;
        if (argc != 2)
            std::cout << "Usage of command line input is "  << argv[0] << "<filename>";
        else
        {
            readData(G, inf);
        }
        
        outf.open("errorlog.txt");
        
        if (!outf.is_open())
            throw;
        
        std::cout << "Enter three sources:\n";
        std::cin >> src_o >> src_t >> src_th;
        if(src_o < 0 || src_t < 0 || src_th < 0)
        {
            throw std::invalid_argument("Negative value has been entered\n");
        }
        std::cout << "Enter three destinations:\n";
        std::cin >> dest_o >> dest_t >> dest_th;
        if (dest_o < 0 || dest_t < 0 || dest_th < 0)
        {
            throw std::invalid_argument("Negative value has been entered\n");
        }
        
        G.print(src_o, dest_o, dest_t, dest_th);
        G.print(src_t, dest_o, dest_t, dest_th);
        G.print(src_th, dest_o, dest_t, dest_th);
    }
    catch (std::invalid_argument)
    {
        throw;
    }
    catch (std::fstream::failure)
    {
        std::cerr << "Error opening file check file path on line 102 in main" << std::endl;
        throw;
    }
    catch (...)
    {
        std::cout << "Error with program operation. Terminating program, please reference error log file." << std::endl;
        exit(1);
    }
    std::cerr.rdbuf(stream_buffer_cerr);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Total program run time took " << duration1.count() << " seconds\n";
    getTime();
    std::cout << "Program has terminated succesefully. Live long and prosper\n";

    return 0;
}

