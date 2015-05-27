/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

#include <vector>
#include <iterator>


using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***

    // https://www.youtube.com/watch?v=XuCbpw6Bj1U - video om queues

    Queue<int> Q;
    int v;

    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
    }

    dist[s] = 0;

    Q.enqueue(s);

    while(!Q.isEmpty())
    {
        v = Q.getFront();
        Q.dequeue();

        Node* next = array[v].getFirst();

        while(next)
        {
            if(dist[next->vertex] == INFINITY)
            {
                dist[next->vertex] = dist[v] + 1;
                path[next->vertex] = v;
                Q.enqueue(next->vertex);
            }
            next = array[v].getNext();
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***

    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;

    int v = s;

    while(true) 
    {

        Node* next = array[v].getFirst();

        while(next)
        {
            if(!done[next->vertex] && dist[next->vertex] > dist[v] + next->weight)
            {
                dist[next->vertex] = dist[v] + next->weight;
                path[next->vertex] = v;
            }
            next = array[v].getNext();
        }

        done[v] = true;

        int smallest = INFINITY;

        for(int i = 1; i <= size; i++)
        {

            if(dist[i] < smallest && !done[i])
            {
                smallest =  dist[i];
                v = i;
            }
            
        }
        if(smallest == INFINITY) { break; }
    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;

         return;
    }

    // *** TODO ***
/*
    // recussiv
    if(path[t] != 0)
    {
        printPath(path[t]);
    }

    std::cout << t << setw(3) << "dist: " << dist[t] << setw(3); 

    // Hur får ut distansen rekusivt?  
*/

    // Iterativ
    std::vector<int> v;
    vector<int>::reverse_iterator it;
    int distance = dist[t];

    while(path[t] != 0)
    {
        v.push_back(t);
        t = path[t];
    }
    v.push_back(t);

    for(it = v.rbegin(); it != v.rend(); it++)
    {
        std::cout << *it << setw(3);
    }

    std::cout << "(" << distance << ")" << endl;
    
}