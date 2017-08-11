#ifndef SORTED_LIST_PRIORITY_QUEUE_
#define SORTED_LIST_PRIORITY_QUEUE_

#include "PriorityQueueInterface.hpp"
#include "LinkedSortedList.hpp"
#include "PrecondViolatedExcept.hpp"
#include <memory>

template <class QueueType>
class SortedListPriorityQueue : public PriorityQueueInterface<QueueType> {
 public:
  SortedListPriorityQueue();
  SortedListPriorityQueue(const SortedListPriorityQueue& pq);
  ~SortedListPriorityQueue();

  bool IsEmpty() const;
  int GetSize() const;
  bool Enqueue(const QueueType& entry);
  bool Dequeue();
  QueueType PeekFront() const throw(PrecondViolatedExcept);

 private:
  std::unique_ptr<LinkedSortedList<QueueType>> sorted_list_ptr_;
};

#include "SortedListPriorityQueue.cpp"
#endif
