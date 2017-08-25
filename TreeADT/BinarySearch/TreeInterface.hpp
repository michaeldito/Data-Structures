#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_

template <class TreeType>
class TreeInterface {
 public:
  virtual bool IsEmpty() const = 0;
  virtual int GetMaxDepth() const = 0;
  virtual int GetMaxDepthIter() const = 0;
  virtual int GetNumberOfNodes() const = 0;
  virtual TreeType GetRootData() const = 0;
  virtual void SetRootData(const TreeType& data) = 0;
  virtual void Insert(const TreeType& data) = 0;
  virtual bool Remove(const TreeType& data) = 0;
  virtual void Clear() = 0;
  virtual bool Contains(const TreeType& data) const = 0;
  virtual bool IterContains(const TreeType& data) const = 0;
  virtual TreeType GetEntry(const TreeType& data) const = 0;

  virtual void PreorderTraverse(void Visit(TreeType&)) const = 0;
  virtual void InorderTraverse(void Visit(TreeType&)) const = 0;
  virtual void PostorderTraverse(void Visit(TreeType&)) const = 0;

  virtual ~TreeInterface() {}
};


#endif
