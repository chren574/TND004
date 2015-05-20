/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
    : current(ptr)
{

}


//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
    return current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    return &current->value;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    return (current == it.current);
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
    return (current != it.current);
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
    if(!current->r_thread)
    {
        current = current->right->findMin();
    }
    else
    {
        current = current->right;
    }
    return *this;
}


//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
    BiIterator *pos = this;

    if(!current->r_thread)
    {
        current = current->right->findMin();
    }
    else
    {
        current = current->right;
    }
    return *pos;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
    if(!current->l_thread)
    {
        current = current->left->findMax();
        //current = current->left->findMax();
    }
    else
    {
        current = current->left;
    }
    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
    BiIterator *pos = this;

    if(!current->l_thread)
    {
        //current = current->left->findMax();
        current = current->left;
    }
    else
    {
        current = current->left;
    }
    return *pos;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
