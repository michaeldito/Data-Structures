#include "Node.hpp"

template <class NodeType>
Node<NodeType>::Node() {}

template <class NodeType>
Node<NodeType>::Node(const NodeType& data): data_(data) {}

template <class NodeType>
Node<NodeType>::Node(const NodeType& data, std::shared_ptr<Node<NodeType>> next): data_(data), next_(next) {}

template <class NodeType>
void Node<NodeType>::SetData(const NodeType& data) {
  data_ = data;
}

template <class NodeType>
void Node<NodeType>::SetNext(std::shared_ptr<Node<NodeType>> next) {
  next_ = next;
}

template <class NodeType>
NodeType Node<NodeType>::GetData() const {
  return data_;
}

template <class NodeType>
auto Node<NodeType>::GetNext() const {
  return next_;
}
