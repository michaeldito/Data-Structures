#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <iostream>
using namespace std;

bool testing = false;

enum dtype { FORWARD, BACKWARD };

template <class LT> class SinglyLinkedList;
template <class LT> ostream & operator << (ostream & outs, const SinglyLinkedList<LT> & L);

template <class LT>
class SinglyLinkedList
{
	private:
		struct Node 
		{
			Node();
			void PrintNode(ostream & output);
			LT data;
			Node * next;
		};
	public:
		SinglyLinkedList();
		SinglyLinkedList(const SinglyLinkedList & other);
		~SinglyLinkedList();
		SinglyLinkedList & operator = (const SinglyLinkedList & other);
		bool operator == (const SinglyLinkedList & other);
		int Size () const;
		void SetDirection(dtype dir);
		dtype GetDirection() const;
		friend ostream & operator << <> (ostream & outs, const SinglyLinkedList<LT> & L);
		bool InsertFirst(const LT & value);
		bool InsertLast(const LT & value);
		bool DeleteFirst();
		bool DeleteLast();
		void Forward(void function(const LT & param));
	private:
		Node * first;
		Node * last;
		int size;
		dtype direction;
};

/* Function : Node()
 * Return value : none
 * Parameters : none
 * Description : This is the default constructor for the Node struct. It initializes nexto to NULL.
 */
template <class LT>
SinglyLinkedList<LT>::Node::Node()
{ 
	if (testing) { cout << "Node default constructor called for address: " << this << endl; }
	next = NULL;
}

/* Function : PrintNode(ostream & output)
 * Return value : none
 * Parameters : ostream & output
 * Description : This function will print out the contents of an Node.
 */
template <class LT>
void SinglyLinkedList<LT>::Node::PrintNode(ostream & output)
{
	if(next != NULL)
		next->PrintNode(output);
	if(next != NULL)
		output << ' ';
	output << data;
}

/* Function : SinglyLinkedList()
 * Return value : none
 * Parameters : none
 * Description : This is the default constructor for a SinglyLinkedList object. It will initialize size to 0,
 * first to NULL, and set the traversal direction to FORWARD.
 */
template <class LT>
SinglyLinkedList<LT>::SinglyLinkedList()
{
	size = 0; 
	first = NULL;
	last = NULL;
	direction = FORWARD; 
}

/* Function : SinglyLinkedList(const SinglyLinkedList & other)
 * Return value : none
 * Parameters :const SinglyLinkedList & other
 * Description : This is the copy constructor for the SinglyLinkedList class. It will instantiate a new SinglyLinkedList object
 * that is a copy of the SinglyLinkedList passed as a parameter. 
 */
template <class LT>
SinglyLinkedList<LT>::SinglyLinkedList(const SinglyLinkedList & other)
{ 
	first = NULL;
	last = NULL;
	size = 0; 
	for (Node * n = other.first; n != NULL; n = n->next) 
		InsertLast(n->data); 
	direction = other.direction;
}

/* Function : ~SinglyLinkedList()
 * Return value : none
 * Parameters : none
 * Description : This is the destructor for the SinglyLinkedList class. It will call DeleteFirst as long as there
 * is a Node pointed to by first.
 */
template <class LT>
SinglyLinkedList<LT>::~SinglyLinkedList()
{
		while(DeleteFirst());
}

/* Function : operator = (const SinglyLinkedList<LT> & other)
 * Return value : none
 * Parameters : const SinglyLinkedList<LT> & other
 * Description : This is the overloaded assignment operator for the SinglyLinkedList class. It wil assign the contents
 * of the right hand operand to be the contents of the left hand operand.
 */
template <class LT>
SinglyLinkedList<LT> & SinglyLinkedList<LT>::operator = (const SinglyLinkedList<LT> & other)
{
	if (this == &other) 
		return * this;
	while (first)
		DeleteFirst();
	for (Node * n = other.first; n != NULL; n = n->next)
		InsertLast(n->data);
	direction = other.direction;
	return * this;
}

/* Function : operator == (const SinglyLinkedList & other) 
 * Return value : bool
 * Parameters : const SinglyLinkedList & other
 * Description : This is the overloaded equality operator for the SinglyLinkedList class. It will compare two SinglyLinkedLists
 * to see if the data they contain is identical. If it is, return true. If not, return false.
 */
template <class LT>
bool SinglyLinkedList<LT>::operator == (const SinglyLinkedList & other)
{
	if (size != other.size) 
		return false;
	Node * temp = other.first;
	Node * this_temp = first; 
	while (this_temp != NULL && temp != NULL)
	{
		if (this_temp->data != temp->data)
			return false;
		this_temp = this_temp->next;
		temp = temp->next;
	}
	return true;
}

/* Function : Size() const
 * Return value : int
 * Parameters : none
 * Description : This is an accessor function for the SinglyLinkedList class. It will return the size of the SinglyLinkedList.
 */
template <class LT>
int SinglyLinkedList<LT>::Size() const
{ 
	return size; 
}

/* Function : SetDirection(dtype dir)
 * Return value : none
 * Parameters : dtype dir
 * Description : This is a mutator function for the SinglyLinkedList class. It will set the traversal direction to be
 * the value passed as a parameter. It accepts an enumerated type as a parameter.
 */
template <class LT>
void SinglyLinkedList<LT>::SetDirection(dtype dir)
{
	direction = dir;
}

/* Function : ostream & operator << (ostream & outs, const SinglyLinkedList<LT> & L)
 * Return value : ostream
 * Parameters : ostream & outs, const SinglyLinkedList<LT> & L
 * Description : This is a friend function of the SinglyLinkedList class. It is the insertion operator. It will insert 
 * the contents of the SinglyLinkedList into the output stream in FORWARD or BACKWARD order.
 */
template <class LT>
ostream & operator << (ostream & outs, const SinglyLinkedList<LT> & L)
{
	if (L.first == NULL)
		return outs;
	if (L.direction == FORWARD) 
	{
		outs << L.first->data;
		typename SinglyLinkedList<LT>::Node * n;
		for (n = L.first->next; n != NULL; n = n->next)
			outs << ' ' << n->data;
	}
	else // L.direction == BACKWARD
		L.first -> PrintNode(outs);
	return outs;
}

/* Function : InsertFirst(const LT & value)
 * Return value : bool
 * Parameters : const LT & value
 * Description : This function will insert a Node at the front of the SinglyLinkedList.
 */
template <class LT>
bool SinglyLinkedList<LT>::InsertFirst(const LT & value)
{
	Node * nnp = new Node; 
	if (nnp == NULL)
		return false;
	nnp->data = value;
	nnp->next = first;
	first = nnp; 
	if (size == 0)
		last = nnp;
	size++; 
	return true;
}

/* Function : InsertLast(const LT & value)
 * Return value : bool
 * Parameters : const LT & value
 * Description : This function will insert a Node at the end of the SinglyLinkedList.
 */
template <class LT>
bool SinglyLinkedList<LT>::InsertLast(const LT & value)
{
	if (size == 0)
		return InsertFirst(value);
	Node * n = new Node;
	if (n == NULL)
		return false;
	n->data = value;
	n->next = NULL;
	last->next = n;
	last = n;
	size++;
	return true;
}

/* Function : DeleteFirst()
 * Return value : bool
 * Parameters : none
 * Description : This function will delete the first Node in the SinglyLinkedList.
 */
template <class LT>
bool SinglyLinkedList<LT>::DeleteFirst()
{
	if (size == 0)
		return false;
	Node * temp = first; 
	first = first->next;
	delete temp; 
	size--;
	return true;
}

/* Function : DeleteLast()
 * Return value : bool
 * Parameters : none
 * Description : This function will delete the last Node in the SinglyLinkedList.
 */
template <class LT>
bool SinglyLinkedList<LT>::DeleteLast()
{ 
	if (size == 0)
		return false;
	if (size == 1)
		return DeleteFirst();
	Node * temp = last;
	Node * second2last = first;
	while (second2last->next != last)
		second2last = second2last->next;
	second2last->next = NULL;
	delete temp;
	last = second2last;
	size--;
	return true;
}

/* Function : Forward(void function(const LT & param))
 * Return value : none
 * Parameters : void function(const LT& param))
 * Description : This function will assist in printing out the SinglyLinkedList in FORWARD direction. 
 */
template <class LT>
void SinglyLinkedList<LT>::Forward(void function(const LT & param))
{
	for (Node * n = first; n; n = n->next)
		function(n->data);
}

#endif
