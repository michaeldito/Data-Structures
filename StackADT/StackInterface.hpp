#ifndef STACK_INTERFACE_
#define STACK_INTERFACE

template <class StackType>
class StackInterface {
 public:
   virtual bool IsEmpty() const = 0;
   virtual bool Push(const StackType & entry) = 0;
   virtual bool Pop() = 0;
   virtual StackType Peek() const = 0;
   virtual ~StackInterface() {}
};

#endif
