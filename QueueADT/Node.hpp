#ifndef NODE_
#define NODE_

#include <memory>

template <class NodeType>
class Node {
 public:
   Node();
   Node(const NodeType& data);
   Node(const NodeType& data, std::shared_ptr<Node<NodeType>> next);
   void SetData(const NodeType& data);
   void SetNext(std::shared_ptr<Node<NodeType>> next);
   NodeType GetData() const;
   auto GetNext() const;

 private:
   NodeType data_;
   std::shared_ptr<Node<NodeType>> next_;
};

#include "Node.cpp"
#endif
