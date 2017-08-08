#include "ArrayBag.hpp"

template <class BagType>
ArrayBag<BagType>::ArrayBag(): bag_count_(0), bag_max_items_(kDefaultCapacity_) {}

template <class BagType>
int ArrayBag<BagType>::GetSize() const{
  return bag_count_;
}

template <class BagType>
bool ArrayBag<BagType>::IsEmpty() const {
  return bag_count_ == 0;
}

template <class BagType>
bool ArrayBag<BagType>::Add(const BagType& entry) {
  bool room_to_add = (bag_count_ < bag_max_items_);
    if(room_to_add) {
      bag_[bag_count_] = entry;
      bag_count_++;
    }
    return room_to_add;
}

template <class BagType>
bool ArrayBag<BagType>::Remove(const BagType& entry) {
  int remove_index = GetIndexOf(entry);
  bool remove_allowed = !IsEmpty() && (remove_index > -1);
  if (remove_allowed) {
    bag_[remove_index] = bag_[bag_count_ - 1];
    bag_count_--;
  }
  return remove_allowed;
}

template <class BagType>
void ArrayBag<BagType>::Clear() {
  bag_count_ = 0;
}

template <class BagType>
bool ArrayBag<BagType>::Contains(const BagType& entry) const {
  for(int i = 0; i < bag_count_; ++i) {
    if (bag_[i] == entry)
      return true;
  }
  return false;
}

template <class BagType>
int ArrayBag<BagType>::GetFrequencyOf(const BagType& entry) const {
  int frequency = 0;
  int current_index = 0;
  while (current_index < bag_count_) {
    if (bag_[current_index] == entry)
     frequency++;
    current_index++;
  }
  return frequency;
}

template <class BagType>
std::vector<BagType> ArrayBag<BagType>::ToVector() const {
  std::vector<BagType> vector_bag;
  for (int i = 0; i < bag_count_; ++i) {
    vector_bag.push_back(bag[i]);
  }
  return vector_bag;
}

template <class BagType>
int ArrayBag<BagType>::GetIndexOf(const BagType& target) const {
  for(int i = 0; i < bag_count_; ++i) {
    if (bag_[i] == target)
      return i;
  }
  return -1;
}
