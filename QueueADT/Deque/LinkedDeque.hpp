#ifndef LINKED_DEQUE_
#define LINKED_DEQUE_

#include "DequeInterface.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcept.hpp"
#include "MemoryAllocationExcept.hpp"
#include <memory>

template <class DequeType>
class LinkedDeque : public DequeInterface<DequeType> {
 public:
  LinkedDeque();
  LinkedDeque(const LinkedDeque& D) throw(MemoryAllocationExcept);
  ~LinkedDeque();

  bool IsEmpty() const;
  int GetSize() const;
  bool AddToFront(const DequeType& entry) throw(MemoryAllocationExcept);
  bool AddToBack(const DequeType& entry) throw(MemoryAllocationExcept);
  bool RemoveFront();
  bool RemoveBack();

  DequeType PeekFront() const throw(PrecondViolatedExcept);
  DequeType PeekBack() const throw(PrecondViolatedExcept);

 private:
  std::shared_ptr<Node<DequeType>> front_ptr_;
  std::shared_ptr<Node<DequeType>> back_ptr_;
  int count_;
};

#include "LinkedDeque.cpp"
#endif
