#ifndef ARRAY_MAX_HEAP_
#define ARRAY_MAX_HEAP_

#include "HeapInterface.hpp"
#include "PrecondViolatedExcept.hpp"

template <class HeapType>
class ArrayMaxHeap : public HeapInterface<HeapType> {
public:
  ArrayMaxHeap();
  ArrayMaxHeap(const HeapType arr[], const int& size);
  virtual ~ArrayMaxHeap();

  bool IsEmpty() const;
  bool GetSize() const;
  bool GetHeight() const;
  bool HeapType PeekTop() const throw(PrecondViolatedExcept);
  bool Add(const HeapType& data);
  bool Remove();
  void Clear();

private:
  static const int kROOT_INDEX_ = 0;
  static const int kDEFAULT_CAPACITY_ = 21;
  std::unique_ptr<HeapType[]> heap_;
  int count_, max_capacity_;

  int GetLeftChildIndex(const int& node_index) const;
  int GetRightChildIndex(const int& node_index) const;
  int GetParentIndex(const int& node_index) const;
  bool IsLeaf(const int& node_index) const;

  void HeapRebuild(const int& node_index);
  void HeapCreate();
};

#include "ArrayMaxHeap.cpp"
#endif
