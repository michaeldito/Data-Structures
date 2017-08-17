#include "SortedListPriorityQueue.hpp"
#include <iostream>

template <class QueueType>
SortedListPriorityQueue<QueueType>::SortedListPriorityQueue():
  sorted_list_ptr_(std::make_shared<LinkedSortedList<QueueType>>()) {}

template <class QueueType>
SortedListPriorityQueue<QueueType>::SortedListPriorityQueue(const SortedListPriorityQueue& pq) {
  auto original_chain_ptr = pq.sorted_list_ptr_;
  if (original_chain_ptr == nullptr) {
    sorted_list_ptr_ = nullptr;
  } else {
    // Initialize the sorted_list_ptr_
    sorted_list_ptr_ = std::make_shared<LinkedSortedList<QueueType>>();

    // Create a pointer to the sorted_list_ptr_
    auto new_chain_ptr = sorted_list_ptr_;

    // Copy each nodes data in the original_chain_ptr and add it
    // to the sorted_list_ptr_ chain
    for (int i = 1; i <= original_chain_ptr->GetLength(); ++i) {
      QueueType next_data = original_chain_ptr->GetEntry(i);
      new_chain_ptr->InsertSorted(next_data);
    }
  }
}


template <class QueueType>
SortedListPriorityQueue<QueueType>::~SortedListPriorityQueue() {
  sorted_list_ptr_->Clear();
}

template <class QueueType>
bool SortedListPriorityQueue<QueueType>::IsEmpty() const {
  return sorted_list_ptr_->IsEmpty();
}

template <class QueueType>
int SortedListPriorityQueue<QueueType>::GetSize() const {
  return sorted_list_ptr_->GetLength();
}

template <class QueueType>
bool SortedListPriorityQueue<QueueType>::Enqueue(const QueueType& entry) {
  return sorted_list_ptr_->InsertSorted(entry);
}

template <class QueueType>
bool SortedListPriorityQueue<QueueType>::Dequeue() {
  // The highest priority item is at the end of the sorted list
  return sorted_list_ptr_->Remove(sorted_list_ptr_->GetLength());
}

template <class QueueType>
QueueType SortedListPriorityQueue<QueueType>::PeekFront() const throw(PrecondViolatedExcept) {
  return sorted_list_ptr_->GetEntry(sorted_list_ptr_->GetLength());
}
