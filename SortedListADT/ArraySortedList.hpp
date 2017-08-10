#ifndef ARRAY_SORTED_LIST_
#define ARRAY_SORTED_LIST_

#include <memory>
#include "SortedListInterface.hpp"
#include "PrecondViolatedExcept.hpp"

template <class ListType>
class ArraySortedList : public SortedListInterface<ListType> {
 public:
   ArraySortedList();
   virtual ~ArraySortedList();

   bool InsertSorted(const ListType& entry);
   bool RemoveSorted(const ListType& entry) throw(PrecondViolatedExcept);
   int GetPosition(const ListType& entry) const;
   bool IsEmpty() const;
   int GetLength() const;
   bool Remove(int position) throw(PrecondViolatedExcept);
   void Clear();
   ListType GetEntry(int position) const throw(PrecondViolatedExcept);

 private:
   static const int kDefaultCapacity_ = 2;
   ListType* list_;
   int list_count_;
   int max_capacity_;
};

#include "ArraySortedList.cpp"
#endif
