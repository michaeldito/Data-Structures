#ifndef BAG_INTERFACE_
#define BAG_INTERFACE_

#include <vector>

template <class BagType>
class BagInterface {
 public:
  virtual int GetSize() const = 0;
  virtual bool IsEmpty() const = 0;
  virtual bool Add(const BagType& entry) = 0;
  virtual bool Remove(const BagType& entry) = 0;
  virtual void Clear() = 0;
  virtual int GetFrequencyOf(const BagType& entry) const = 0;
  virtual bool Contains(const BagType& entry) const = 0;
  virtual std::vector<BagType> ToVector() const = 0;
  virtual ~BagInterface() {}
};

#endif
