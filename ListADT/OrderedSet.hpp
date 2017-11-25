/**********************************************************************************************************
 * File : OrderedSet.hpp										  *
 * Author : Mike Dito											  *
 * Description : This file contains the specifications and implementations for an Ordered Set of data.    *
 * The private members of the class include an Node (composed of a peice of data, and pointers to the     *
 * next and previous Nodes), functions to insert and delete the data at the beginning or end of the set,  *
 * an enumerated type to indicate the output traversal direction, an integer to store the size of the     *
 * set, and two pointers to the first and last Nodes in the set. The public interface includes class	  *
 * descriptions for an Iterator and Exception handling. The public interface also includes many functions *
 * for creating/deleting a set, comparing sets, checking if the set is empty, checking if an item is in   *
 * the set, inserting/deleting an item, setting/getting the direction, helper functiosn to access the     *
 * data in forward/backward order, an output stream operator, operators to find the union & intersection  * 
 * of two sets, the index operator, and iterators to help with set traversal.				  *
 *********************************************************************************************************/
#ifndef ORDEREDSET_HPP
#define ORDEREDSET_HPP

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <sstream>

using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class ST> class OrderedSet;
template <class ST> ostream & operator << (ostream & outs, const OrderedSet<ST> & S);

template <class ST>
class OrderedSet
{
	private:
		class Node
		{
			public:
				Node (); 
				ST data; 
				Node * next; 
				Node * prev;
		};

	public:
		class Iterator 
		{
			public:
				Iterator (); 
				Iterator (Node * NP); 
				const ST operator * () const; 
				Iterator operator ++ (); 
				Iterator operator ++ (int); 
				Iterator operator -- (); 
				Iterator operator -- (int); 
				bool operator == (const Iterator & other) const;
				bool operator != (const Iterator & other) const;
			private:
				Node * current;
		};
		class Exception
		{
			public:
				Exception ();
				Exception (string msg);
				Exception (int indx);
				string Message () const;
			private:
				string message;
		};

		OrderedSet (); 
		OrderedSet (const OrderedSet & other);
		~OrderedSet ();
		OrderedSet & operator = (const OrderedSet & other); 
		bool operator == (const OrderedSet & other);
		int Size () const;
		void SetDirection(dtype dir);
		dtype GetDirection () const;
		friend ostream & operator << <> (ostream & outs, const OrderedSet<ST> & S);
		void Forward(void function(const ST & param));
		void Backward(void function(const ST & param));
		void Clear ();
		bool IsEmpty () const;
		bool IsIn (const ST & value) const;
		bool Insert (const ST & value);
		bool Delete (const ST & value);
		OrderedSet operator + (const OrderedSet & other) const;
		OrderedSet operator * (const OrderedSet & other) const;

		Iterator begin () const;
		Iterator rbegin () const;
		Iterator end () const; 
		Iterator rend () const;
		ST operator [] (const int & index) const;

	private:
		Node * first;
		Node * last;
		int size;
		dtype direction;
		bool InsertFirst(const ST & value);
		bool InsertLast(const ST & value);
		bool DeleteFirst ();
		bool DeleteLast ();
};

/*********************************************************************************************************
 * Function : Node ()											 *
 * Parameters : none											 *
 * Return value : none											 *
 * Description : Default constructor for the Node class. This function will initialize the next and prev *
 * pointers of the Node class to NULL. The data value initialization is left to the data type class.     *
 * Data values of primities types may, or may not, be initialized (compiler dependent).			 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::Node::Node ()
{
	next = NULL; 
	prev = NULL; 
}

/*********************************************************************************************************
 * Function : OrderedSet ()									 	 *
 * Parameters : none											 *
 * Return value : none											 *
 * Description : Default constructor for the OrderedSet class. This function will initialize the size to *
 * zero, set the first and last pointers of the OrderedSet class to NULL, and set the direction of the   *
 * set to be FORWARD.											 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::OrderedSet ()
{
	size = 0; 
	first = NULL; 
	last = NULL; 
	direction = FORWARD; 
}
/*********************************************************************************************************
 * Function : OrderedSet (const OrderedSet & other) 							 *
 * Parameters : An existing OrderedSet of the same data type ST						 *
 * Return value : none											 *
 * Description : Copy constructor for the OrderedSet class. This function will copy the contents of the  *
 * OrderedSet passed as a parameter into a new OrderedSet. It accomplishes this by setting the new       *
 * OrderedSet's first pointer to NULL, and it's size to 0. A pointer is then assigned the address of the *
 * other OrderedSet's first pointer, and a for loop is used to have that pointer traverse the list until *
 * the end, InsertLast is used to insert each node's data into the new set (inserting last to preserve   *
 * it's order). Finally we set the new set's direction to be what the other set's direction is.          *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::OrderedSet (const OrderedSet & other)
{
	first = NULL;
	size = 0;
	for (Node * n = other.first; n != NULL; n = n->next)
		InsertLast(n->data);
	direction = other.direction;
}
/*********************************************************************************************************
 * Function : ~OrderedSet ()										 *
 * Parameters : none											 *
 * Return value : none											 *
 * Description : Desctructor for the OrderedSet class. This function will delete the contents of the     *
 * OrderedSet. It accomplishes this by calling DeleteFirst() while the pointer first is not NULL. First  *
 * would only be NULL if the list is empty, so as soon as the set is empty, the while loop ends.         *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::~OrderedSet ()
{
	Clear();
}

/*********************************************************************************************************
 * Function : operator = (const OrderedSet & other)							 *
 * Parameters : An existing OrderedSet of the same data type ST						 *
 * Return value : OrderedSet<ST>				 					 *
 * Description : Assignment operator for the OrderedSet class. This function will assign the contents of *
 * the parameter, other, to the current OrderedSet object. It first checks if the parameter has the same *
 * address as the current object, if it does, they are the same set, so return the object unmodified.    *
 * If the address is different, delete all of the nodes in the current list. Then copy the contents of   *
 * other into the current object (inserting last to preserve it's order), and set the direction of the   *
 * current object to be the direction of other. Finally, return the modified set. 			 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST> & OrderedSet<ST>::operator = (const OrderedSet & other)
{
	if (this == &other)
		return * this;
	while (!IsEmpty())
		DeleteFirst(); 
	for (Node * n = other.first; n != NULL; n = n->next)
		InsertLast(n->data);
	direction = other.direction; 
	return * this;
}

/*********************************************************************************************************
 * Function : operator == (const OrderedSet & other)							 * 
 * Parameters : An existing OrderedSet of the same data type ST (const because we will not modify it)    *
 * Return value : bool											 *
 * Description : Equality operator for the OrderedSet class. This function will determine if two sets    *
 * are equal. If the sets are not the same size, they are not equal, so return false. If they are the    *
 * same size, then create two temporary pointers. Have one point to the current set's first, and the     *
 * other point to the other set's first. Traverse through both sets, and if the data pointed to in the   *
 * current set is not equal to the data pointed to in the other set, the sets are not equal, so return   *
 * false. If the end of both sets is reached and all data values have been equal to eachother, the sets  *
 * are equal, so return true.									  	 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::operator == (const OrderedSet & other)
{
	if (size != other.size)
		return false;
	Node * temp = other.first;
	Node * this_temp = first; 
	while (this_temp)
	{
		if (this_temp->data != temp->data)
			return false; 
		this_temp = this_temp->next;
		temp = temp->next;
	}
	return true;
}

/*********************************************************************************************************
 * Function : Size () const										 *
 * Parameters : none											 *
 * Return value : size											 *
 * Description : Accessor function that will return the size of the OrderedSet. It is a const function   *
 * because it does not modify anything.									 *
 *********************************************************************************************************/
template <class ST>
int OrderedSet<ST>::Size () const
{
	return size;
}

/*********************************************************************************************************
 * Function : SetDirection (dtype dir)									 *
 * Parameters : An enumerated data type, dtype, that repesents the direction				 *
 * Return value : none											 *
 * Description : Mutator function that will set the direction of the OrderedSet to be the value passed	 *
 * as a parameter.											 *
 *********************************************************************************************************/
template <class ST>
void OrderedSet<ST>::SetDirection (dtype dir)
{
	direction = dir;
}

/*********************************************************************************************************
 * Function : operator << (ostream & outs, const OrderedSet<ST> & L)					 *
 * Parameters : An output stream variable, outs. And an OrderedSet of the same time ST. The OrderedSet   *
 * is passed as const to prevent modifications to it.							 *
 * Return value : ostream										 *
 * Description : This is a friend function ostream insertion operator. It will insert an OrderedSet into *
 * the output stream in propert format. If the set is empty, it will print out empty brackets {}. If the *
 * direction is FORWARD or BACKWARD it will print out the data from beginning to end, or the opposite.   * 
 * For both directions, if the size of the set is 1, it will print out one item in between the brackets. *
 * For a set with size greater than 1, it will print out items separated by commas. When we declare the  *
 * traversal pointers, we must use typename before, because i's followed by a qualified, dependent name  *
 * which referes to a type. We must also include the full declaration (OrderedSet<ST>::Node * p) because *
 * the friend function is not a member of the class, and it needs to know that the pointer is to a Node, *
 * that is a part of the OrderedSet class.								 *
 *********************************************************************************************************/
template <class ST>
ostream & operator << (ostream & outs, const OrderedSet<ST> & S)
{
	if (S.IsEmpty())
	{
		outs << "{}";
		return outs;
	}
	if (S.direction == FORWARD)
	{ 
		if (S.Size() == 1)
		{
			outs << "{" << S.first->data << "}";
			return outs;
		}
		outs << "{" << S.first->data << ", ";
		typename OrderedSet<ST>::Node * n;
		for (n = S.first->next; n != NULL; n = n->next)
		{
			if (n->next != NULL)
				outs << n->data << ", ";
			else
				outs << n->data;
		}
		outs << "}";
	}
	else // S.direction == BACKWARD
	{
		if (S.Size() == 1)
		{
			outs << "{" << S.first->data << "}";
			return outs;
		}
		outs << "{" << S.last->data << ", ";
		typename OrderedSet<ST>::Node * p;
		for (p = S.last->prev; p != NULL; p = p->prev)
		{
			if (p->prev != NULL)
				outs << p->data << ", ";
			else
				outs << p->data;
		}
		outs << "}";
	}
	return outs;
}

/*********************************************************************************************************
 * Function : InsertFirst (const ST & value)								 *
 * Parameters : const ST & value (const because will will not modify it)				 *
 * Return value : bool											 *
 * Description : This function will insert a new Node at the beginning of the OrderedSet.		 *
 * First, allocate memory for a new Node. If allocation fails, return false. If it was successful,	 *
 * assign the new Node's data the value passed as a parameter. Next check if other Nodes are in the set. *
 * If there are, then have the prev pointer from the first Node in the current set point to the new      *
 * Node. Then have the new Node's next pointer point to first. If the set is currently empty, set this   *
 * new Node to be the last Node. Then, regardless of the size of the set, have the first pointer point   *
 * to the new Node, increment the size by 1, and return true to indicate success.			 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::InsertFirst (const ST & value)
{
	Node * nnp = new Node;
	if (nnp == NULL)
		return false;
	nnp->data = value; 
	if (!IsEmpty())
	{
		first->prev = nnp;
		nnp->next = first;
	}
	else // If the set is empty
		last = nnp;
	first = nnp;
	size++;
	return true;
}

/*********************************************************************************************************
 * Function : InsertLast (const ST & value)								 *
 * Parameters : const ST & value									 *
 * Return value : bool											 *
 * Description : This function will insert a new Node at the end of the set. First it checks if the set  *
 * is empty, if so call InsertFirst(value) to insert the value. InsertFirst will return true if the Node *
 * was inserted, and false otherwise. If the set is not empty, allocate memory for a new Node. If	 *
 * allocation failed, return false. If allocation was successful, set the new Node's data to be value. 	 *
 * Then have last's next pointer point to the new node, making it the last in the set. Next have the     *
 * new Nodes prev pointer point to where last points (connecting the second to last and last Nodes).     *
 * Have the last pointer point to the new last node, increment size by 1, and return true to indicate    *
 * success.												 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::InsertLast(const ST & value)
{
	if (size == 0)
		return InsertFirst(value);
	Node * n = new Node;
	if (n == NULL)
		return false;
	n->data = value;
	last->next = n;
	n->prev = last;
	last = n;
	size++;
	return true;
}

/*********************************************************************************************************
 * Function : DeleteFirst ()										 *
 * Parameters : none											 *
 * Return value : bool										         *
 * Description : This function will delete the first Node in the set. First it checks if the Set is      *
 * empty, and returns false if so. Otherwise it's not empty, so we create a temporary Node pointer and   *
 * have it point to where the Set's first points to. Then have first point to it's next node, the second *
 * Node in the set. Then delete the address the temporary pointer points to, the first Node in the       *
 * set. Next, decrement the size by 1. Check if the set is now empty, if so set last and first to NULL.  *
 * If the set is not empty, set the new first Node's prev pointer to NULL. Then check if this is the     * 
 * only Node in the list, if so it is also the last, so have last point to first. Return true to         *
 * indicate success. 											 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::DeleteFirst ()
{
	if (first == NULL)
		return false;
	Node * temp = first;
	first = first->next;
	delete temp;
	size--;
	if (size == 0)
	{
		last = NULL;
		first = NULL;
	}
	if (size > 0)
		first->prev = NULL;
	if (size == 1)
		last = first;
	return true;
}

/*********************************************************************************************************
 * Function : DeleteLast ()										 *
 * Parameters : none											 *
 * Return value : bool										         *
 * Description : This function will delete the last Node in the set. First it checks to see if the set   *
 * is empty, if it is return false because their is nothing to delete. If the size is equal to 1, call   *
 * DeleteFirst() to delete the one Node in the set. It will return true if it was successful, and false  *
 * if not. If the size is greater than 1, create two temporary points. Temp will point to the last node, *
 * and second2last will point where last's prev pointer points (second to last Node). Next have the      *
 * second2last pointer point to NULL, because it will soon be the last Node. Then delete the address     *
 * that temp points to, which is the address of the last Node. Next, have the set's last pointer point   *
 * to second2last, making it the last Node in the set. Decrement the size by 1, and return true to 	 *
 * indicate success.											 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::DeleteLast ()
{
	if (size == 0)
		return false;
	if (size == 1)
		return DeleteFirst();
	// if (size > 1)
	Node * temp = last;
	Node * second2last = last->prev;
	second2last->next = NULL;
	delete temp;
	last = second2last;
	size--;
	return true;
}

/*********************************************************************************************************
 * Function : Forward(void function(const ST & param))							 *
 * Parameters : void function(const ST & param)								 *
 * Return value : none											 *
 * Description : This function will access the set's data in forward order. It accomplishes this with    *
 * help of a void function that is passed as a parameter. For example, if the void function is called    *
 * WriteOut(const string & v) it will pass every Node's string data to WriteOut, which then writes the   *
 * data to the output stream.										 *
 *********************************************************************************************************/
template <class ST>
void OrderedSet<ST>::Forward(void function(const ST & param))
{
	for (Node * n = first; n; n = n->next)
		function(n->data);
}

/*********************************************************************************************************
 * Function : Backward(void function(const ST & param))							 *
 * Parameters : void function(const ST & param))							 *
 * Return value : none											 *
 * Description : This function will access the set's data in backward order. It accomplishes this with   *
 * the help of a void function that is passed as a parameter. Every Node's data in the list is then      *
 * passed to the void function, which will perform it's function on the data. (see Forward above for     *
 * example).												 *
 *********************************************************************************************************/
template <class ST>
void OrderedSet<ST>::Backward(void function(const ST & param))
{
	for (Node * n = last; n; n = n->prev)
		function(n->data);
}

/*********************************************************************************************************
 * Function : Clear ()											 *
 * Parameters : none											 *
 * Return value : none											 *
 * Description : This function will clear all elements of the list. It accomplishes this with a while    *
 * loop. As long as first does not point to NULL, call DeleteFirst(). When first does point to NULL, that*
 * means it does not point to a Node, which means the set is empty, so the while loop exits, and the set *
 * is cleared. 												 *
 ********************************************************************************************************/
template <class ST>
void OrderedSet<ST>::Clear ()
{
	while(first)
		DeleteFirst();
}

/*********************************************************************************************************
 * Function : IsEmpty() const										 *
 * Parameters : none											 *
 * Return value : bool											 *
 * Description : This function will determine if the set is empty. It accomplishes this by checking if   *
 * the set's size is equal to 0. If it is return true. If the set is not empty, return false. This is a  *
 * const function because it does not modify anything.							 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::IsEmpty () const
{
	if (size == 0)
		return true;
	return false;
}

/*********************************************************************************************************
 * Function : IsIn (const ST & value) const 								 *
 * Parameters : const ST & value (const value because it is not modified)				 *
 * Return value : bool											 *
 * Descriptoin : This function will determine if a value is in the set. It uses a linear search to	 *
 * traverse every Node in the set. If it finds a Node whose data matches value, return true.		 *
 * If we've reached the end of the set and we haven't found a Node whose data matches value, return 	 *
 * false. This is a const function because it does not modify anything.					 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::IsIn (const ST & value) const
{
	for (Node * n = first; n != NULL; n = n->next)
	{
		if (n->data == value)
			return true;
	}
	return false;	
}

/*********************************************************************************************************
 * Function : Insert (const ST & value)									 *
 * Parameters : const ST & value (const value because it is not modified)				 *
 * Return value : bool											 *
 * Description : This function will maintain the Nodes of the set in ascending order based on the Node	 *
 * data. Duplicate items are not permitted. First we check if the value is in the set. If so return false*
 * Next check if the set is empty, if so call InsertFirst(value). If the value is not in the set, and the* 
 * set isn't empty, check if the value we want to insert is less than the data pointed to by first. 	 *
 * If so call InsertFirst(value). If value is greater than the value pointed to by last, call 		 *
 * InsertLast(value). If it's inbetween these values, we'll need to create a new Node that will be	 *
 * inserted in the proper location in the set. First check if new Node allocation failed, if so return	 *
 * false. If successful, assign value to the Node's data. Then create 2 helper pointers of Node type, 	 *
 * called left and right. Have right point to first. Now begin traversal. As long as the data pointed	 *
 * to by right is less than value, have right point to it's next. As soon as right's data is greater	 *
 * than value, we have found the insertion position for the new Node. Have left point to where right's	 *
 * prev points, have the new Nodes prev point to left, have left's next point to new Node, have new	 * 
 * Node's next point to right, and have right's prev point to the new Node. This will successfully 	 *
 * insert the new Node and attach all links appropriately. We then increment the size of the set by 1 	 *
 * and  return true to indicate success.								 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::Insert (const ST & value)
{
	if (IsIn(value))
		return false;
	if (IsEmpty())
		return InsertFirst(value);
	if (value < first->data)
		return InsertFirst(value);
	if (last->data < value)
		return InsertLast(value);
	Node * nnp = new Node;
	if (nnp == NULL)
		return false;
	nnp->data = value;
	Node * left, * right = first;
	while (right->data < value)
		right = right->next;
	left = right->prev;
	nnp->prev = left;
	left->next = nnp;
	nnp->next = right;
	right->prev = nnp;
	size++;
	return true;
}

/*********************************************************************************************************
 * Function : Delete (const ST & value)									 *
 * Parameters : const ST & value									 *
 * Return value : bool											 *
 * Description : This function will remove a Node from the set that has value as it's data, if it exists.*
 * First, check if the value is not in the set, if it's not return false. If the data in the first Node	 *
 * is equal to value, return DeleteFirst(). If the data in the last Node is equal to value, return 	 *
 * DeleteLast(). If it's not the first or last's data it must be in the middle. So we create a temporary *
 * pointer, have it point to first, and traverse through the list while temp's data is not equal to value*
 * When it is equal to value the while loop breaks, and temp is now pointing to the Node that will be	 *
 * deleted. First create two more temporary Node pointers (left and right), to point to temps prev (left)*
 * and temps next (right). Now link up the Nodes surrounding temp by having right's prev point to left,  *
 * left's next point to right. Delete temp, the Node that contains value. Decrement the size by 1,	 *
 * and return true to indicate success.									 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::Delete (const ST & value)
{
	if (!IsIn(value))
		return false;
	if (first->data == value)
		return DeleteFirst();
	if (last->data == value)
		return DeleteLast();
	Node * temp = first;
	while (temp->data != value)
		temp = temp->next;
	Node * left = temp->prev;
	Node * right = temp->next;
	right->prev = left;
	left->next = right;
	delete temp;
	size--;
	return true;	

}

/*********************************************************************************************************
 * Function : operator + (const OrderedSet & other) const						 *
 * Parameters : const OrderedSet & other								 *
 * Return value : OrderedSet<ST>									 *
 * Description : This function is the overloaded addition operator for the OrderedSet class. It is a 	 *
 * constant function because it will not modify the current OrderedSet object. This operator will 	 *
 * return the set that is the union of two ordered sets. It accomplishes this by first checking if the 	 *
 * OrderedSet passed as a parameter has the same memory address as the current OrderedSet object. If it  *
 * does then they have the same contents, so return the current object. If their addresses are different *
 * and the set passed as a parameter is empty, return the current set because their is nothing to add. 	 *
 * If the addresses are different and the other set is not empty, create a new OrderedSet called U, and	 *
 * assign it the contents of the current set. Then traverse the other set, and if any data is not in U,	 *
 * insert it. When traversal has ended return U, the union of two OrderedSets.				 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST> OrderedSet<ST>:: operator + (const OrderedSet & other) const
{
	if (this == &other)
		return * this;
	if (other.IsEmpty())
		return * this;
	OrderedSet <ST> U = *this;
	for (Node * n = other.first; n != NULL; n = n->next)
	{
		if (!U.IsIn(n->data))
			U.Insert(n->data);
	}	
	return U;
}

/*********************************************************************************************************
 * Function : operator * (const OrderedSet & other) const						 *
 * Parameters: const OrderedSet & other									 *
 * Return value : OrderedSet<ST>									 *
 * Description : This function is the overloaded multiplication operator for the OrderedSet class.	 *
 * It is a constant function because it will not modify the current OrderedSet object. This operator 	 *
 * will return the set that is the intersection of two OrderedSet objects. It accomplishes this by first *
 * checking to see if the parameter has the same address as the current object, if so return the current *
 * obejct. If the set passed as a parameter is empty, create a new, empty OrderedSet, I, and return it.	 *
 * If the addresses are different and the other set is not empty, use the copy constructor to create I,  *
 * a copy of the current Orderedset object. Then for every Node in I, check if it's data is not in the	 *
 * other set. If it's not, delete it from from I. When finished traversing return I, the intersection of *
 * two OrderedSets.											 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST> OrderedSet<ST>:: operator * (const OrderedSet & other) const
{
	if (this == &other)
		return * this;
	if (other.IsEmpty())
	{
		OrderedSet <ST> I;
		return I;
	}
	OrderedSet <ST> I = * this;
	for (Node * n = I.first; n != NULL; n = n->next)
	{
		if (!other.IsIn(n->data))
			I.Delete(n->data);
	}		
	return I;
}

/*********************************************************************************************************
 * Function : operator [] (const int & index) const							 *
 * Parameters : const int & index									 *
 * Return value : ST											 *
 * Description : This function is the overloaded indexing (subscript) operator for the OrderedSet class. *
 * It is a const function because it will not modify the current OrderedSet object.			 *
 * It will be used to access elements of the list by an index value. This function returns a reference	 *
 * type. This causes it to be an l-value, allowing you to use subscripted expressions on either side of	 *
 * assignment operators. Start by checking if the index value is less than 0, if so throw an exception	 *
 * to the user with the index value as the parameter, because it is out of bounds. If the index value	 *
 * is greater than or equal to the size, throw an exception with the index value as the parameter,	 *
 * because it is out of bounds. If it's within bounds, traverse the list index-1 times and return that	 *
 * Nodes data.												 *
 *********************************************************************************************************/
template <class ST>
ST OrderedSet<ST>::operator [] (const int & index) const
{
	if (index < 0) 
		throw (Exception(index));
	if (index >= size)
		throw (Exception(index));
	typename OrderedSet<ST>::Node * n = first;
	for (int i = 0; i < index; i++)
		n = n->next;
	return n->data;
}

/*********************************************************************************************************
 * Function: Iterator ()										 *
 * Parameters : none											 *
 * Return value : none											 *
 * Description : This function is the default constructor for an Iterator object. It will set it's Node  *
 * pointer current to NULL.										 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::Iterator::Iterator ()
{ 
	current = NULL;
}

/*********************************************************************************************************
 * Function : Iterator (Node * NP) 									 *
 * Parameters : Node * NP										 *
 * Return value : none											 *
 * Description : This is the copy constructor for an Iterator object. It will set it's Node pointer	 *
 * current to point to NP.										 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::Iterator::Iterator (Node * NP)
{ 
	current = NP;
}

/*********************************************************************************************************
 * Function : Iterator:: operator * () const 								 *
 * Parameter : none											 *
 * Return value : ST											 *
 * Description : This function overloads the dereferencing operator for the Iterator class. If the 	 *
 * iterator object's current pointer points to NULL, throw an exception. Otherwise return the data	 *
 * pointed to by current. 										 *
 *********************************************************************************************************/
template <class ST>
const ST OrderedSet<ST>::Iterator::operator * () const
{
	if (current == NULL)
		throw (Exception("Cannot dereference a NULL pointer"));
	return current->data;
}

/*********************************************************************************************************
 * Function :  OrderedSet<ST>::Iterator:: operator ++ ()						 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function overloads the pre-increment operator for the Iterator class. First, try	 *
 * to check if the Iterators current is pointing to NULL, if so throw an exception. Otherwise go to the  *
 * next Node, and return the Iterator. If an exception is thrown, catch it and print a message through   *
 * the cerr stream, and exit.										 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator:: operator ++ ()
{
	if (current == NULL) 
		throw (Exception("Cannot increment a NULL iterator"));
	current = current->next; 
	return *this; 
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::Iterator:: operator ++ (int)						 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function overloads the post-increment operator for the Iterator class. It 	 *
 * accomplishes this by first creating copy of the current Iterator object. Then try and check if the	 *
 * current Iterator's current pointer points to NULL, if so throw an exception. Otherwise go to the 	 *
 * next Node, and return the copy of the Iterator made at the beginning. If an exception is thrown it    *
 * will be caught and passed to the cerr stream, and then the program will exit.			 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator:: operator ++ (int)
{
	Iterator itr = *this;
	if (current == NULL)
		throw (Exception("Cannot increment a NULL iterator"));
	current = current->next; 
	return itr; 
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::Iterator:: operator -- ()							 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function overloads the pre-decrement operator for the Iterator class. First check  *
 * if the current Iterator's current is pointing to NULL, if so throw an exception. Otherwise go to the  *
 * current's prev Node, and return the current Iterator. If an exception is thrown it will be caught 	 *
 * and and displayed through the cerr stream, and the program will exit.				 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator:: operator -- ()
{
	if (current == NULL)
		throw (Exception("Cannot decrement a NULL iterator"));
	current = current->prev; 
	return *this; 
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::Iterator:: operator -- (int)						 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator 							 *
 * Description : This function overloads the post-decrement operator for Iterators. It accomplishes this *
 * by first creating an Iterator that is a copy of the current Iterator object. Then try and check if	 * 
 * the current Iterator's current pointer is pointing to NULL, if so throw an exception. Otherwise go to *
 * current's prev Node, and return the copy of the iterator. If an exception is thrown it will be caught *
 * and displayed by the cerr stream, and the program will exit.						 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator:: operator -- (int)
{
	Iterator itr = *this;
	if (current == NULL) 
		throw (Exception("Cannot decrement a NULL iterator"));
	current = current->prev;  
	return itr;
}

/*********************************************************************************************************
 * Function : Iterator::operator == (const Iterator & other) const					 *
 * Parameters : const Iterator & other									 *
 * Return value : bool											 *
 * Description : This function overloads the equality operator for Iterators. It will return the boolean *
 * value of the equality comparison between the current Iterator's current and the other Iterator's 	 *
 * current. 												 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::Iterator::operator == (const Iterator & other) const
{
	return current == other.current;
}

/*********************************************************************************************************
 * Function : Iterator::operator != (const Iterator & other) const					 *
 * Parameters : const Iterator & other									 *
 * Return value : bool											 *
 * Description : This function overloads the not equal operator for Iterators. It will return the boolean*
 * value of the not equal comparison for the current Iterator's current, and the other Iterator's 	 *
 * current.												 *
 *********************************************************************************************************/
template <class ST>
bool OrderedSet<ST>::Iterator::operator != (const Iterator & other) const
{
	return current != other.current;
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::begin () const								 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function creates an Iterator and sets it's Node pointer equal to the first Node	 *
 * in the set.												 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::begin () const
{
	Iterator temp (first);
	return temp;
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::rbegin () const								 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function creates an Iterator and sets it's Node pointer equal to the last Node	 *
 * in the set.												 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rbegin () const
{
	Iterator temp (last);
	return temp;
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::end() const								 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function creates an iterator with it's default constructor, and simply returns it. *
 * It's Node pointer will be set to NULL, which will be useful for traversal. 				 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::end () const
{
	Iterator temp;
	return temp;
}

/*********************************************************************************************************
 * Function : OrderedSet<ST>::rend() const								 *
 * Parameters : none											 *
 * Return value : typename OrderedSet<ST>::Iterator							 *
 * Description : This function creates an iterator with it's default constructor, and simply returns it. *
 * It's Node pointer will be set to NULL, which will be useful for traversal.  				 *
 *********************************************************************************************************/
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rend () const
{
	Iterator temp;
	return temp;
}

/*********************************************************************************************************
 * Function : Exception::Exception ()									 *
 * Parameters : none											 *
 * Return value : none											 *
 * Description : Default constructor for an Exception object. It is left blank.				 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::Exception::Exception ()
{
}

/*********************************************************************************************************
 * Function : Exception::Exception (string msg)								 *
 * Parameters : string msg										 *
 * Return value : none											 *
 * Description : This is a parameterized constructor for an Exception object. It is passed a string, and *
 * the Exception objects message is set to that strings value.						 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::Exception::Exception (string msg)
{
	message = msg;
}

/*********************************************************************************************************
 * Function : Exception::Exception (int indx)								 *
 * Parameters : int indx										 *
 * Return value : none											 *
 * Description : This is a parameterized constructor for an Exception object. It is passed an integer,	 *
 * a stringstream object is created, an error message with the indx is sent to the stringstream.	 *
 *********************************************************************************************************/
template <class ST>
OrderedSet<ST>::Exception::Exception (int indx)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << "Subscript [" << indx << "] out of range";
	getline(ss, message);
}

/*********************************************************************************************************
 * Function : Exception::Message () const								 *
 * Parameters : none											 *
 * Return value : string										 *
 * Description : This function is an accessor function for the Exception class that will return the	 *
 * value of it's string message.									 *
 *********************************************************************************************************/
template <class ST>
string OrderedSet<ST>::Exception::Message () const
{
	return message;
}

#endif
