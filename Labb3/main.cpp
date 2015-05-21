/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

bool isNotAlnum(char c)
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

/*******************************
* 2. Main function             *
********************************/


int main()
{
    MAP table;

    string name;
    string s;

    int count = 0;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile;
    textFile.open(name);
    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }

    cout << "Loading the words from " << name << " ...\n";

    //Read words and load them in the table

    while (textFile >> s)
    {
        //remove non-alphanumeric chars
        s.erase(remove_if(s.begin(), s.end(), isNotAlnum), s.end());

        //convert to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (!s.size()) continue; //skip numbers and punctuation signs

        table[s].second++;  //if s is not in the table then it is inserted

        count++;
    }
    textFile.close();


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    cout << "Number of words in the file = " << table.total() << endl;
    cout << "Number of unique words in this file = " << table.size() << endl << endl;
    cout << "Frequency table sorted alphabetically..."  << endl << endl;
    cout << setw(5) << "KEY" << setw(10) << "COUNTER" << endl;
    cout <<  "====================================" << endl;

    BiIterator it = table.begin();

    for( ; it != table.end(); it++)
    {
        cout << setw(15) << it->first << setw(12) << it->second << endl;
    }


    /******************************************************
    * PHASE 2: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    vector<string> toRemove;

    it = table.begin();

    for( ; it != table.end(); it++)
    {
        if(it->second == 1)
        {
            toRemove.push_back(it->first);
        }
    }

    for(unsigned int i = 0; i < toRemove.size(); i++){
        table.remove(toRemove.at(i));
    }
    toRemove.clear();

    cout << "Number of words after remove: " << table.size() << endl << endl;

    cout << "Frequency table sorted alphabetically..."  << endl << endl;

    cout << setw(5) << "KEY" << setw(10) << "COUNTER" << endl;
    cout <<  "====================================" << endl;

    it = table.begin();

    for( ; it != table.end(); it++)
    {
        cout << setw(15) << it->first << setw(12) << it->second << endl;
    }


    /***********************************************************
    * PHASE 3: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/


    cout << "Enter two words: " << endl;
    string w1,w2;

    cin >> w1;
    cin >> w2;

    BiIterator firstWord = table.find(w1);
    BiIterator lastWord = table.find(w2);

    cout << "Frequency table in [" << w1 << "," << w2 << "]" << endl << endl;
    cout << setw(5) << "KEY" << setw(5) << "COUNTER" << endl;
    cout <<  "====================================" << endl;

    for(; firstWord != lastWord; firstWord++)
    {
        cout << setw(15) << firstWord->first << setw(12) << firstWord->second << endl;
    }

    cout << setw(15) << firstWord->first << setw(12) << firstWord->second << endl;

    return 0;
}
