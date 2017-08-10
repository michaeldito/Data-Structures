#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackInterface.hpp"
#include "PrecondViolatedExcept.hpp"

template <class StackType>
class ArrayStack : public StackInterface<StackType> {
 public:
   ArrayStack();
   bool IsEmpty() const;
   bool Push(const StackType& entry);
   bool Pop();
   StackType Peek() const throw(PrecondViolatedExcept);
   int GetSize() const;

 private:
   static const int kDefaultCapacity_ = 2;
   StackType* myStack_;
   int top_;
   int size_;
   int max_capacity_;
};

#include "ArrayStack.cpp"
#endif
