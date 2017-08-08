#ifndef ARRAY_BAG_
#define ARRAY_BAG_

#include "BagInterface.hpp"

template <class BagType>
class ArrayBag : public BagInterface<BagType> {
 public:
   ArrayBag();
   int GetSize() const;
   bool IsEmpty() const;
   bool Add(const BagType& entry);
   bool Remove(const BagType& entry);
   void Clear();
   bool Contains(const BagType& entry) const;
   int GetFrequencyOf(const BagType& entry) const;
   std::vector<BagType> ToVector() const;

 private:
   static const int kDefaultCapacity_ = 10;
   BagType bag_[kDefaultCapacity_];
   int bag_count_;
   int bag_max_items_;

   int GetIndexOf(const BagType& target) const;
};

#include "ArrayBag.cpp"
#endif
