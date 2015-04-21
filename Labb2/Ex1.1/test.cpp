/*
  Name: hashTable.h
  Author: Aida Nordman
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "hashTable.h"

using namespace std;

//A simple hash function
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++)
        hashVal += s[i];

    hashVal %= tableSize;

    return hashVal;
}


bool ignoreChar(char c)
{
    switch(c)
    {
    case '.':
    case ',':
    case '!':
    case '?':
    case ':':
    case '"':
    case '(':
    case ')':
    case ';':
    case '\\':
        return true;
    default:
        return false;
    }
}

int main()
{
    
    string key;
    const int TABLE_SIZE = 7;

    HashTable table(TABLE_SIZE, my_hash);

    ifstream in;
    in.open("files/test_file1.txt");


    if(in.is_open())
    {
        while(!in.eof())
        {
            in >> key;
            transform(key.begin(), key.end(), key.begin(), ::tolower);
            key.erase(std::remove_if(key.begin(), key.end(), &ignoreChar), key.end());
            if(key == "power" || key == "biggest"){
            cout << key << endl;
            }
            table.insert(key, 1);
        }
    }
    in.close();

    cout << "Number of words in the file = " << table.getNumberofWords() << endl;
    cout << "Number of uniqe words in this file = " << table.getnItems() << endl << endl;
    cout << "Frequency table ..."  << endl << endl;
    table.display(cout);



    return 0;
}
