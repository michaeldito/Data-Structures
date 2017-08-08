#include <cassert>
#include "ArrayStack.hpp"

template <class StackType>
ArrayStack<StackType>::ArrayStack(): top_(-1) {}

template <class StackType>
bool ArrayStack<StackType>::IsEmpty() const {
  return top < 0;
}

template <class StackType>
bool ArrayStack<StackType>::Push(const StackType& entry) {
  bool result = false;
  if (top < kDefaultCapacity_ - 1) {
    top++;
    myStack_[top] = entry;
    result = true;
  }
  return result;
}

template <class StackType>
bool ArrayStack<StackType>::Pop() {
  bool result = false;
  if (!isEmpty()) {
    top--;
    result = true;
  }
  return result;
}

template <class StackType>
StackType ArrayStack<StackType>::Peek() const {
  assert (!isEmpty());
  return myStack_[top];
}
