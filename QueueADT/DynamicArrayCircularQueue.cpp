#include "DynamicArrayCircularQueue.hpp"

template <class QueueType>
DynamicArrayCircularQueue<QueueType>::DynamicArrayCircularQueue(): front_(0), back_(max_capacity_ - 1), count_(0) {
  queue_ = new QueueType[max_capacity_];
}

template <class QueueType>
bool DynamicArrayCircularQueue<QueueType>::IsEmpty() const {
  return count_ == 0;
}

template <class QueueType>
int DynamicArrayCircularQueue<QueueType>::GetSize() const {
  return count_;
}

template <class QueueType>
bool DynamicArrayCircularQueue<QueueType>::Enqueue(const QueueType& entry) throw (MemoryAllocationExcept) {
  // Do we need to expand the queue?
  if (count_ >= max_capacity_) {
    max_capacity_ += max_capacity_ / 2;
    QueueType* new_queue = new QueueType[max_capacity_];
    if (new_queue == nullptr) {
      throw MemoryAllocationExcept();
      return false;
    }
    for (int i = 0; i < max_capacity_; ++i)
      new_queue[i] = queue_[i];
    delete [] queue_;
    queue_ = new_queue;
  }

  // Add to the queue
  back_ = (back_ + 1) % max_capacity_;
  queue_[back_] = entry;
  count_++;

  return true;
}

template <class QueueType>
bool DynamicArrayCircularQueue<QueueType>::Dequeue() {
  bool result = false;
  if (!IsEmpty()) {
    front_ = (front_ + 1) % max_capacity_;
    count_--;
    result = true;
  }
  return result;
}

template <class QueueType>
QueueType DynamicArrayCircularQueue<QueueType>::PeekFront() const throw (PrecondViolatedExcept) {
    // Enforce precondition
    if (IsEmpty())
      throw PrecondViolatedExcept("PeekFront() called with empty queue");
    return queue_[front_];
}
