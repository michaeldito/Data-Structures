#include "ArrayStack.hpp"

template <class StackType>
ArrayStack<StackType>::ArrayStack(): top_(-1), size_(0) {}

template <class StackType>
bool ArrayStack<StackType>::IsEmpty() const {
  return top_ < 0;
}

template <class StackType>
bool ArrayStack<StackType>::Push(const StackType& entry) {
  bool result = false;
  if (top_ < kDefaultCapacity_ - 1) {
    top_++;
    size_++;
    myStack_[top_] = entry;
    result = true;
  }
  return result;
}

template <class StackType>
bool ArrayStack<StackType>::Pop() {
  bool result = false;
  if (!IsEmpty()) {
    top_--;
    size_--;
    result = true;
  }
  return result;
}

template <class StackType>
StackType ArrayStack<StackType>::Peek() const throw(PrecondViolatedExcept) {
  if (IsEmpty())
    throw PrecondViolatedExcept("Peek() called with empty stack");
  else
    return myStack_[top_];
}

template <class StackType>
int ArrayStack<StackType>::GetSize() const {
  return size_;
}
