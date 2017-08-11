#ifndef QUEUE_INTERFACE_
#define QUEUE_INTERFACE_

template <class QueueType>
class QueueInterface {
 public:
   virtual bool IsEmpty() const = 0;
   virtual int GetSize() const = 0;
   virtual bool Enqueue(const QueueType& entry) = 0;
   virtual bool Dequeue() = 0;
   virtual QueueType PeekFront() const = 0;
   virtual ~QueueInterface() {}
};

#endif
