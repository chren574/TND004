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


//Insert v in the tree having root as this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    //cout << "Node::insert\n";

    if(v.first < value.first)
    {
        // if no child at left -> make babies here
        if(l_thread)
        {
            left = new Node(v,this->left,this);
            l_thread = false;

            left->r_thread = true;
            left->l_thread = true;

            //left->value.second = 1;
        }
        else
        {
            //if there is a left child -> insert to the child
            left->insert(v);
        }

        return true;
    }
    else if(v.first > value.first)
    {
        // if there is no child to the right
        if(r_thread)
        {
            right = new Node(v,this,this->right);
            r_thread = false;

            right->l_thread = true;
            right->r_thread = true;

            //right->value.second = 1;
        }
        else
        {
            right->insert(v);
        }

        return true;
    }
    else
    {
        // if v.first == value.first
        value.second++;
        return false;
    }
}

//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{

    cout << "remove" << endl;

    if(key < value.first)
    {
        if(l_thread)
        {
            return false;
        }
        else
        {
            left->remove(key,this,false);
        }
    }
    else if(key > value.first)
    {
        if(r_thread)
        {
            return false;
        }
        else
        {
            right->remove(key,this,true);
        }
    }
    else if(key == value.first)
    {
        // when the node is found...

        //has two children
        if(!l_thread && !r_thread)
        {
            Node* m = this->left->findMax();
            swap(value,m->value);
            removeMe(m->left,true);
        }

        //has one child
        else
        {
            removeMe(parent,isRight);
        }

        return true;
    }
    else
    {
        // not found
        return false;
    }
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
    if(!isRight)
    {
        //1a: a left child with only a right child
        if(l_thread && !r_thread)
        {
            parent->left = this->right;
            Node* m = this->right->findMin();
            m->left = this->left;

            //destroys everything
        }
        //1b: a left child with only a left child
        else if(!l_thread && r_thread)
        {
            parent->left = this->left;

        }
        else
        {
            parent->left = this->left;
        }

    }
    else
    {
        //1a: a right child with only a right child
        if(l_thread && !r_thread)
        {
            parent->right = this->right;

        }
        //1b: a right child with only a left child
        else if(!l_thread && r_thread)
        {
            parent->right = this->left;
            Node* m = this->left->findMax();
            m->right = this->right;


        }
        else
        {
            parent->right = this->right;

        }
    }

    l_thread = true;
    r_thread = true;
    delete this;

    cout << "removeMe" << endl;
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //cout << "Key is " << key << endl;
    if(key < value.first)
    {
        if(l_thread)
        {
            return nullptr;
        }
        else
        {
            return left->find(key);
        }
    }
    else if(key > value.first)
    {
        if(r_thread)
        {
            return nullptr;
        }
        else
        {
            return right->find(key);
        }
    }
    return this;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    // Marcus' iterative traversal

    Node* temp = this;

    while(!temp->l_thread)
    {
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

    if(l_thread || r_thread)
    {
        temp = temp->left;
    }

    while(!temp->r_thread)
    {
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
