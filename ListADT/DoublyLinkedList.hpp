#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
#include <iterator>

using namespace std;

bool testing = false;

enum dtype { FORWARD, BACKWARD };

template <class LT> class DoublyLinkedList;
template <class LT> ostream & operator << (ostream & outs, const DoublyLinkedList<LT> & L);

template <class LT>
class DoublyLinkedList
{
   private:
      struct Node 
      {
         Node ();
         LT data;
         Node * next; 
     	 Node * prev;
      };
  
  public:
		class Iterator
		{
			public:
				Iterator ();
				Iterator (Node * NP);
				LT & operator * () const;
				Iterator operator ++ ();
				Iterator operator ++ (int);
				Iterator operator -- ();
				Iterator operator -- (int);
				bool operator == (const Iterator & other) const;
				bool operator != (const Iterator & other) const;
			private:
				Node * current;
		};

		DoublyLinkedList ();
		DoublyLinkedList (const DoublyLinkedList & other);
		~DoublyLinkedList ();
		DoublyLinkedList & operator = (const DoublyLinkedList & other);
		bool operator == (const DoublyLinkedList & other); 
		int Size () const;
		void SetDirection(dtype dir);
		dtype GetDirection () const;
		friend ostream & operator << <> (ostream & outs, const DoublyLinkedList<LT> & L);
		bool InsertFirst(const LT & value);
		bool InsertLast(const LT & value); 
		bool DeleteFirst (); 
		bool DeleteLast (); 
		void Forward(void function(const LT & param));
		void Backward(void function(const LT & param));

		Iterator begin () const;
		Iterator rbegin () const;
		Iterator end () const;
		Iterator rend () const;

		LT & operator [] (const int & index) const;

	private:
		Node * first;
		Node * last;
		int size;
		dtype direction;
};

// Node default constructor creates an Node object of the DoublyLinkedList class
template <class LT>
DoublyLinkedList<LT>::Node::Node()
{ 
	if (testing) { cout << "Node default constructor called for address: " << this << endl; }
	next = NULL; // Set the Node pointer next to NULL
	prev = NULL; // Set the Node pointer prev to NULL
}

// DoublyLinkedList default constructor will instantiate an DoublyLinkedList object
template <class LT>
DoublyLinkedList<LT>::DoublyLinkedList()
{
	if (testing) { cout << "DoublyLinkedList default constructor called for address: " << this << endl; }
 	size = 0; // Set DoublyLinkedList's private data member size to 0
	first = NULL; // Set DoublyLinkedList's private pointer first to NULL
	last = NULL; // Set DoublyLinkedList's private ponter last to NULL
	direction = FORWARD; // Set the direction to FORWARD
}

// DoublyLinkedList copy constructor will create an DoublyLinkedList object that is a copy of other DoublyLinkedList
template <class LT>
DoublyLinkedList<LT>::DoublyLinkedList(const DoublyLinkedList & other)
{ 
	if (testing) { cout << "DoublyLinkedList copy cosntructor called for address: " << this << endl; }
	first = NULL; // Set first to NULL
	size = 0; // Set size to 0
	for (Node * n = other.first; n != NULL; n = n->next) // Create a node ptr and have it point to other's first
		InsertLast(n->data); // Traverse the entire list, inserting each nodes data at the end of the list,
	direction = other.direction; // Set the current LList's direction to be the other LList's direction
	
}

// DoublyLinkedList destructor will delete the entire DoublyLinkedList
template <class LT>
DoublyLinkedList<LT>::~DoublyLinkedList()
{
	if (testing) { cout << "DoublyLinkedList destructor called for address: " << this << endl; }
	while (first) // While current objects' first points to something besides NULL
		DeleteFirst(); // Delete first node
}

// DoublyLinkedList assignment operator will assign the contents of other DoublyLinkedList to the current DoublyLinkedList
template <class LT>
DoublyLinkedList<LT> & DoublyLinkedList<LT>::operator = (const DoublyLinkedList<LT> & other)
{ 
	if (testing) { cout << "ASSIGNMENT OPERATOR = HAS BEEN CALLED FOR: " << this << endl; }
 	if (this == &other) // If they both have the same memory address (they are the same object)
		return * this; // Return the object
	while (first) // While current objects' first points to something besides NULL
		DeleteFirst(); // Delete first node 
	for (Node * n = other.first; n != NULL; n = n->next) // Traverse the other list
		InsertLast(n->data); // Insert each nodes data at the end of the end of the curent objects list
	direction = other.direction; 
	return * this; // Return the list
}

// DoublyLinkedList equality operator will determine if two LLists are equal
template <class LT>
bool DoublyLinkedList<LT>::operator == (const DoublyLinkedList & other)
{  
	if (testing) { cout << "EQUALITY OPERATOR == HAS BEEN CALLED FOR: " << this << endl; }
	if (size != other.size) // Check if the lists do not have the same size
		return false; // If so, they are not equal, return false
	Node * temp = other.first; // Create temporary ptr to other's first node
	Node * this_temp = first; // Create temporary ptr to current object's node
	while (this_temp != NULL && temp != NULL) // Traverse both lists until the last node
	{
		if (this_temp->data != temp->data) // If any corresponding pairs are different
			return false; // Return false, the lists are not equal
		this_temp = this_temp->next; // Traverse to the next node in current list
		temp = temp->next; // Traverse to the next node in other list
	}
	return true; // Return true to indicate the LLists are equal
}

// Accessor function to access the size of the list
template <class LT>
int DoublyLinkedList<LT>::Size() const
{ 
	return size; // Return the private variable size
}

template <class LT>
void DoublyLinkedList<LT>::SetDirection(dtype dir)
{
	direction = dir;
}


// Friend function ostream insertion operator will insert an DoublyLinkedList into the output stream in proper format
template <class LT>
ostream & operator << (ostream & outs, const DoublyLinkedList<LT> & L)
{
	if (L.first == NULL) // If L is empty
		return outs; // Return output stream
	if (L.direction == FORWARD) // If L direction is forward
	{ // Print the list from beginning (first) to end
		outs << L.first->data;
		typename DoublyLinkedList<LT>::Node * n;
		for (n = L.first->next; n != NULL; n = n->next) // Traverse the list L until there are
			outs << ' ' << n->data; // no more nodes to access. Write to outs the data from the node
	}
	else // L.direction == BACKWARD
	{ // Print the list from end to beginning
		outs << L.last->data;
		typename DoublyLinkedList<LT>::Node * p;
		for (p = L.last->prev; p != NULL; p = p->prev)
			outs << ' ' << p->data;
	}
	return outs; // Return the output stream
}
		
// This function will insert a new node at the beginning of the list
template <class LT>
bool DoublyLinkedList<LT>::InsertFirst(const LT & value)
{
	Node * nnp = new Node; // Allocate memory for a new node
	if (nnp == NULL) // Check to see if memory was not allocated
		return false;	// Return false if memory allocation failed
	nnp->data = value; // Set data of the new node equal to the input value
    if (size > 0)
	{
       	first->prev = nnp; 
		nnp->next = first; // Have the nnp's ptr 'next' poent to the current first's prev ptr
	}
	else
		last = nnp;
	first = nnp; // Have the DoublyLinkedList's ptr 'first' point to the new node, making it the first
	size++; // Increment the size of the list
	return true; // Return true to indicate success
}

// This function will insert a node at the end of the list
template <class LT>
bool DoublyLinkedList<LT>::InsertLast(const LT & value)
{
	if (size == 0) // If the list is empty call InsertFirst and return its result
		return InsertFirst(value); // True if we created node, false otherwise
	Node * n = new Node; // Allocate memory for a new node
	if (n == NULL)	// Check if memory cannot be allocated for the node
		return false; // Return false to indicate memory allocation failed
	n->data = value; // Set the data of the new node equal to the input value
	last->next = n; // Have current last's next point to new node, making it last in list
	n->prev = last; // Have new node's prev point to where last points (connect sec2last and last nodes)
	last = n; // Have the last pointer point to the new last node
	size++; // Increment the size of the list
	return true; // Return true to indicate success
}

// This function will delete the first node in the list
template <class LT>
bool DoublyLinkedList<LT>::DeleteFirst()
{
	if (first == NULL)
		return false; // Return false, nothing to delete
	Node * temp = first; // Create a temp node ptr and have it point to where first points
	first = first->next; // Have first point to the second node in the list
	delete temp; // Delete temp, which contains the address of what was the first node
	size--; // Decrement the size of the list
	if (size == 0) // If the list is now empty
	{
		last = NULL; // Have last point to NULL
		first = NULL; // Have first point to NULL
	}
	if (size > 0) // if this if isn't here, segfault??
        	first->prev = NULL; // Have the new first node's prev pointer point to first
	if (size == 1)
		last = first;
	return true; // Return true to indicate success
}

// This function will delete the last node in the list
template <class LT>
bool DoublyLinkedList<LT>::DeleteLast()
{ 
	if (size == 0) // Check if the list is empty
		return false; // Return false, nothing to delete
	if (size == 1) // Check if there is only one node in the list
		return DeleteFirst(); // Call DeleteFirst to delete it
	Node * temp = last; // Create a temp ptr that points to the last node
	Node * second2last = last->prev; // Pointer to second to last node
	second2last->next = NULL; // Have the second2last pointer point to NULL (it will be new last node)
	delete temp; // Delete current last node, making second2last the last node
	last = second2last; // Have last point to second2last
	size--; // Decrement the size of the list
	return true; // Return true to indicate success
}

template <class LT>
void DoublyLinkedList<LT>::Forward(void function(const LT & param))
{
	for (Node * n = first; n; n = n->next)
		function(n->data);
}

template <class LT>
void DoublyLinkedList<LT>::Backward(void function(const LT & param))
{
	for (Node * n = last; n; n = n->prev)
		function(n->data);
}

template <class LT>
LT & DoublyLinkedList<LT>::operator [] (const int & index) const
{	
// This function returns a reference type. This causes it to be an l-value, allowing you
// to use subscripted expressions on either side of assignment operators.
	DoublyLinkedList<LT>::Node * n = first;
	int i = 0;
	for (int i = 0; i < index; i++)
		n = n->next;
	
	return n->data;
}

template <class LT>
DoublyLinkedList<LT>::Iterator::Iterator ()
{
	current = NULL;
}

template <class LT>
DoublyLinkedList<LT>::Iterator::Iterator (Node * NP)
{
	current = NP;
}

template <class LT>
LT & DoublyLinkedList<LT>::Iterator::operator * () const
{
	return current->data;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::Iterator::operator ++ ()
{
	current = current->next;
	return *this;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::Iterator::operator ++ (int)
{
	Iterator temp = *this;
	current = current->next;
	return temp;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::Iterator::operator -- ()
{
	current = current->prev;
	return *this;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::Iterator::operator -- (int)
{
	Iterator temp = *this;
	current = current->prev;
	return temp;
}

template <class LT>
bool DoublyLinkedList<LT>::Iterator::operator == (const Iterator & other) const
{
	return current == other.current;
}

template <class LT>
bool DoublyLinkedList<LT>::Iterator::operator != (const Iterator & other) const
{
	return current != other.current;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::begin () const
{
	Iterator temp (first);
	return temp;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::rbegin () const
{
	Iterator temp (last);
	return temp;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::end () const
{
	Iterator temp;
	return temp;
}

template <class LT>
typename DoublyLinkedList<LT>::Iterator DoublyLinkedList<LT>::rend () const
{
	Iterator temp;
	return temp;
}


#endif
