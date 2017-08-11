#include "ArrayDeque.hpp"

template <class DequeType>
ArrayDeque<DequeType>::ArrayDeque(): front_(-1), back_(0), count_(0) {
  dq_ = new DequeType[max_capacity_];
}

template <class DequeType>
ArrayDeque<DequeType>::~ArrayDeque() {
  delete [] dq_;
}

template <class DequeType>
void ArrayDeque<DequeType>::print() {
  for(int i = front_; i <= back_; i++)
    std::cout << dq_[i] << ',';
  std::cout << '\n';
}

template <class DequeType>
bool ArrayDeque<DequeType>::IsEmpty() const {
  return count_ == 0;
}

template <class DequeType>
bool ArrayDeque<DequeType>::IsFull() const {
  return ((front_ == 0 && back_ == max_capacity_ - 1) || (front_ == back_ + 1));
}

template <class DequeType>
int ArrayDeque<DequeType>::GetSize() const {
  return count_;
}

template <class DequeType>
bool ArrayDeque<DequeType>::AddToFront(const DequeType& entry) {
  if(IsFull())
    Expand();

  if (front_ == -1) {
    front_ = 0;
    back_ = 0;
  } else if (front_ == 0) {
      front_ = max_capacity_ - 1;
  } else {
      front_--;
  }

  dq_[front_] = entry;
  count_++;

  return true;
}

template <class DequeType>
bool ArrayDeque<DequeType>::AddToBack(const DequeType& entry) {
  if(IsFull())
    Expand();

  if (front_ == -1) {
    front_ = 0;
    back_ = 0;
  } else if (back_ == max_capacity_ - 1) {
     back_ = 0;
  } else {
      back_++;
  }

  dq_[back_] = entry;
  count_++;

  return true;
}

template <class DequeType>
bool ArrayDeque<DequeType>::RemoveFront() {
  if (IsEmpty())
    return false;
  if (front_ == back_) {
    front_ = -1;
    back_ = -1;
  } else {
      if (front_ == max_capacity_ - 1) {
        front_ = 0;
      } else {
          front_++;
      }
  }

  count_--;
  return true;
}

template <class DequeType>
bool ArrayDeque<DequeType>::RemoveBack() {
  if (IsEmpty())
    return false;
  if (front_ == back_) {
    front_ = -1;
    back_ = -1;
  } else if (back_ == 0) {
      back_ = max_capacity_ - 1;
    } else {
        back_--;
      }

  count_--;
  return true;
}

template <class DequeType>
DequeType ArrayDeque<DequeType>::PeekFront() const throw(PrecondViolatedExcept) {
  // Enforce precondition
  if (IsEmpty())
    throw PrecondViolatedExcept("PeekFront() called with empty queue");
  return dq_[front_];
}

template <class DequeType>
DequeType ArrayDeque<DequeType>::PeekBack() const throw(PrecondViolatedExcept) {
  // Enforce precondition
  if (IsEmpty())
    throw PrecondViolatedExcept("PeekFront() called with empty queue");
  return dq_[back_];
}

template <class DequeType>
bool ArrayDeque<DequeType>::Expand() throw (MemoryAllocationExcept) {
  max_capacity_ += max_capacity_ / 2;
  DequeType* new_dq = new DequeType[max_capacity_];
  if (new_dq == nullptr) {
    throw MemoryAllocationExcept();
    return false;
  }
  for (int i = 0; i < max_capacity_; ++i)
    new_dq[i] = dq_[i];
  delete [] dq_;
  dq_ = new_dq;
  return true;
}
