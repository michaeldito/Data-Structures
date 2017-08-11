#ifndef PRIORITY_QUEUE_INTERFACE_
#define PRIORITY_QUEUE_INTERFACE_

#include "QueueInterface.hpp"

template <class QueueType>
class PriorityQueueInterface {
 public:
  virtual bool IsEmpty() const = 0;
  virtual int GetSize() const = 0;
  virtual bool Enqueue(const QueueType& entry) = 0;
  virtual bool Dequeue() = 0;
  virtual QueueType PeekFront() const = 0;
  virtual ~PriorityQueueInterface() {}
};

#endif
