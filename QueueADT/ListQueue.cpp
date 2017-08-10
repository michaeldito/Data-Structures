#include "ListQueue.hpp"

template <class QueueType>
ListQueue<QueueType>::ListQueue(): list_ptr_(std::make_unique<LinkedList<QueueType>>()), count_(0) {}

template <class QueueType>
ListQueue<QueueType>::ListQueue(const ListQueue& Q) {
  int count_ = Q.count_;
  auto original_chain_ptr = Q.list_ptr_;
  if (original_chain_ptr == nullptr) {
    list_ptr_ = nullptr;
  } else {
    // Copy first node.
    list_ptr_ = std::make_shared<Node<QueueType>>();
    list_ptr_->SetData(original_chain_ptr->GetData());

    // Copy remaining nodes.
    auto new_chain_ptr = list_ptr_;
    original_chain_ptr = original_chain_ptr->GetNext();

    // Copy remaining nodes.
    for (int i = 1; i < list_ptr_->GetLength(); ++i) {
      QueueType next_data = list_ptr_->GetEntry(i);
      auto new_node_ptr = std::make_shared<Node<QueueType>>(next_data);
      new_chain_ptr = new_chain_ptr->GetNext();
      original_chain_ptr = original_chain_ptr->GetNext();
    }
    // End the new chain.
    new_chain_ptr->SetNext(nullptr);
  }
}
// Shallow Copy... revise to deep Copy

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
