#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryTreeInterface.hpp"
#include "TreeNode.hpp"
#include <queue>
#include <iostream>

typedef std::shared_ptr<BinarySearchTree<TreeType>> BinSearchTreePtr;

template <class TreeType>
class BinarySearchTree : public BinaryTreeInterface {
 public:
  BinarySearchTree();
  BinarySearchTree(TreeNodePtr root);
  ~BinarySearchTree();

  TreeNodePtr SortedArrayToBst(int a[], int n);

  TreeType GetRootData() const;
  void SetRootData(const TreeType& v);
  auto GetRoot() { return root_ptr_ };

  void Insert(const TreeType& v);
  bool Remove(const TreeType& v);
  void Clear();
  bool ContainsRecursive(const TreeType& v) const;
  bool ContainsIterative(const TreeType& v) const;
  int GetSize() const;
  bool IsEmpty() const;

//  TreeType GetEntry(const TreeType& v) const;
//  void PreorderTraverse(void Visit(TreeType&)) const;
//  void InorderTraverse(void Visit(TreeType&)) const;
//  void PostorderTraverse(void Visit(TreeType&)) const;

  void DumpValuesAtLevelRecursive(ostream& os, const int& level) const;
  void DumpValuesAtLevelIterative(ostream& os, const int& level) const;
  void LevelOrderDump(ostream& os) const;
  void InOrderDump(ostream& os) const;
  void PreOrderDump(ostream& os) const;
  void PostOrderDump(ostream& os) const;

  int MaxDepthRecursive() const;
  int MaxDepthIterative() const;
  TreeType KthSmallest(const int& k) const;
  bool HasRootToLeafSum(const int& sum) const;
  bool AreBstIdentical(BinSearchTreePtr bst) const;

  BinSearchTreePtr IntersectionWith(BinSearchTreePtr bst) const;
  BinSearchTreePtr UnionWith(BinSearchTreePtr bst) const;
  BinSearchTreePtr DifferenceOf(BinSearchTreePtr bst) const;

  bool IsBSubstructureOfA(TreeNodePtr a, TreeNodePtr b) const;
  bool TwoTheSame(TreeNodePtr p, TreeNodePtr q) const;

protected:
 TreeNodePtr BuildTreeFromSortedArray(TreeType a[], int start, int end);

 TreeNodePtr LocalInsert(TreeNodePtr root, TreeType v);
 TreeNodePtr ExtractNextLargestNode(TreeNodePtr root);
 bool Contains(TreeNodePtr root, TreeType v) const;
 int NumberOfNodes(TreeNodePtr root) const;

 void DumpValuesAtLevel(ostream& os, TreeNodePtr root, const int& level) const;
 void InOrderPrint(ostream& os,TreeNodePtr root) const;
 void PreOrderPrint(ostream& os, TreeNodePtr root) const;
 void PostOrderPrint(ostream& os, TreeNodePtr root) const;

 int MaxDepth(TreeNodePtr root) const;
 TreeType GetKthSmallest(TreeNodePtr root, const int& k) const;
 bool FindPathSumEqualToSum(TreeNodePtr root, const int& sum) const;
 bool AreTreeNodesEqual(TreeNodePtr root, TreeNodePtr otherRoot) const;

 void MakeIntersection(BinSearchTree intersection, TreeNodePtr root, BinSearchTreePtr tree) const;
 void MakeUnion(TreeNodePtr root, BinSearchTreePtr the_union) const;
 void MakeDifference(TreeNodePtr root, BinSearchTreePtr the_union) const;

 HasSubstructure(TreeNodePtr a, TreeNodePtr b) const;

private:
  TreeNodePtr root_ptr_;
};

#endif
