#ifndef LIST_INTERFACE_
#define LIST_INTERFACE_

template <class ListType>
class ListInterface {
  virtual bool IsEmpty() const = 0;
  virtual int GetLength() const = 0;
  virtual bool Insert(int position, const ListType& entry) = 0;
  virtual bool Remove(int position) = 0;
  virtual void Clear() = 0;
  virtual ListType GetEntry(int position) const = 0;
  virtual ListType Replace(int position, const ListType& entry) = 0;
  virtual ~ListInterface {}
};

#endif
