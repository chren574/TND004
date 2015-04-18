/*
  Name: hashTable.h
  Author: Jingelman
  Course: TND004, Lab 1
  Description: template class to represent a set of elements of type T
  implementation uses a sorted doubly-linked list
  */

#include <iostream>
#include <new>
#include <cassert>

using namespace std;


/** \brief Template class to represent a Set of elements of type T
 *
 * Set is implemented as a sorted doubly linked list
 * \invariant Sets should not contain repetitions, i.e.
 * two objects with the same value cannot belong to a Set
 *
 * \param T is the type of the objects (elements) stored in the set
 * \note All Set operations have a linear complexity, in the worst case
 */

template<typename T>
class Set
{
private:

	/** \brief Class Node
	 *
	 * This class represents an internal node of a doubly linked list storing objects of type T
	 * \param T is the type of the object (element) stored in a Node
	 * \note All members of class Node are public
	 * but only class Set can access them, since Node is declared in the private part of class Set
	 *
	 */

	class Node
	{
	public:
		/** \brief Constructor
		 *
		 * \param nodeVal an object of type T whose copy will be stored in the Node
		 * \param nextPtr a pointer to the next Node in the list
		 * \param prevPtr a pointer to the previous Node in the list
		 * \pre Type T should support the following operations:
		 *  default constructor T(), operator<<, operator<=,
		 *
		 */
		//Constructor
		Node(T nodeVal = T(), Node* nextPtr = nullptr, Node* prevPtr = nullptr)
			: value(nodeVal), next(nextPtr), prev(prevPtr)
		{  };

		//Data members
		T value;    /**< Object (element) stored in the Node */
		Node* next; /**< Pointer to the next Node */
		Node* prev; /**< Pointer to the previous Node */
	};


public:

	/** \brief Default constructor
	 *
	 * Create an empty Set
	 *
	 */
	//Default constructor
	Set();


	/** \brief Conversion constructor
	 *
	 * Convert an object val into a singleton {val}
	 * \param val an object of type T
	 *
	 */
	//Conversion constructor
	Set(T val);


	/** \brief Constructor to create a Set from an array of objects
	 *
	 * Create a Set with (a copy of) all objects in array a
	 * \param a sorted array of objects of type T
	 * \param n number of objects in array a
	 *
	 */
	//Constructor to create a Set from a sorted array
	Set(T a[], int n);


	/** \brief Copy constructor
	 *
	 * Create a new Set as a copy of Set b
	 * \param b Set to be copied
	 * \note This function does not modify Set b in any way
	 *
	 */
	//Copy constructor
	Set(const Set& b);


	/** \brief Destructor
	 *
	 * Deallocate all memory (Nodes) allocated by the constructor
	 *
	 */
	//Destructor
	~Set();


	/** \brief Assignment operator
	 *
	 * Assigns new contents to the Set, replacing its current content
	 * \param b Set to be copied into Set *this
	 * \note This function does not modify Set b in any way
	 * \return *this
	 *
	 */
	//Assignment operator
	const Set& operator=(const Set& b);


	/** \brief Test whether the Set is empty
	 *
	 * \note This function does not modify the Set in any way
	 * \return true if the set is empty, otherwise false
	 *
	 */
	//Test whether a set is empty
	bool is_empty() const;


	/** \brief Count the number of objects stored in the Set
	 *
	 * \note This function does not modify the Set in any way
	 * \return An int larger or equal to zero
	 *
	 */
	//Return number of elements in the set
	int cardinality() const;


	/** \brief Test whether an object belongs to the Set
	 *
	 * \param val an object of type T to be searched for
	 * \note This function does not modify the Set in any way
	 * \return true if val belongs to the set, otherwise false
	 *
	 */
	//Test set membership
	bool is_member(T val) const;


	/** \brief Remove all elements from the Set
	*
	* Transform the Set into an empty set
	* \return None
	*
	*/
	//Make the set empty
	void clear();


	/** \brief Test whether *this is a subset of Set b
	 *
	 * a <= b iff every member of a is a member of b
	 * \param b a Set
	 * \note This function does not modify *this nor b in any way
	 * \return true, if *this is a subset of b, otherwise false
	 *
	 */
	//Return true, if the set is a subset of b, otherwise false
	//a <= b iff every member of a is a member of b
	bool operator<=(const Set& b) const;


	/** \brief Test whether *this and b represent the same set
	 *
	 * a == b, iff a <= b but not b <= a
	 * \param b a Set
	 * \note This function does not modify *this nor b in any way
	 * \return true, if *this stores the same elements as Set b, otherwise false
	 *
	 */
	//Return true, if the set is equal to set b
	//a == b, if a <= b but not b <= a
	bool operator==(const Set& b) const;


	/** \brief Test whether *this is a strict subset of Set b
	 *
	 * a < b iff a <= b but not b <= a
	 * \param b a Set
	 * \note This function does not modify *this nor b in any way
	 * \return true, if *this is a strict subset of b, otherwise false
	 *
	 */
	//Return true, if the set is a strict subset of S, otherwise false
	//a < b iff a <= b but not b <= a
	bool operator<(const Set& b) const;


private:
	Node *head;  /**< Pointer to the dummy header Node */
	Node *tail;  /**< Pointer to the dummy tail Node */
	int counter; /**< Count number of elements in the Set */

	//Private member functions

	/** \brief Insert a new Node storing val before the Node pointed by p
	 *
	 * \param p pointer to a Node
	 * \param val value to be inserted  before position p
	 * \return *this
	 *
	 */
	//Insert a new Node storing val before the Node pointed by p
	Set& insert(Node *p, T val);


	/** \brief Remove the Node pointed by p
	*
	* \param p pointer to a Node
	* \return *this
	*
	*/
	//Remove the Node pointed by p
	Set& erase(Node *p);


	/** \brief Initialize the Set to an empty Set
	*
	* \return None
	*
	*/
	//Initialize the Set to an empty Set
	void init();


	/** \brief Display the Set to ostream os
	*
	* \note This function does not modify *this in any way
	* \return None
	*
	*/
	//Display the Set to ostream os
	void print(ostream& os) const;


	/** \brief Set union of *this with Set S
	*
	* \param S a Set
	* \note This function does not modify *this nor S in any way
	* \return A new Set representing the union of *this with Set S
	*
	*/
	//Return a new set with the elements in S1 or in S2 (without repeated elements)
	Set _union(const Set& S) const;


	/** \brief Set intersection of *this with Set S
	*
	* \param S a Set
	* \note This function does not modify *this nor S in any way
	* \return A new Set representing the intersection of *this with Set S
	*
	*/
	//Return a new set with the elements in both sets S1 and S2
	Set _intersection(const Set& S) const;


	/** \brief Set difference of *this with Set S
	*
	* \param S a Set
	* \note This function does not modify *this nor S in any way
	* \return A new Set representing the difference of *this with Set S
	*
	*/
	//Return a new set with the elements in set S1 that do not belong to set S2
	Set _difference(const Set& S) const;



	//overloaded operators: union, intersection, difference, operator<<


	/** \brief Overloaded operator<<
	 *
	 * \param os output stream
	 * \param b Set to be displayed
	 * \return parameter os
	 *
	 */
	friend ostream& operator<< (ostream& os, const Set<T>& b)
	{
		if (b.is_empty())
			os << "Set is empty!" << endl;
		else
		{
			b.print(os); //call the private function Set<T>::print
		}

		return os;
	}


	/** \brief Overloaded operator+: to represent Set union S1+S2
	 *
	 * S1+S2 is the Set of elements in Set S1 or in Set S2 (without repeated elements)
	 * \param S1 a Set
	 * \param S2 a Set
	 * \note This function does not modify S1 nor S2 in any way
	 * \return A new Set representing the union of S1 with S2, S1+S2
	 *
	 */
	friend Set<T> operator+ (const Set<T>& S1, const Set<T>& S2)
	{
		return S1._union(S2); //call the private function Set<T>::_union
	};



	/** \brief Overloaded operator*: to represent Set intersection S1*S2
	 *
	 * S1*S2 is the Set of elements in both Sets S1 and set S2
	 * \param S1 a Set
	 * \param S2 a Set
	 * \note This function does not modify S1 nor S2 in any way
	 * \return A new Set representing the intersection of S1 with S2, S1*S2
	 *
	 */
	friend Set<T> operator* (const Set<T>& S1, const Set<T>& S2)
	{
		return S1._intersection(S2); //call the private function Set<T>::_intersection
	};


	/** \brief Overloaded operator-: to represent Set difference S1-S2
	 *
	 * S1-S2 is the Set of elements in Set S1 that do not belong to Set S2
	 * \param S1 a Set
	 * \param S2 a Set
	 * \note This function does not modify S1 nor S2 in any way
	 * \return A new Set representing the set difference S1-S2
	 *
	 */
	friend Set<T> operator- (const Set<T>& S1, const Set<T>& S2)
	{
		return S1._difference(S2); //call the private function Set<T>::_difference
	}


};


/*****************************************************
* Implementation of the member functions             *
******************************************************/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//Default constructor
template<typename T>
Set<T>::Set()
{
	init();
}


//conversion constructor
template<typename T>
Set<T>::Set(T n)
{
	init();

	insert(tail, n);
}


//Constructor to create a Set from a sorted array
template<typename T>
Set<T>::Set(T a[], int n)
{
	init();
	for (int i = 0; i < n; i++)
	{
		insert(tail, a[i]);
	}
}


//Copy constructor
template<typename T>
Set<T>::Set(const Set& b)
{
	init();
	Node* ptr = b.head->next;

	while (ptr != b.tail)
	{
		insert(tail, ptr->value);
		ptr = ptr->next;
	}
}


//Destructor
template<typename T>
Set<T>::~Set()
{
	Node *ptr = head;

	while (ptr)
	{
		Node* to_remove = ptr;
		ptr = ptr->next;

		delete to_remove;
	}
}

//Assignment operator
template<typename T>
const Set<T>& Set<T>::operator=(const Set& b)
{
	this->clear();

	Node *ptr = b.head->next;

	while (ptr != b.tail)
	{
		insert(tail, ptr->value);
		ptr = ptr->next;
	}

	return *this; //delete this code
}


//Test whether a set is empty
template<typename T>
bool Set<T>::is_empty() const
{
	return (head->next == tail);
}


//Test set membership
template<typename T>
bool Set<T>::is_member(T val) const
{
	Node *ptr = head->next;

	while (ptr)
	{

		if (val == ptr->value)
		{
			return true;
		}

		ptr = ptr->next;
	}
	return false;
}


//Return number of elements in the set
template<typename T>
int Set<T>::cardinality() const
{
	Node *ptr = head->next;

	int c = 0;

	while (ptr != tail)
	{
		c++;
		ptr = ptr->next;
	}
	return c;
}


//Make the set empty
template<typename T>
void Set<T>::clear()
{
	Node *ptr = head->next;

	while (ptr != tail)
	{
		Node *to_remove = ptr;
		ptr = ptr->next;
		delete to_remove;
	}

	head->next = tail;
	tail->prev = head;
}

//Return true, if the set A is a subset of b, otherwise false
//a <= b if every member of a is a member of b
template<typename T>
bool Set<T>::operator<=(const Set& b) const
{
	Node *ptr_a = head->next;
	Node *ptr_b = b.head->next;

	while (ptr_a && ptr_b && (ptr_a != tail) && (ptr_b != b.tail)){

		if (ptr_a->value > ptr_b->value){
			ptr_b = ptr_b->next;
		}
		else if (ptr_a->value < ptr_b->value){
			return false;
		}
		else{
			ptr_a = ptr_a->next;
			ptr_b = ptr_b->next;
		}
	}
	if (ptr_a != tail){
		return false;
	}

	return true;
}

//Return true, if the set is equal to set b
//a == b, if a <= b and b <= a
template<typename T>
bool Set<T>::operator==(const Set& b) const
{
	Node *ptr_a = head->next;
	Node *ptr_b = b.head->next;

	while (ptr_a && ptr_b && (ptr_a != tail) && (ptr_b != b.tail))
	{
		if (ptr_a->value != ptr_b->value)
		{
			return false;
		}

		ptr_a = ptr_a->next;
		ptr_b = ptr_b->next;
	}

	if (ptr_b == b.tail && ptr_a == tail)
	{
		return true;
	}
	else{
		return false;
	}


}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, if a <= b but not b <= a
template<typename T>
bool Set<T>::operator<(const Set& b) const
{
	Node *ptr = head->next;

	while (ptr && ptr != tail)
	{
		if (!b.is_member(ptr->value))
		{
			return false;
		}
		ptr = ptr->next;
	}

	if (cardinality() >= b.cardinality())
	{
		return false;
	}

	return true;
}


/****************************************************
* Private member functions                          *
*****************************************************/

//Insert a new Node storing val before the Node pointed by p
template<typename T>
Set<T>& Set<T>::insert(Node *p, T val)
{
	Node *ins = new Node(val, p, p->prev);
	Node *old_prev = p->prev;

	p->prev = ins;
	old_prev->next = ins;

	return *this;
}


//Delete the Node pointed by p
template<typename T>
Set<T>& Set<T>::erase(Node *p)
{

	Node *prev_node = p->prev;
	Node *next_node = p->next;

	prev_node->next = next_node;
	next_node->prev = prev_node;

	delete p;

	return *this;
}

//Create an empty Set
template<typename T>
void Set<T>::init()
{
	head = new Node();
	tail = new Node();

	head->next = tail;
	tail->prev = head;

}

//Display all elements in the Set
template<typename T>
void Set<T>::print(ostream& os) const
{
	if (is_empty())
	{

		os << "Set is empty. ";
	}
	else
	{
		Node *ptr = head->next;

		os << "{ ";

		while (ptr != tail)
		{
			os << ptr->value << " ";
			ptr = ptr->next;
		}
		os << "}";
	}
}

//Set union
//Return a new set with the elements in S1 or in S2 (without repeated elements)
template<typename T>
Set<T> Set<T>::_union(const Set& b) const
{
	Node* ptr_a = head->next;
	Node* ptr_b = b.head->next;

	Set result;
	result.init();

	while (ptr_a && ptr_b && (ptr_a != tail) && (ptr_b != b.tail))
	{
		if (ptr_a->value < ptr_b->value)
		{
			result.insert(result.tail, ptr_a->value);
			ptr_a = ptr_a->next;
		}
		else if (ptr_a->value > ptr_b->value)
		{
			result.insert(result.tail, ptr_b->value);
			ptr_b = ptr_b->next;
		}
		else
		{
			result.insert(result.tail, ptr_a->value);
			ptr_a = ptr_a->next;
			ptr_b = ptr_b->next;
		}
	}

	// if there are more elements in A
	while (ptr_a && (ptr_a != tail))
	{
		result.insert(result.tail, ptr_a->value);
		ptr_a = ptr_a->next;
	}

	// if there are more elements in B
	while (ptr_b && (ptr_b != b.tail))
	{
		result.insert(result.tail, ptr_b->value);
		ptr_b = ptr_b->next;
	}

	return result;
}

//Set intersection
//Return a new set with the elements in both sets S1 and S2
template<typename T>
Set<T> Set<T>::_intersection(const Set& b) const
{
	Node* ptr_a = head->next;
	Node* ptr_b = b.head->next;

	Set result;
	result.init();

	while (ptr_a && ptr_b && (ptr_a != tail) && (ptr_b != b.tail))
	{

		if (ptr_a->value < ptr_b->value)
		{
			ptr_a = ptr_a->next;
		}
		else if (ptr_a->value > ptr_b->value)
		{
			ptr_b = ptr_b->next;
		}
		else
		{
			result.insert(result.tail, ptr_a->value);
			ptr_a = ptr_a->next;
			ptr_b = ptr_b->next;
		}
	}
	return result; //delete this code
}


//Set difference
//Return a new set with the elements in set S1 that do not belong to set S2
template<typename T>
Set<T> Set<T>::_difference(const Set& b) const
{
	Node* ptr_a = head->next;
	Node* ptr_b = b.head->next;

	Set result;
	result.init();

	while (ptr_a && ptr_b && (ptr_a != tail) && (ptr_b != b.tail))
	{
		if (ptr_a->value == ptr_b->value)
		{
			ptr_a = ptr_a->next;
			ptr_b = ptr_b->next;
		}
		else if (ptr_a->value < ptr_b->value)
		{
			result.insert(result.tail, ptr_a->value);
			ptr_a = ptr_a->next;
		}
		else
		{
			ptr_b = ptr_b->next;
		}
	}

	// if there are MOAR in list A

	while (ptr_a && ptr_a != tail)
	{
		result.insert(result.tail, ptr_a->value);
		ptr_a = ptr_a->next;
	}
	return result;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

