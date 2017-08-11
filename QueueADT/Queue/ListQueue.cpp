#include "ListQueue.hpp"

template <class QueueType>
ListQueue<QueueType>::ListQueue(): list_ptr_(std::make_unique<LinkedList<QueueType>>()), count_(0) {}

template <class QueueType>
ListQueue<QueueType>::ListQueue(const ListQueue& Q) {
  count_ = Q.count_;
  // Point to Q's list
  auto original_chain_ptr = Q.list_ptr_;
  if (original_chain_ptr == nullptr) {
    list_ptr_ = nullptr;
  } else {
    // Have the list_ptr_ point to a new node; give it data
    list_ptr_ = std::make_shared<Node<QueueType>>();
    list_ptr_->SetData(original_chain_ptr->GetData());

    // Make a traversal pointer for our new chain
    auto new_chain_ptr = list_ptr_;
    // Move the original_chain_ptr along
    original_chain_ptr = original_chain_ptr->GetNext();
    // for all other nodes in the chain to be copied
    while (original_chain_ptr != nullptr) {
      // get the next peice of data and make a node with it
      QueueType next_data = original_chain_ptr->GetData();
      auto new_node_ptr = std::make_shared<Node<QueueType>>(next_data);
      // make it new_node_ptrs next
      new_chain_ptr->SetNext(new_node_ptr);
      // move new and original chain pointers along
      original_chain_ptr = original_chain_ptr->GetNext();
      new_chain_ptr = new_chain_ptr->GetNext();
    }
    // End the new chain.
    new_chain_ptr->SetNext(nullptr);
  }
}

template <class QueueType>
ListQueue<QueueType>::~ListQueue() {
  while (count_ > 0)
    Dequeue();
}

template <class QueueType>
bool ListQueue<QueueType>::IsEmpty() const {
  return list_ptr_->IsEmpty();
}

template <class QueueType>
int ListQueue<QueueType>::GetSize() const {
  return count_;
}

template <class QueueType>
bool ListQueue<QueueType>::Enqueue(const QueueType& entry) {
  if (list_ptr_->Insert(list_ptr_->GetLength() + 1, entry)) {
    count_++;
    return true;
  }
  return false;
}

template <class QueueType>
bool ListQueue<QueueType>::Dequeue() {
  if (list_ptr_->Remove(1)) {
    count_--;
    return true;
  }
  return false;
}

template <class QueueType>
QueueType ListQueue<QueueType>::PeekFront() const throw(PrecondViolatedExcept) {
  if (IsEmpty())
    throw PrecondViolatedExcept("PeekFront() called with empty queue.");
  return list_ptr_->GetEntry(1);
}
