#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "TreeInterface.hpp"
#include "TreeNode.hpp"
#include <queue>
#include <iostream>
#include <memory>

template <class TreeType>
class BinarySearchTree : public TreeInterface<TreeType> {
 public:
  BinarySearchTree();
  BinarySearchTree(std::shared_ptr<TreeNode<TreeType>> root);
  virtual ~BinarySearchTree();

  auto SortedArrayToBst(int a[], int n);
  auto GetRoot() const { return root_ptr_; };

  TreeType GetRootData() const;
  void SetRootData(const TreeType& v);
  void Insert(const TreeType& v);
  bool Remove(const TreeType& v);
  void Clear();
  bool IsEmpty() const;
  int MaxDepthRecursive() const;
  int MaxDepthIterative() const;
  bool ContainsRecursive(const TreeType& v) const;
  bool ContainsIterative(const TreeType& v) const;
  int GetSize() const;

//  TreeType GetEntry(const TreeType& v) const;
//  void PreorderTraverse(void Visit(TreeType&)) const;
//  void InorderTraverse(void Visit(TreeType&)) const;
//  void PostorderTraverse(void Visit(TreeType&)) const;

  void DumpValuesAtLevelRecursive(std::ostream& os, const int& level) const;
  void DumpValuesAtLevelIterative(std::ostream& os, const int& level) const;
  void LevelOrderDump(std::ostream& os) const;
  void InOrderDump(std::ostream& os) const;
  void PreOrderDump(std::ostream& os) const;
  void PostOrderDump(std::ostream& os) const;


  TreeType KthSmallest(const int& k) const;
  bool HasRootToLeafSum(const int& sum) const;
  bool AreBstIdentical(std::shared_ptr<BinarySearchTree<TreeType>> bst) const;

  auto IntersectionWith(std::shared_ptr<BinarySearchTree<TreeType>> bst) const;
  auto UnionWith(std::shared_ptr<BinarySearchTree<TreeType>> bst) const;
  auto DifferenceOf(std::shared_ptr<BinarySearchTree<TreeType>> bst) const;

  bool IsBSubstructureOfA(std::shared_ptr<TreeNode<TreeType>> a, std::shared_ptr<TreeNode<TreeType>> b) const;
  bool TwoTheSame(std::shared_ptr<TreeNode<TreeType>> p, std::shared_ptr<TreeNode<TreeType>> q) const;

protected:
 auto BuildTreeFromSortedArray(TreeType a[], int start, int end);

 auto LocalInsert(std::shared_ptr<TreeNode<TreeType>> root, TreeType v);
 auto ExtractNextLargestNode(std::shared_ptr<TreeNode<TreeType>> root);

 bool Contains(std::shared_ptr<TreeNode<TreeType>> root, const TreeType& v) const;
 int NumberOfNodes(std::shared_ptr<TreeNode<TreeType>> root) const;

 void DumpValuesAtLevel(std::ostream& os, std::shared_ptr<TreeNode<TreeType>> root, const int& level) const;
 void InOrderPrint(std::ostream& os,std::shared_ptr<TreeNode<TreeType>> root) const;
 void PreOrderPrint(std::ostream& os, std::shared_ptr<TreeNode<TreeType>> root) const;
 void PostOrderPrint(std::ostream& os, std::shared_ptr<TreeNode<TreeType>> root) const;

 int MaxDepth(std::shared_ptr<TreeNode<TreeType>> root) const;
 TreeType GetKthSmallest(std::shared_ptr<TreeNode<TreeType>> root, const int& k) const;
 bool FindPathSumEqualToSum(std::shared_ptr<TreeNode<TreeType>> root, const int& sum) const;
 bool AreTreeNodesIdentical(std::shared_ptr<TreeNode<TreeType>> root, std::shared_ptr<TreeNode<TreeType>> otherRoot) const;

 void MakeIntersection(std::shared_ptr<BinarySearchTree<TreeType>> the_intersection, std::shared_ptr<TreeNode<TreeType>> root, std::shared_ptr<BinarySearchTree<TreeType>> bst) const;
 void MakeUnion(std::shared_ptr<TreeNode<TreeType>> root, std::shared_ptr<BinarySearchTree<TreeType>> the_union) const;
 void MakeDifference(std::shared_ptr<BinarySearchTree<TreeType>> the_diff, std::shared_ptr<TreeNode<TreeType>> root) const;

 bool HasSubstructure(std::shared_ptr<TreeNode<TreeType>> a, std::shared_ptr<TreeNode<TreeType>> b) const;

private:
  std::shared_ptr<TreeNode<TreeType>> root_ptr_;
};

#include "BinarySearchTree.cpp"
#endif
