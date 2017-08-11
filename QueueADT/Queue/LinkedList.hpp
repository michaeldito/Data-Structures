#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "ListInterface.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcept.hpp"

template <class ListType>
class LinkedList : public ListInterface<ListType> {
 public:
   LinkedList();
   LinkedList(const LinkedList<ListType>& L);
   virtual ~LinkedList();

   bool IsEmpty() const;
   int GetLength() const;
   bool Insert(int position, const ListType& entry);
   bool Remove(int position);
   void Clear();
   ListType GetEntry(int position) const throw(PrecondViolatedExcept);
   ListType Replace(int position, const ListType& entry) throw(PrecondViolatedExcept);

 private:
   std::shared_ptr<Node<ListType>> head_;
   int list_count_;

   auto GetNodeAt(int position) const;
};

#include "LinkedList.cpp"
#endif
