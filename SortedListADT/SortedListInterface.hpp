#ifndef SORTED_LIST_INTERFACE_
#define SORTED_LIST_INTERFACE_

template <class ListType>
class SortedListInterface {
 public:
   virtual bool InsertSorted(const ListType& entry) = 0;
   virtual bool RemoveSorted(const ListType& entry) = 0;
   virtual int GetPosition(const ListType& entry) const = 0;
   virtual bool IsEmpty() const = 0;
   virtual int GetLength() const = 0;
   virtual bool Remove(int position) = 0;
   virtual void Clear() = 0;
   virtual ListType GetEntry(int position) const = 0;
   virtual ~SortedListInterface() {}
};

#endif
