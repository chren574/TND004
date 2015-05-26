/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

#include <vector>
#include <iterator>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{

    // *** TODO ***

    int start = 1;
    int distence = 0;

    std::vector<int> visited;

    visited.push_back(start);


    for(int i = 0; i < size; i++)
    {  
        int shortest = INFINITY;
        int index;

        for(int j = 1; j <= size; j++)
        {
            // edge j:s head == visitet(i)

            Node *current = array[j].getFirst();

            if(current->head != visited.at(i) && findInVisited(visited,j))
            {
                if(current->weight < shortest){
                    shortest = current->weight;
                    index = j;
                }
            }
        }
        distence += shortest;
        visited.push_back(index);

    }

    std::cout << "shortest distence is " << distence << endl;
}

bool Graph::findInVisited(std::vector<int> V, int j){
    vector<int>::iterator it;
    it = find(V.begin(), V.end() , j);

    // found if it != V.end()
    return ( if(it != V.end() ) );
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
