#include "ArraySortedList.hpp"

template <class ListType>
ArraySortedList<ListType>::ArraySortedList(): list_count_(0), max_capacity_(kDefaultCapacity_) {
  list_ = new ListType[kDefaultCapacity_ + 1];
}

template <class ListType>
ArraySortedList<ListType>::~ArraySortedList() {
  Clear();
}

template <class ListType>
bool ArraySortedList<ListType>::InsertSorted(const ListType& entry) {
  bool need_to_expand = list_count_ >= max_capacity_;
  if (need_to_expand) {
    max_capacity_ += max_capacity_ / 2;
    ListType* new_list = new ListType[max_capacity_ + 1];
    for (int i = 1; i <= list_count_; i++)
      new_list[i] = list_[i];
    delete [] list_;
    list_ = new_list;
  }

  int first = 1, idx = list_count_ + 1;
	while ((idx > first) && (entry < list_[idx - 1]))
	{
		list_[idx] = list_[idx - 1];
		idx = idx - 1;
	}
	list_[idx] = entry;
	list_count_++;

	return true;
}

template <class ListType>
bool ArraySortedList<ListType>::RemoveSorted(const ListType& entry) throw(PrecondViolatedExcept) {
  int remove_index = GetPosition(entry);
  if (remove_index > 0) {
    Remove(remove_index);
    return true;
  }
  std::string message = "RemoveSorted() called with an empty list or invalid entry.";
  throw(PrecondViolatedExcept(message));
  return false;
}

template <class ListType>
int ArraySortedList<ListType>::GetPosition(const ListType& entry) const {
  int low = 1, mid = 0, high = list_count_;
  while (low <= high) {
    mid = (low + high) / 2;
    if (list_[mid] == entry)
      return mid;
    else if (list_[mid] < entry)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}

template <class ListType>
bool ArraySortedList<ListType>::IsEmpty() const {
  return list_count_ == 0;
}

template <class ListType>
int ArraySortedList<ListType>::GetLength() const {
  return list_count_;
}

template <class ListType>
bool ArraySortedList<ListType>::Remove(int position) throw(PrecondViolatedExcept) {
  bool able_to_remove = (position >= 1) && (position <= list_count_);
  if (able_to_remove) {
    for (int i = position; i <= list_count_; i++)
      list_[i] = list_[i + 1];
    list_count_--;
  } else {
      std::string message = "Remove() called with an empty list or invalid position.";
      throw(PrecondViolatedExcept(message));
  }
  return able_to_remove;
}

template <class ListType>
void ArraySortedList<ListType>::Clear() {
  list_count_ = 0;
}

template <class ListType>
ListType ArraySortedList<ListType>::GetEntry(int position) const throw(PrecondViolatedExcept) {
  bool able_to_get = (position >= 1) && (position <= list_count_);
  if (able_to_get) {
    return list_[position];
  } else {
      std::string message = "GetEntry() called with an empty list or invalid position.";
      throw(PrecondViolatedExcept(message));
  }
}
