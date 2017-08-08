#ifndef LINKED_BAG_
#define LINKED_BAG_

#include "BagInterface.hpp"
#include "Node.hpp"

template <class BagType>
class LinkedBag : public BagInterface<BagType> {
 public:
  LinkedBag();
  LinkedBag(const LinkedBag<BagType>& bag);
  virtual ~LinkedBag();
  int GetSize() const;
  bool IsEmpty() const;
  bool Add(const BagType& entry);
  bool Remove(const BagType& entry);
  void Clear();
  bool Contains(const BagType& entry) const;
  int GetFrequencyOf(const BagType& entry) const;
  std::vector<BagType> ToVector() const;

 private:
  Node<BagType>* head_;
  int bag_count_;
  Node<BagType>* GetPointerTo(const BagType& target) const;
};

#include "LinkedBag.cpp"
#endif
