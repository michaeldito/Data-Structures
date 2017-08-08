#ifndef ARRAY_LIST_
#define ARRAY_LIST_

#include "ListInterface.hpp"
#include "PrecondViolatedExcept.hpp"

template <class ListType>
class ArrayList : public ListInterface<ListType> {
 public:
   ArrayList();
   bool IsEmpty() const;
   int GetLength() const;
   bool Insert(int position, const ListType& entry);
   bool Remove(int position);
   void Clear();
   ListType GetEntry(int position) const throw(PrecondViolatedExcept);
   ListType Replace(int position, const ListType& entry) throw(PrecondViolatedExcept);

 private:
   static const int kDefaultCapacity_ = 100;
   ListType list_[kDefaultCapacity_ + 1];
   int list_count_;
   int max_capacity_;
};

#include "ArrayList.cpp"
#endif
