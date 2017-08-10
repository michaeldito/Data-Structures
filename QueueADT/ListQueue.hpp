#ifndef LIST_QUEUE_
#define LIST_QUEUE_

#include "QueueInterface.hpp"
#include "LinkedList.hpp"
#include "PrecondViolatedExcept.hpp"
#include <memory>

template <class QueueType>
class ListQueue : public QueueInterface<QueueType> {
 public:
   ListQueue();
   ListQueue(const ListQueue& Q);
   ~ListQueue();

   bool IsEmpty() const;
   int GetSize() const;
   bool Enqueue(const QueueType& entry);
   bool Dequeue();
   QueueType PeekFront() const throw(PrecondViolatedExcept);

 private:
   std::unique_ptr<LinkedList<QueueType>> list_ptr_;
   int count_;
};

#include "ListQueue.cpp"
#endif
