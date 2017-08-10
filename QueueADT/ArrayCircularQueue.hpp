#ifndef ARRAY_CIRCULAR_QUEUE_
#define ARRAY_CIRCULAR_QUEUE_

#include "QueueInterface.hpp"
#include "PrecondViolatedExcept.hpp"

template <class QueueType>
class ArrayCircularQueue : public QueueInterface<QueueType> {
 public:
  ArrayCircularQueue();

  bool IsEmpty() const;
  int GetSize() const;
  bool Enqueue(const QueueType& entry) throw(PrecondViolatedExcept);
  bool Dequeue();
  QueueType PeekFront() const throw(PrecondViolatedExcept);

 private:
   int max_capacity_ = 10;
   QueueType* queue_;
   int front_, back_, count_;
};

#include "ArrayCircularQueue.cpp"
#endif
