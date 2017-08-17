#include "ListQueue.hpp"
#include <iostream>
using std::cout;
using std::endl;

template <class QueueType>
ListQueue<QueueType>::ListQueue(): list_ptr_(std::make_shared<LinkedList<QueueType>>()), count_(0) {}

template <class QueueType>
ListQueue<QueueType>::ListQueue(const ListQueue& Q) {
  list_ptr_ = std::make_shared<LinkedList<QueueType>>();
  auto original_chain_ptr = Q.list_ptr_;
    for (int i = 1; i <= Q.GetSize(); ++i) {
      list_ptr_->Insert(i, original_chain_ptr->GetEntry(i));
    }
  count_ = Q.count_;
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
