#include "ArrayCircularQueue.hpp"

template <class QueueType>
ArrayCircularQueue<QueueType>::ArrayCircularQueue(): front_(0), back_(max_capacity_ - 1), count_(0) {
  queue_ = new QueueType[max_capacity_];
}

template <class QueueType>
bool ArrayCircularQueue<QueueType>::IsEmpty() const {
  return count_ == 0;
}

template <class QueueType>
int ArrayCircularQueue<QueueType>::GetSize() const {
  return count_;
}

template <class QueueType>
bool ArrayCircularQueue<QueueType>::Enqueue(const QueueType& entry) throw(PrecondViolatedExcept) {
  if (count_ < max_capacity_) {
    back_ = (back_ + 1) % max_capacity_;
    queue_[back_] = entry;
    count_++;
    return true;
  }
  throw PrecondViolatedExcept("Enqueue() called with empty queue or queue is at capacity");
  return false;
}

template <class QueueType>
bool ArrayCircularQueue<QueueType>::Dequeue() {
  bool result = false;
  if (!IsEmpty()) {
    front_ = (front_ + 1) % max_capacity_;
    count_--;
    result = true;
  }
  return result;
}

template <class QueueType>
QueueType ArrayCircularQueue<QueueType>::PeekFront() const throw (PrecondViolatedExcept) {
    // Enforce precondition
    if (IsEmpty())
      throw PrecondViolatedExcept("PeekFront() called with empty queue");
    return queue_[front_];
}
