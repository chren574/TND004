#include <assert.h>
#include <iomanip>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{
    hTable = new Item* [size];

    for(int i = 0; i < size; i++)
    {
        hTable[i] = nullptr;
    }
}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    for(int i = 0; i < size; i++)
    {
        delete hTable[i];
    }
    
    delete hTable;
}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{

    unsigned int index = h(key, size);
    if(hTable[index]->key == key)
    {
        return 1;
    }
    else
    {
        return NOT_FOUND;
    }
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{

    if(loadFactor()+1 >= MAX_LOAD_FACTOR)
    {
        reHash();
    }

    unsigned int index = h(key, size);

    if(hTable[index] != nullptr)
    {
        if(hTable[index]->key != key)
        {
            while(hTable[index] != nullptr)
            {
                if(index == size -1)
                {
                    index = 0;
                }
                else
                {
                    index++;
                }
            }
            hTable[index] = new Item(key, 1);
            nItems++;
        }
        else
        {
            hTable[index]->value = v;
        }
    }
    else
    {
        hTable[index] = new Item(key,1);
        nItems++;
    }
}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    unsigned int index = h(key, size);
    if(hTable[index] != nullptr)
    {
        hTable[index] = new Item("",NOT_FOUND);
        nItems--;
        return true;
    }

    return false;
}

void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;
}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
	cout << "Rehashing...";

    HashTable newHash(nextPrime(2*size), h);

    for(int i = 0; i < size; i++)
    {
        if(hTable[i]->value == 1)
        {
            newHash.insert(hTable[i]->key, 1);
        }
    }

    std::swap(hTable, newHash.hTable);
    std::swap(size, newHash.size);
    std::swap(nItems, newHash.nItems);
}
