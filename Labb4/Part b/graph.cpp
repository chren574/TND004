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

    std::vector<Edge> edge;

    int* dist  = new int [size + 1];
    int* path  = new int [size + 1];
    bool* done  = new bool[size + 1];

    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    // Start position
    int current = 1;

    dist[current] = 0;
    done[current] = true;

    while(true) 
    {

        Node* next = array[current].getFirst();

        while(next)
        {
            if(!done[next->vertex] && dist[next->vertex] > next->weight)
            {
                dist[next->vertex] = next->weight;
                path[next->vertex] = current;
            }
            next = array[current].getNext();
        }

        done[current] = true;

        edge.push_back(Edge(current, path[current], dist[current]));

        int smallest = INFINITY;

        for(int i = 1; i <= size; i++)
        {

            if(dist[i] < smallest && !done[i])
            {
                smallest =  dist[i];
                current = i;
            }
            
        }    
        if(smallest == INFINITY) { break; }
    }

    int distence = 0;

    for (unsigned int i = 1; i < edge.size(); ++i)
    {
        std::cout << "( " << edge[i].tail << ", " << edge[i].head << ". " << edge[i].weight << ")" << endl;
        distence += edge[i].weight;   
    }

    std::cout << endl <<"Total weight = " << distence;

    delete[] dist;
    delete[] path;
    delete[] done;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{ 
    // *** TODO ***
    Heap<Edge> H;
    DSets D(size);

    int totaldist = 0;

    // Heapify
    for(int i = 1; i <= size; i++)
    {
        Node* e = array[i].getFirst();

        while(e->next)
        {
            // Checks if the are reverse - only join one time
            if(e->vertex < i)
            {
                H.insert(Edge(e->vertex, i, e->weight) );
                e = array[i].getNext();    
            }
            
        }
    }
    int counter = 0;

    while(counter < size -1)
    {
        Edge e = H.deleteMin();
        if(D.find(e.head) != D.find(e.tail) )
        {
            D.join(D.find(e.head) , D.find(e.tail));
            counter++;
            totaldist += e.weight;
            std::cout << e << endl;
        }
    }
    std::cout << endl <<"Total weight = " << totaldist;

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
