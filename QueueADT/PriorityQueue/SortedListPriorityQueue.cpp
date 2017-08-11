#include "SortedListPriorityQueue.hpp"
#include <iostream>

template <class QueueType>
SortedListPriorityQueue<QueueType>::SortedListPriorityQueue():
  sorted_list_ptr_(std::make_unique<LinkedSortedList<QueueType>>()) {}

template <class QueueType>
SortedListPriorityQueue<QueueType>::SortedListPriorityQueue(const SortedListPriorityQueue& pq) {
  auto original_chain_ptr = pq.sorted_list_ptr_.head_;
  if (original_chain_ptr == nullptr) {
    sorted_list_ptr_ = nullptr;
  } else {
    // Copy first node.
    sorted_list_ptr_ = std::make_unique<Node<QueueType>>();
    sorted_list_ptr_->SetData(original_chain_ptr->GetData());

    // Copy remaining nodes.
    auto new_chain_ptr = sorted_list_ptr;
    original_chain_ptr = original_chain_ptr->GetNext();

    for (int i = 2; i < sorted_list_ptr_->GetLength(); ++i) {
      QueueType next_data = sorted_list_ptr_->GetEntry(i);
      auto new_node_ptr = std::make_shared<Node<QueueType>>(next_data);
      new_chain_ptr = new_chain_ptr->SetNext(new_node_ptr);

      new_chain_ptr = new_chain_ptr->GetNext();
      original_chain_ptr = original_chain_ptr->GetNext();
    }
    // End the new chain.
    new_chain_ptr->SetNext(nullptr);
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
