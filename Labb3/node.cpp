/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
    : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    // Recursive deletion of nodes. If the node have children, remove them.
    if(!l_thread)
    {
        delete left;
    }
    if(!r_thread)
    {
        delete right;
    }
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{

    // Marcus' new recursive version

    if(stoi(v.first) < stoi(value.first))
    {
        // if no child at left -> make babies here
        if(l_thread)
        {
            left = new Node(v,root,this);
            l_thread = false;

            left->r_thread = true;
            left->l_thread = true;
        }
        else
        {
            //if there is a left child -> insert to the child
            insert(left);
        }
    }
    else if(stoi(v.first) > stoi(value.first))
    {
        // if there is no child to the right
        if(r_thread)
        {
            right = new Node(v,this,root);
            r_thread = false;

            right->l_thread = true;
            right->r_thread = true;
        }
        else
        {
            insert(right);
        }
    }
    else
    {
        // if v.first == value.first
        value.second++;
    }

    return true;
}

//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
    //ADD CODE
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    if(stoi(key) < stoi(value.first))
    {
        if(!l_thread)
        {
            find(left);
        }
        else
        {
            return nullptr;
        }
    }
    else if(stoi(key) < stoi(value.first))
    {
        if(!r_thread)
        {
            find(right);
        }
        else
        {
            return nullptr;
        }
    }

    // else
    // stoi(key) == stoi(value.first) -> found it
    return this;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    // Marcus' iterative traversal

    Node* temp = this;

    while(!temp->l_thread){
        temp = temp->left;
    }
    return temp;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    // Marcus' iterative version

    Node* temp = this;

    if(this == root){
        temp = temp->left;
    }

    while(!temp->r_thread){
        temp = temp->right;
    }
    return temp;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
