#include "ArrayStack.hpp"
#include <iostream>

template <class StackType>
ArrayStack<StackType>::ArrayStack(): top_(-1), size_(0), max_capacity_(kDefaultCapacity_) {
  myStack_ = new StackType[kDefaultCapacity_];
}

template <class StackType>
bool ArrayStack<StackType>::IsEmpty() const {
  return top_ < 0;
}

template <class StackType>
bool ArrayStack<StackType>::Push(const StackType& entry) {
  bool need_to_expand = top_ >= max_capacity_ - 1;
  if (!need_to_expand) {
    top_++;
    size_++;
    myStack_[top_] = entry;
  }
  else {
    std::cout << "EXPANDING\n";
    max_capacity_ += max_capacity_ / 2;
    StackType* new_stack = new StackType[max_capacity_];
    for (int i = 0; i < size_; i++)
      new_stack[i] = myStack_[i];
    delete [] myStack_;
    myStack_ = new_stack;

    top_++;
    size_++;
    myStack_[top_] = entry;
  }
  return true;
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
