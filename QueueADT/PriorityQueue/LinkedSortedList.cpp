#include "LinkedSortedList.hpp"
#include <cassert>

template <class ListType>
LinkedSortedList<ListType>::LinkedSortedList(): list_count_(0) {}

template <class ListType>
LinkedSortedList<ListType>::LinkedSortedList(const LinkedSortedList<ListType>& L) {
  head_ = CopyChain(L.head_);
  list_count_ = L.list_count_;
}

template <class ListType>
LinkedSortedList<ListType>::~LinkedSortedList() {
  Clear();
}

template <class ListType>
bool LinkedSortedList<ListType>::InsertSorted(const ListType& entry) throw(MemoryAllocationExcept) {
  auto new_node_ptr(std::make_shared<Node<ListType>>(entry));
  if (new_node_ptr == nullptr) {
    throw MemoryAllocationExcept();
    return false;
  }
  auto prev_ptr = GetNodeBefore(entry);
  if (IsEmpty() || (prev_ptr == nullptr)) {
    new_node_ptr->SetNext(head_);
    head_ = new_node_ptr;
  } else {
      auto after_ptr = prev_ptr->GetNext();
      new_node_ptr->SetNext(after_ptr);
      prev_ptr->SetNext(new_node_ptr);
  }
  list_count_++;
  return true;
}

template <class ListType>
bool LinkedSortedList<ListType>::RemoveSorted(const ListType& entry) {
  return Remove(GetPosition(entry));
}

template <class ListType>
int LinkedSortedList<ListType>::GetPosition(const ListType& entry) const{
  auto traversal_ptr = head_;
  int position = 1;
  while (traversal_ptr != nullptr) {
    if (traversal_ptr->GetData() == entry)
      return position;
    traversal_ptr = traversal_ptr->GetNext();
    position++;
  }
  return -1; // We reached the end and did not find it
}

template <class ListType>
bool LinkedSortedList<ListType>::IsEmpty() const {
  return list_count_ == 0 && head_ == nullptr;
}

template <class ListType>
int LinkedSortedList<ListType>::GetLength() const {
  return list_count_;
}

template <class ListType>
bool LinkedSortedList<ListType>::Remove(int position) {
  bool able_to_remove = (position >= 1) && (position <= list_count_);
  if (able_to_remove) {
      if (position == 1) {
        head_ = head_->GetNext();
      } else {
          auto prev = GetNodeAt(position - 1);
          auto current = prev->GetNext();
          prev->SetNext(current->GetNext());
      }
      list_count_--;
      return true;
  }
  return false;
}

template <class ListType>
void LinkedSortedList<ListType>::Clear() {
  head_ = nullptr;
  list_count_ = 0;
}

template <class ListType>
ListType LinkedSortedList<ListType>::GetEntry(int position) const throw(PrecondViolatedExcept) {
  bool able_to_get = (position >= 1) && (position <= list_count_);
  if (able_to_get) {
    auto node = GetNodeAt(position);
    return node->GetData();
  } else {
    std::string message = "GetEntry() called with an empty list or invalid position.";
    throw PrecondViolatedExcept(message);
  }
}

template <class ListType>
auto LinkedSortedList<ListType>::GetNodeBefore(const ListType& entry) const {
    auto current_ptr = head_;
    std::shared_ptr<Node<ListType>> prev_ptr;
    while ((current_ptr != nullptr) && (entry > current_ptr->GetData()) ) {
      prev_ptr = current_ptr;
      current_ptr = current_ptr->GetNext();
    }
    return prev_ptr;
}

template <class ListType>
auto LinkedSortedList<ListType>::GetNodeAt(int position) const {
  assert((position >= 1) && (position <= list_count_));
  // Count from the beginning of the chain
  auto current = head_;
  for (int skip = 1; skip < position; skip++)
    current = current->GetNext();

  return current;
}

template <class ListType>
auto LinkedSortedList<ListType>::CopyChain(const std::shared_ptr<Node<ListType>>& original_chain_ptr) {
  std::shared_ptr<Node<ListType>> copied_chain_ptr;
  if (original_chain_ptr != nullptr) {
    // Build new chain from given one
    // Create new node with the current item
    copied_chain_ptr = std::make_shared<Node<ListType>>(original_chain_ptr->GetData());
    // Make the node point to the rest of the chain
    copied_chain_ptr->SetNext(CopyChain(original_chain_ptr->GetNext()));
  }
  return copied_chain_ptr;
}
