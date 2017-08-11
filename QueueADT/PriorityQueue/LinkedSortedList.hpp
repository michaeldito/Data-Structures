#ifndef LINKED_SORTED_LIST_
#define LINKED_SORTED_LIST_

#include <memory>
#include "SortedListInterface.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcept.hpp"
#include "MemoryAllocationExcept.hpp"

template <class ListType>
class LinkedSortedList : public SortedListInterface<ListType> {
 public:
   LinkedSortedList();
   LinkedSortedList(const LinkedSortedList<ListType>& L);
   virtual ~LinkedSortedList();

   bool InsertSorted(const ListType& entry) throw(MemoryAllocationExcept);
   bool RemoveSorted(const ListType& entry);
   int GetPosition(const ListType& entry) const;
   bool IsEmpty() const;
   int GetLength() const;
   bool Remove(int position);
   void Clear();
   ListType GetEntry(int position) const throw(PrecondViolatedExcept);

 private:
   std::shared_ptr<Node<ListType>> head_;
   int list_count_;

   auto GetNodeBefore(const ListType& entry) const;
   auto GetNodeAt(int position) const;
   auto CopyChain(const std::shared_ptr<Node<ListType>>& original_chain_ptr);
};

#include "LinkedSortedList.cpp"
#endif
