#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "QueueInterface.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcept.hpp"
#include "MemoryAllocationExcept.hpp"
#include <memory>

template <class QueueType>
class LinkedQueue : public QueueInterface<QueueType> {
 public:
  LinkedQueue();
  LinkedQueue(const LinkedQueue& Q) throw(MemoryAllocationExcept);
  ~LinkedQueue();

  bool IsEmpty() const;
  int GetSize() const;
  bool Enqueue(const QueueType& entry) throw(MemoryAllocationExcept);
  bool Dequeue();
  QueueType PeekFront() const throw(PrecondViolatedExcept);

 private:
  std::shared_ptr<Node<QueueType>> front_ptr_;
  std::shared_ptr<Node<QueueType>> back_ptr_;
  int count_;
};

#include "LinkedQueue.cpp"
#endif
