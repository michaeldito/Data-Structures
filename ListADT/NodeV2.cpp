#include "NodeV2.hpp"

template <class NodeType>
NodeV2<NodeType>::NodeV2() {}

template <class NodeType>
NodeV2<NodeType>::NodeV2(const NodeType& data): data_(data) {}

template <class NodeType>
NodeV2<NodeType>::NodeV2(const NodeType& data, std::shared_ptr<NodeV2<NodeType>> next): data_(data), next_(next) {}

template <class NodeType>
void NodeV2<NodeType>::SetData(const NodeType& data) {
  data_ = data;
}

template <class NodeType>
void NodeV2<NodeType>::SetNext(std::shared_ptr<NodeV2<NodeType>> next) {
  next_ = next;
}

template <class NodeType>
NodeType NodeV2<NodeType>::GetData() const {
  return data_;
}

template <class NodeType>
auto NodeV2<NodeType>::GetNext() const {
  return next_;
}
