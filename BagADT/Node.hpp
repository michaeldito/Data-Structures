#ifndef NODE_
#define NODE_

template <class NodeType>
class Node {
 public:
   Node();
   Node(const NodeType& data);
   Node(const NodeType& data, Node<NodeType>* next);
   void SetData(const NodeType& data);
   void SetNext(Node<NodeType>* next);
   NodeType GetData() const;
   Node<NodeType>* GetNext() const;

 private:
   NodeType data_;
   Node<NodeType>* next_;
};

#include "Node.cpp"
#endif
