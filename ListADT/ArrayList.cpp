#include "ArrayList.hpp"

template <class ListType>
ArrayList<ListType>::ArrayList(): list_count_(0), max_capacity_(kDefaultCapacity_) {
  list_ = new ListType[max_capacity_ + 1];
}

template <class ListType>
bool ArrayList<ListType>::IsEmpty() const {
  return list_count_ == 0;
}

template <class ListType>
int ArrayList<ListType>::GetLength() const {
  return list_count_;
}

template <class ListType>
bool ArrayList<ListType>::Insert(int position, const ListType& entry) throw(MemoryAllocationExcept) {
  bool able_to_insert = (position >= 1) &&
                        (position <= list_count_ + 1) &&
                        (list_count_ < max_capacity_);

  if (able_to_insert) {
    // Make room for new entry by shifting all entries at positions
    // from list_count_ down to position
    // (no shift if position == list_count_ + 1)
    for (int i = list_count_; i >= position; i--)
      list_[i + 1] = list_[i];

    // Insert new entry
    list_[position] = entry;
    list_count_++;
  }

  bool need_to_expand = list_count_ >= max_capacity_;
  if (need_to_expand) {
    // Copy all items into new larger array.
    max_capacity_ += max_capacity_ / 2;
    ListType* new_list = new ListType[max_capacity_ + 1];
    if (new_list == nullptr) {
      throw MemoryAllocationExcept();
      return false;
    }
    for (int i = 1; i <= list_count_; i++)
      new_list[i] = list_[i];
    delete [] list_;
    list_ = new_list;
  }

  return true;
}

template <class ListType>
bool ArrayList<ListType>::Remove(int position) {
  bool able_to_remove = (position >= 1) && (position <= list_count_);
  if (able_to_remove) {
    // Remove entry by shifting all entries after the one at
    // position toward the beginning of the ArrayList
    // (no shift if position == list_count_)
    for (int i = position; i < list_count_; i++)
      list_[i] = list_[i + 1];

    list_count_--;
  }
  return able_to_remove;
}

template <class ListType>
void ArrayList<ListType>::Clear() {
  list_count_ = 0;
}

template <class ListType>
ListType ArrayList<ListType>::GetEntry(int position) const throw(PrecondViolatedExcept) {
  // Enforce Precondition
  bool able_to_get = (position >= 1) && (position <= list_count_);
  if (able_to_get) {
    return list_[position];
  } else {
      std::string message = "GetEntry() called with an empty list or invalid position.";
      throw PrecondViolatedExcept(message);
  }
}

template <class ListType>
ListType ArrayList<ListType>::Replace(int position, const ListType& entry) throw(PrecondViolatedExcept) {
  // Enforce Precondition
  bool able_to_set = (position >= 1) && (position <= list_count_);
  if (able_to_set) {
    ListType old_entry = list_[position];
    list_[position] = entry;
    return old_entry;
  } else {
      std::string message = "Replace() called with an empty list or invalid position.";
      throw PrecondViolatedExcept(message);
  }
}
