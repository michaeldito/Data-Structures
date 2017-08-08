#include "LinkedBag.hpp"

template <class BagType>
LinkedBag<BagType>::LinkedBag(): head_(nullptr), bag_count_(0) {}

template <class BagType>
LinkedBag<BagType>::LinkedBag(const LinkedBag<BagType>& bag) {
  bag_count_ = bag.bag_count_;
  Node<BagType>* original_chain_ptr = bag.head_;
  if (original_chain_ptr == nullptr) {
    head_ = nullptr;
  } else {

    // Copy first node.
    head_ = new Node<BagType>();
    head_->SetData(original_chain_ptr->GetData());

    // Copy remaining nodes.
    Node<BagType>* new_chain_ptr = head_;
    original_chain_ptr = original_chain_ptr->GetNext();

    while (original_chain_ptr != nullptr) {
      // Get next data from original chain.
      BagType next_data = original_chain_ptr->GetData();
      // Create a new node containing the next data.
      Node<BagType>* new_node_ptr = new Node<BagType>(next_data);
      // Link new node to end of new chain.
      new_chain_ptr->SetNext(new_node_ptr);
      // Advance the pointers.
      new_chain_ptr = new_chain_ptr->GetNext();
      original_chain_ptr = original_chain_ptr->GetNext();
    }
    // End the new chain.
    new_chain_ptr->SetNext(nullptr);
  }
}

template <class BagType>
LinkedBag<BagType>::~LinkedBag() {
  Clear();
}

template <class BagType>
int LinkedBag<BagType>::GetSize() const {
  return bag_count_;
}

template <class BagType>
bool LinkedBag<BagType>::IsEmpty() const {
  return bag_count_ == 0;
}

template <class BagType>
bool LinkedBag<BagType>::Add(const BagType& entry) {
  Node<BagType>* newNode = new Node<BagType>();
  newNode->SetData(entry);
  newNode->SetNext(head_);
  head_ = newNode;
  bag_count_++;

  return true;
}

template <class BagType>
bool LinkedBag<BagType>::Remove(const BagType& entry) {
  Node<BagType>* node_to_remove = GetPointerTo(entry);
  bool remove_allowed = !IsEmpty() && (node_to_remove != nullptr);
  if (remove_allowed) {
    // Copy data from the head to the node that will be removed.
    node_to_remove->SetData(head_->GetData());
    // Disconnect the head.
    Node<BagType>* node_to_delete = head_;
    head_ = head_->GetNext();
    // Return the node to memory.
    node_to_delete->SetNext(nullptr);
    delete node_to_delete;
    node_to_delete = nullptr;

    bag_count_--;
  }
  return remove_allowed;
}

template <class BagType>
void LinkedBag<BagType>::Clear() {
  Node<BagType>* node_to_remove = head_;
  while (head_ != nullptr) {
    head_ = head_->GetNext();
    // Return node to memory.
    node_to_remove->SetNext(nullptr);
    delete node_to_remove;
    node_to_remove = head_;
  }
  bag_count_ = 0;
}

template <class BagType>
bool LinkedBag<BagType>::Contains(const BagType& entry) const {
  return GetPointerTo(entry) != nullptr;
}

template <class BagType>
int LinkedBag<BagType>::GetFrequencyOf(const BagType& entry) const {
  int frequency = 0;
  Node<BagType>* current = head_;
  while (current != nullptr) {
    if (current->GetData() == entry)
      frequency++;
    current = current->GetNext();
  }
  return frequency;
}

template <class BagType>
std::vector<BagType> LinkedBag<BagType>::ToVector() const {
  std::vector<BagType> vector_bag;
  Node<BagType>* current = head_;
  int counter = 0;
  while ((current != nullptr) && (counter < bag_count_)) {
    vector_bag.push_back(current->GetData());
    current = current->GetNext();
    counter++;
  }
  return vector_bag;
}

template <class BagType>
Node<BagType>* LinkedBag<BagType>::GetPointerTo(const BagType& target) const {
  Node<BagType>* current = head_;
  while (current != nullptr) {
    if (current->GetData() == target)
      return current;
    current = current->GetNext();
  }
  return nullptr;
}
