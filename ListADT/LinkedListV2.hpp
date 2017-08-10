#ifndef LINKED_LIST_V2_
#define LINKED_LIST_V2_

#include "ListInterface.hpp"
#include "NodeV2.hpp"
#include "PrecondViolatedExcept.hpp"

template <class ListType>
class LinkedListV2 : public ListInterface<ListType> {
 public:
   LinkedListV2();
   LinkedListV2(const LinkedListV2<ListType>& L);
   virtual ~LinkedListV2();

   bool IsEmpty() const;
   int GetLength() const;
   bool Insert(int position, const ListType& entry);
   bool Remove(int position);
   void Clear();
   ListType GetEntry(int position) const throw(PrecondViolatedExcept);
   ListType Replace(int position, const ListType& entry) throw(PrecondViolatedExcept);

 private:
   std::shared_ptr<NodeV2<ListType>> head_;
   int list_count_;

   auto GetNodeAt(int position) const;
};

#include "LinkedListV2.cpp"
#endif
