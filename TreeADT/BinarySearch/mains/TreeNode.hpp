#ifndef TREE_NODE_
#define TREE_NODE_

#include <memory>

template <class NodeType>
class TreeNode {
 public:
	TreeNode(): data_(NULL) {}
	TreeNode(const NodeType& data): data_(data) {}

	std::shared_ptr<TreeNode<NodeType>> GetLeftSubtree() 	          { return left_; }
	std::shared_ptr<TreeNode<NodeType>> GetRightSubtree() 	        { return right_; }
	void SetLeftSubtree(std::shared_ptr<TreeNode<NodeType>> left)   { this->left_ = left; }
	void SetRightSubtree(std::shared_ptr<TreeNode<NodeType>> right) { this->right_ = right; }
  NodeType& Value() 			      				                          { return data_; }

  bool IsLeaf() const { return ((left_ == nullptr) && (right_ == nullptr)); }

 private:
  std::shared_ptr<TreeNode<NodeType>> left_, right_;
	NodeType data_;
};

#endif
