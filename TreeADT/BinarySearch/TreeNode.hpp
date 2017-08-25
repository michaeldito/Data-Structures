#ifndef TREE_NODE_
#define TREE_NODE_

#include <memory>

typedef std::shared_ptr<TreeNode<NodeType>> TreeNodePtr;

template <class NodeType>
class TreeNode {
 public:
	TreeNode(): data_(0) {}
	TreeNode(const NodeType& data): data_(n) {}

	TreeNodePtr GetLeftSubtree() 	            { return left_; }
	TreeNodePtr GetRightSubtree() 	          { return right_; }
	void SetLeftSubtree(TreeNodePtr left)     { this->left_ = left; }
	void SetRightSubtree(TreeNodePtr right)   { this->right_ = right; }
	TreeNode& Value() 			      				    { return data_; }

 private:
  TreeNodePtr left_, right_;
	NodeType data_;
};

#endif
