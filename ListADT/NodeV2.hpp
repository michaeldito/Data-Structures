#ifndef NODE_V2_
#define NODE_V2_

#include <memory>

template <class NodeType>
class NodeV2 {
 public:
   NodeV2();
   NodeV2(const NodeType& data);
   NodeV2(const NodeType& data, std::shared_ptr<NodeV2<NodeType>> next);
   void SetData(const NodeType& data);
   void SetNext(std::shared_ptr<NodeV2<NodeType>> next);
   NodeType GetData() const;
   auto GetNext() const;

 private:
   NodeType data_;
   std::shared_ptr<NodeV2<NodeType>> next_;
};

#include "NodeV2.cpp"
#endif
