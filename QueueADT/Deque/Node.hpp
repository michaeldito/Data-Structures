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
   void SetPrev(std::shared_ptr<Node<NodeType>> prev);
   NodeType GetData() const;
   auto GetNext() const;
   auto GetPrev() const;

 private:
   NodeType data_;
   std::shared_ptr<Node<NodeType>> next_;
   std::shared_ptr<Node<NodeType>> prev_;
};

#include "Node.cpp"
#endif
