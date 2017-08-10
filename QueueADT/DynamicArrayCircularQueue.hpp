#ifndef DYNAMIC_ARRAY_CIRCULAR_QUEUE_
#define DYNAMIC_ARRAY_CIRCULAR_QUEUE_

#include "QueueInterface.hpp"
#include "PrecondViolatedExcept.hpp"

template <class QueueType>
class DynamicArrayCircularQueue : public QueueInterface<QueueType> {
 public:
  DynamicArrayCircularQueue();

  bool IsEmpty() const;
  int GetSize() const;
  bool Enqueue(const QueueType& entry) throw(MemoryAllocationExcept);
  bool Dequeue();
  QueueType PeekFront() const throw(PrecondViolatedExcept);

 private:
   int max_capacity_ = 5;
   QueueType* queue_;
   int front_, back_, count_;
};

#include "DynamicArrayCircularQueue.cpp"
#endif
