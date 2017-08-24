#include "BinarySearchTree.hpp"

template <class TreeType>
BinarySearchTree<TreeType>::BinarySearchTree() {}

template <class TreeType>
BinarySearchTree<TreeType>::BinarySearchTree(TreeNodePtr root): root_ptr_(root) {}

template <class TreeType>
BinSearchTreePtr BinarySearchTree<TreeType>::SortedArrayToBst(int a[], int n) {
	BinSearchTreePtr bst =  std::make_shared<BinarySearchTree<TreeType>>(BuildTreeFromSortedArray(a, 0, n - 1));
	return bst;
}

template <class TreeType>
TreeNodePtr BinarySearchTree<TreeType>::BuildTreeFromSortedArray(TreeType a[], int start, int end) {
	if (start > end)
		return nullptr;
	int mid = (start + end) / 2;
	TreeNodePtr node = std::make_shared<TreeNode<TreeType>>(a[mid]);
	node->SetLeftSubtree(BuildTreeFromSortedArray(a, start, mid - 1));
	node->SetRightSubtree(BuildTreeFromSortedArray(a, mid + 1, end));
	return node;
}

template <class TreeType>
BinarySearchTree<TreeType>::~BinarySearchTree() {
  Clear();
}

template <class TreeType>
TreeType BinarySearchTree<TreeType>::GetRootData() const {
  return root_ptr_->GetData();
}

template <class TreeType>
void BinarySearchTree<TreeType>::SetRootData(const TreeType& v) {
  root_ptr_->Value() = v;
}

template <class TreeType>
void BinarySearchTree<TreeType>::Insert(const TreeType& v) {
  if (!ContainsRecursive(v))
    root_ptr_ = LocalInsert(root, v);
}

template <class TreeType>
TreeNodePtr BinarySearchTree<TreeType>::LocalInsert(TreeNodePtr root, TreeType v) {
  if (root == nullptr)
    return new TreeNode(v);
  if (root->Value() < v)
    root->SetRightSubtree(LocalInsert(root->GetRightSubtree(), v));
  if (root->Value() > v)
    root->SetLeftSubtree(LocalInsert(root->GetLeftSubtree(), v));
  return root;
}

template <class TreeType>
bool BinarySearchTree<TreeType>::Remove(const TreeType& v) {
  if (!ContainsRecursive(v)) {
    std::cout << "The value: " << v << " is not in the tree.\n";
    return false;
  }
  bool is_node_deleted = false;
  TreeNodePtr current = root_ptr_, parent = root_ptr_;
  while (!is_node_deleted) {
    if (current->Value() == v) {
      // case 1: no subtrees
      if (current->GetRightSubtree() == nullptr && current->GetLeftSubtree() == nullptr) {
        if (current == root_ptr_) // special case: deleting root that is also a leaf
          root_ptr_ = nullptr;
        else if (parent->GetLeftSubtree() == current)
          parent->SetLeftSubtree(nullptr);
        else
          parent->SetRightSubtree(nullptr);
      }
      // case 2: one subtree
      else if ((current->GetRightSubtree() != nullptr && current->GetLeftSubtree() == nullptr) ||
              (current->GetRightSubtree() == nullptr && current->GetLeftSubtree() != nullptr)) {
        if (current == root_ptr_)
          if (current->GetRightSubtree() == nullptr)
            root_ptr_ = current->GetLeftSubtree();
          else
            root_ptr_ = current->GetRightSubtree();
        else if (parent->GetLeftSubtree() == current)
          if (current->GetRightSubtree() != nullptr)
            parent->GetLeftSubtree(current->GetRightSubtree());
          else
            parent->GetLeftSubtree(current->GetLeftSubtree());
        else
          if (current->GetRightSubtree() != nullptr)
            parent->SetRightSubtree(current->GetRightSubtree());
          else
            parent->SetRightSubtree(current->GetLeftSubtree());
        }
        // case 3: two subtrees
        else {
          TreeNodePtr replacement = ExtractNextLargestNode(current);
          current->Value() = replacement->Value();
        }
        is_node_deleted = true;
    }
    // if we didn't delete it, moev parent to current, and keep searching
    if (!is_node_deleted) {
      parent = current;
      if (current->Value() > v)
        current = current->GetLeftSubtree();
      else
        current = current->GetRightSubtree();
    }
  }
  return is_node_deleted;
}

template <class TreeType>
TreeNodePtr BinarySearchTree<TreeType>::ExtractNextLargestNode(TreeNodePtr root) {
  TreeNodePtr current = root->GetRightSubtree();
  TreeNodePtr parent = root;
  while (current->GetLeftSubtree() != nullptr) {
    parent = current;
    current = current->GetLeftSubtree();
  }
  if (parent->GetLeftSubtree() == current)
    parent->SetLeftSubtree(nullptr);
  else
    parent->SetRightSubtree(nullptr);
  return current;
}

template <class TreeType>
void BinarySearchTree<TreeType>::Clear() {
  root_ptr_.reset();
}

template <class TreeType>
bool BinarySearchTree<TreeType>::ContainsRecursive(const TreeType& v) const {
 if (root_ptr_ == nullptr)
  return false;
 if (root_ptr_->Value() == v)
  return true;
 if (root_ptr_->Value() > v)
  return Contains(root_ptr_->GetLeftSubtree(), v)
 return Contains(root_ptr_->GetRightSubtree(), v);
}

template <class TreeType>
bool BinarySearchTree<TreeType>::Contains(TreeNodePtr root, const TreeType& v) const {
  if (root == nullptr)
   return false;
  if (root->Value() == v)
   return true;
  if (root->Value() > v)
   return Contains(root->GetLeftSubtree(), v)
  return Contains(root->GetRightSubtree(), v);
}

template <class TreeType>
bool BinarySearchTree<TreeType>::ContainsIterative(const TreeType& v) const {
  TreeNodePtr current = root_ptr_;
  while (current != nullptr) {
    if (current->Value() == v)
      return true;
    if (current->Value() > v)
      current = current->GetLeftSubtree();
    else
      current = current->GetRightSubtree();
  }
  return false;
}

/*
 * Use void Visit function!
 *
template <class TreeType>
TreeType BinarySearchTree<TreeType>::GetEntry(const TreeType& v) const {

}
*/

template <class TreeType>
int BinarySearchTree<TreeType>::GetSize() const {
  return NumberOfNodes(root_ptr_);
}

template <class TreeType>
int BinarySearchTree<TreeType>::NumberOfNodes(TreeNodePtr root) const {
  if (root == nullptr)
    return 0;
  return 1 + NumberOfNodes(root->GetLeftSubtree()) + NumberOfNodes(root->GetRightSubtree();
}

template <class TreeType>
bool BinarySearchTree<TreeType>::IsEmpty() const {
  return root_ptr_ == nullptr;
}

/*
template <class TreeType>
void BinarySearchTree<TreeType>::PreorderTraverse(void Visit(TreeType&)) const {
  if (root == nullptr)
    return;
  Visit(root);
  PreOrderPrint(os, root->GetLeftSubtree());
  PreOrderPrint(os, root->GetRightSubtree());
}

template <class TreeType>
void BinarySearchTree<TreeType>::InorderTraverse(void Visit(TreeType&)) const {
  if (root == nullptr)
    return;
  InorderPrint(os, root->GetLeftSubtree());
  Visit(root);
  InorderPrint(os, root->GetRightSubtree());
}

template <class TreeType>
void BinarySearchTree<TreeType>::PostorderTraverse(void Visit(TreeType&)) const {
  if (root == nullptr)
    return;
  PostOrderPrint(os, root->GetLeftSubtree());
  PostOrderPrint(os, root->GetRightSubtree());
  Visit(root);
}
*/

template <class TreeType>
void BinarySearchTree<TreeType>::DumpValuesAtLevelRecursive(ostream& os, const int& level) const {
  DumpValuesAtLevel(os, root_ptr_, level);
}

template <class TreeType>
void BinarySearchTree<TreeType>::DumpValuesAtLevel(ostream& os, TreeNodePtr root, const int& level) {
  if (root == nullptr)
    return;
  if (k == 1)
    os << root->Value() << '\n';
  DumpValuesAtLevel(os, root->GetLeftSubtree(), k - 1);
  DumpValuesAtLevel(os, root->GetRightSubtree(), k - 1);
}

template <class TreeType>
void BinarySearchTree<TreeType>::DumpValuesAtLevelIterative(ostream& os, const int& level) const {
  if (root == nullptr || level > MaxDepthRecursive())
    return;
  if (level == 1) {
    os << root_ptr_->Value() << '\n';
    return;
  }
  std::queue<TreeNodePtr> parents, children;
  parents.push(root_ptr_);
  int current_level = 2;
  while (current_level < level) {
    while (! parents.empty()) {
      if (parents.front()->GetLeftSubtree() != nullptr)
        children.push(parents.front()->GetLeftSubtree());
      if (parents.front()->GetRightSubtree() != nullptr)
        children.push(parents.front()->GetRightSubtree());
      parents.pop();
    }
    if (current_level == level) {
      while (! childeren.empty()) {
        std::cout << children.front()->Value() << '\n';
        children.pop();
      }
      return; // We have now dumped the values at level, we're done.
    }
    std::swap(parents, children);
    current_level++;
  }
}

template <class TreeType>
void BinarySearchTree<TreeType>::LevelOrderDump(ostream& os) const {
  if (root == nullptr)
    return;
  std::queue<TreeNodePtr> q;
  q.push(root_ptr_);
  while (!q.empty()) {
    TreeNodePtr node = q.front();
    q.pop();
    os << node->Value() << '\n';
    if (node->GetLeftSubtree() != nullptr)
      q.push(node->GetLeftSubtree());
    if (node->GetRightSubtree() != nullptr)
      q.push(node->GetRightSubtree());
  }
}

template <class TreeType>
void BinarySearchTree<TreeType>::InOrderDump(ostream& os) const {
  InorderPrint(os, root_ptr_);
}

template <class TreeType>
void BinarySearchTree<TreeType>::InOrderPrint(ostream& os, TreeNodePtr root) const {
  if (root == nullptr)
    return;
  InorderPrint(os, root->GetLeftSubtree());
  os << root->Value() << '\n';
  InorderPrint(os, root->GetRightSubtree());
}

template <class TreeType>
void BinarySearchTree<TreeType>::PreOrderDump(ostream& os) const {
  PreOrderPrint(os, root_ptr_);
}

template <class TreeType>
void BinarySearchTree<TreeType>::PreOrderPrint(ostream& os, TreeNodePtr root) const {
  if (root == nullptr)
    return;
  os << root->Value() << '\n';
  PreOrderPrint(os, root->GetLeftSubtree());
  PreOrderPrint(os, root->GetRightSubtree());
}

template <class TreeType>
void BinarySearchTree<TreeType>::PostOrderDump(ostream& os) const {
  PostOrderPrint(os, root_ptr_);
}

template <class TreeType>
void BinarySearchTree<TreeType>::PostOrderPrint(ostream& os, TreeNodePtr root) const {
  if (root == nullptr)
    return;
  PostOrderPrint(os, root->GetLeftSubtree());
  PostOrderPrint(os, root->GetRightSubtree());
  os << root->Value() << '\n';
}

template <class TreeType>
int BinarySearchTree<TreeType>::MaxDepthRecursive() const {
  return Depth(root_ptr_);
}

template <class TreeType>
int BinarySearchTree<TreeType>::MaxDepth(TreeNodePtr root) const {
  if (root == nullptr)
    return 0;
  int left = MaxDepth(root->GetLeftSubtree());
  int right = MaxDepth(root->GetRightSubtree());
  return 1 + (left > right ? left : right);
}

template <class TreeType>
int BinarySearchTree<TreeType>::MaxDepthIterative() const {
  if (root_ptr_ == nullptr)
    return 0;
  std::queue<TreeNodePtr> q;
  q.push(root_ptr_);
  int depth = 0;
  while (!q.empty()) {
    int nodes_in_q = q.size();
    while (nodes_in_q > 0) {
      TreeNodePtr node = q.front();
      q.pop();
      if (node->GetLeftSubtree() != nullptr)
        q.push(node->GetLeftSubtree());
      if (node->GetRightSubtree() != nullptr)
        q.push(node->GetRightSubtree());
      nodes_in_q--;
    }
    depth++;
  }
  return depth;
}

template <class TreeType>
TreeType BinarySearchTree<TreeType>::KthSmallest(const int& k) const {
  return (GetSize() < k) ? 0 : GetKthSmallest(root_ptr_, k);
}

template <class TreeType>
TreeType BinarySearchTree<TreeType>::GetKthSmallest(TreeNodePtr root, const int& k) {
  int size_of_left_subtree = NumberOfNodes(root->GetLeftSubtree());
  if (size_of_left_subtree == k - 1)
    return root->Value();
  if (size_of_left_subtree < k)
    return GetKthSmallest(root->GetRightSubtree(), k - size_of_left_subtree - 1);
  return GetKthSmallest(root->GetLeftSubtree(), k);
}

template <class TreeType>
bool BinarySearchTree<TreeType>::HasRootToLeafSum(const int & sum) const {
  return FindPathSumEqualToSum(root->GetLeftSubtree(), sum - GetRootData()) ||
         FindPathSumEqualToSum(root->GetRightSubtree(), sum - GetRootData());
}

template <class TreeType>
bool BinarySearchTree<TreeType>::FindPathSumEqualToSum(TreeNodePtr root, const int& sum) const {
  if (root == nullptr)
    return (sum == 0) ? true : false;
  return FindPathSumEqualToSum(root->GetLeftSubtree(), sum - root->Value()) ||
         FindPathSumEqualToSum(root->GetRightSubtree(), sum - root->Value());
}

template <class TreeType>
bool BinarySearchTree<TreeType>::AreBstIdentical(BinSearchTreePtr bst) {
  return AreTreeNodesEqual(root_ptr_, bst->root_ptr_);
}

template <class TreeType>
bool BinarySearchTree<TreeType>::AreTreeNodesEqual(TreeNodePtr root1, TreeNodePtr root2) const {
  if (root1 == nullptr && root2 == nullptr)
    return true;
  if ((root1 == nullptr && root2 != nullptr) || (root1 != nullptr && root2 == nullptr))
    return false;
  if (root1->Value() != root2->Value())
    return false;
  return AreTreeNodesEqual(root1->GetLeftSubtree(), root2->GetLeftSubtree()) &&
         AreTreeNodesEqual(root1->GetRightSubtree(), root2->GetRightSubtree());
}

template <class TreeType>
BinSearchTreePtr BinarySearchTree<TreeType>::IntersectionWith(BinSearchTreePtr bst) const {
  BinSearchTreePtr the_intersection = std::make_shared<BinarySearchTree<TreeType>>();
  MakeIntersection(the_intersection, root_ptr_, bst);
  return the_intersection;
}

template <class TreeType>
void BinarySearchTree<TreeType>::MakeIntersection(BinSearchTree the_intersection, TreeNodePtr root, BinSearchTreePtr bst)  {
  if (root == nullptr)
    return;
  if (bst->ContainsRecursive(root->Value()))
    the_intersection->Insert(root->Value();
  MakeIntersection(the_intersection, root->GetLeftSubtree(), bst);
  MakeIntersection(the_intersection, root->GetRightSubtree(), bst);
}

template <class TreeType>
BinSearchTreePtr BinarySearchTree<TreeType>::UnionWith(BinSearchTreePtr bst) const {
  BinSearchTreePtr the_union = std::make_shared<BinarySearchTree<TreeType>>();
  MakeUnion(root_ptr_, the_union);
  MakeUnion(bst->root_ptr_, the_union);
  return the_union;
}

template <class TreeType>
void BinarySearchTree<TreeType>::MakeUnion(TreeNodePtr root, BinSearchTreePtr the_union) {
  if (root == nullptr)
    return;
  the_union->Insert(root->Value());
  MakeUnion(root->GetLeftSubtree(), the_union);
  MakeUnion(root->GetRightSubtree(), the_union);
}

template <class TreeType>
BinSearchTreePtr BinarySearchTree<TreeType>::DifferenceOf(BinSearchTreePtr bst) const {
  BinSearchTreePtr the_diff = std::make_shared<BinarySearchTree<TreeType>>();
  MakeDifference(the_diff, bst->root_ptr_);
  return the_diff;
}

template <class TreeType>
void BinarySearchTree<TreeType>::MakeDifference(TreeNodePtr root, BinSearchTree the_diff) const  {
  if (root == nullptr)
    return;
  if (!ContainsRecursive(root->Value()))
    the_diff->Insert(root->Value());
  MakeDifference(the_diff, root->GetLeftSubtree());
  MakeDifference(the_diff, root->GetRightSubtree());
}

template <class TreeType>
bool BinarySearchTree<TreeType>::IsBSubstructureOfA(TreeNodePtr a, TreeNodePtr b) const {
	bool substructure_exists = false;
	std::queue<TreeNodePtr> q;
	q.push(a);
	while(!q.empty()) {
		TreeNodePtr node = q.front();
		q.pop();
		if(node->GetLeftSubtree() != nullptr)
			q.push(node->GetLeftSubtree());
		if(node->GetRightSubtree() != nullptr)
			q.push(node->GetRightSubtree());
		substructure_exists = HasSubstructure(node, b);
	}
	return substructure_exists;
}

template <class TreeType>
bool BinarySearchTree<TreeType>::HasSubstructure(TreeNodePtr a, TreeNodePtr b) const {
	if(a == nullptr && b != nullptr)
		return false;
	if(b->GetLeftSubtree() == nullptr && b->GetRightSubtree() == nullptr)     // if q no children
		return true;
	if((b->GetLeftSubtree() != nullptr) && (b->GetRightSubtree() != nullptr)) // q has 2 children, check them
		return HasSubstructure(a->GetLeftSubtree(), b->GetLeftSubtree()) && HasSubstructure(a->GetRightSubtree(), b->GetRightSubtree());
	if((b->GetLeftSubtree() != nullptr) && (b->rightSubtree() == nullptr))    // q has only a left
		return HasSubstructure(a->GetLeftSubtree(), b->GetLeftSubtree());
	return HasSubstructure(a->GetRightSubtree(), q->GetRightSubtree());		    // q has only a right
}

template <class TreeType>
bool BinarySearchTree<TreeType>::TwoTheSame(TreeNodePtr p, TreeNodePtr q) const {
	if( (p == nullptr && q != nullptr) || (p != nullptr && q == nullptr) || (p == nullptr && q == nullptr) )
		return false;
	if( p->Value() == q->Value() ) {
		std::cout << p->Value() << std::endl;
		return true;
	}
	return TwoTheSame(p->GetLeftSubtree(), q) || TwoTheSame(p->GetRightSubtree(), q) ||
         TwoTheSame(p, q->GetLeftSubtree()) || TwoTheSame(p, q->GetRightSubtree());
}
