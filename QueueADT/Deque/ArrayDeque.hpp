#ifndef ARRAY_DEQUE_
#define ARRAY_DEQUE_

#include <stdlib.h>
#include "DequeInterface.hpp"
#include "PrecondViolatedExcept.hpp"
#include "MemoryAllocationExcept.hpp"

template <class DequeType>
class ArrayDeque : public DequeInterface<DequeType> {
 public:
  ArrayDeque();
  ~ArrayDeque();

  void print();

  bool IsFull() const;
  bool IsEmpty() const;
  int GetSize() const;
  bool AddToFront(const DequeType& entry);
  bool AddToBack(const DequeType& entry);
  bool RemoveFront();
  bool RemoveBack();

  DequeType PeekFront() const throw(PrecondViolatedExcept);
  DequeType PeekBack() const throw(PrecondViolatedExcept);

 private:
  DequeType* dq_;
  int max_capacity_ = 6;
  int front_, back_, count_;

  bool Expand() throw (MemoryAllocationExcept);
};

#include "ArrayDeque.cpp"
#endif
