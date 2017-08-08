#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackInterface.hpp"

template <class StackType>
class ArrayStack : public StackInterface<StackType> {
 public:
   ArrayStack();
   bool IsEmpty() const;
   bool Push(const StackType& entry);
   bool Pop();
   StackType Peek() const;

 private:
   static const int kDefaultCapacity_ = 100;
   StackType myStack_[kDefaultCapacity_];
   int top_;
};

#include "ArrayStack.cpp"
#endif
