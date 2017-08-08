#ifndef LINKED_STACK_
#define LINKED_STACK_

#include "StackInterface.hpp"
#include "Node.hpp"

template <class StackType>
class LinkedStack : public StackInterface<StackType> {
 public:
   LinkedStack();
   LinkedStack(const LinkedStack<StackType>& aStack);
   virtual ~LinkedStack();
   bool IsEmpty() const;
   bool Push(const StackType& entry);
   bool Pop();
   StackType Peek() const;

 private:
   Node<StackType>* top_;
};

#include "LinkedStack.cpp"
#endif
