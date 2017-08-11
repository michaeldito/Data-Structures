#ifndef DEQUE_INTERFACE_
#define DEQUE_INTERFACE_

template <class DequeType>
class DequeInterface {
 public:
  virtual bool IsEmpty() const = 0;
  virtual int GetSize() const = 0;
  virtual bool AddToFront(const DequeType& entry) = 0;
  virtual bool AddToBack(const DequeType& entry) = 0;
  virtual bool RemoveFront() = 0;
  virtual bool RemoveBack() = 0;
  virtual DequeType PeekFront() const = 0;
  virtual DequeType PeekBack() const = 0;
  virtual ~DequeInterface() {}
};

#endif
