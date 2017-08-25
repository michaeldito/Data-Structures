#ifndef HEAP_INTERFACE_
#define HEAP_INTERFACE_

template <class HeapType>
class HeapInterface {
public:
  virtual bool IsEmpty() const = 0;
  virtual int GetSize() const = 0;
  virtual int GetHeight() const = 0;
  virtual HeapType PeekTop() const = 0;
  virtual bool Add(const HeapType& data) = 0;
  virtual bool Remove() = 0;
  virtual void Clear() = 0;
  virtual ~HeapInterface() {}
};

#endif
