#include "LinkedDeque.hpp"

template <class DequeType>
LinkedDeque<DequeType>::LinkedDeque(): count_(0) {}

template <class DequeType>
LinkedDeque<DequeType>::LinkedDeque(const LinkedDeque& D) throw(MemoryAllocationExcept) {
  count_ = D.count_;
  auto original_chain_ptr = D.front_ptr_;
  if (original_chain_ptr == nullptr) {
    front_ptr_ = nullptr;
  } else {
    // Copy first node.
    front_ptr_ = std::make_shared<Node<DequeType>>();
    front_ptr_->SetData(original_chain_ptr->GetData());
    front_ptr_->SetPrev(nullptr);

    // Copy remaining nodes.
    auto new_chain_ptr = front_ptr_;
    if (new_chain_ptr == nullptr) {
      throw MemoryAllocationExcept();
    }
    original_chain_ptr = original_chain_ptr->GetNext();

    while (original_chain_ptr != nullptr) {
      // Get next data from original chain.
      DequeType next_data = original_chain_ptr->GetData();
      // Create a new node containing the next data.
      auto new_node_ptr = std::make_shared<Node<DequeType>>(next_data);
      if (new_node_ptr == nullptr) {
        throw MemoryAllocationExcept();
      }
      // Link new node to end of new chain.
      new_chain_ptr->SetNext(new_node_ptr);
      new_node_ptr->SetPrev(new_chain_ptr);
      // Advance the pointers.
      new_chain_ptr = new_chain_ptr->GetNext();
      original_chain_ptr = original_chain_ptr->GetNext();
    }
    // End the new chain.
    new_chain_ptr->SetNext(nullptr);
    // Set the back pointer
    back_ptr_ = new_chain_ptr;
  }
}

template <class DequeType>
LinkedDeque<DequeType>::~LinkedDeque() {
  front_ptr_.reset();
  back_ptr_.reset();
}

template <class DequeType>
bool LinkedDeque<DequeType>::IsEmpty() const {
  return front_ptr_ == nullptr;
}

template <class DequeType>
int LinkedDeque<DequeType>::GetSize() const {
  return count_;
}

template <class DequeType>
bool LinkedDeque<DequeType>::AddToBack(const DequeType& entry) throw(MemoryAllocationExcept) {
  auto new_node_ptr = std::make_shared<Node<DequeType>>(entry);
  if (new_node_ptr == nullptr) {
    throw MemoryAllocationExcept();
    return false;
  }
  // Insert the new Node
  if (IsEmpty())
    front_ptr_ = new_node_ptr;

  back_ptr_->SetNext(new_node_ptr);
  new_node_ptr->SetPrev(back_ptr_);

  back_ptr_ = new_node_ptr;
  count_++;
  return true;
}

template <class DequeType>
bool LinkedDeque<DequeType>::AddToFront(const DequeType& entry) throw(MemoryAllocationExcept) {
  auto new_node_ptr = std::make_shared<Node<DequeType>>(entry);
  if (new_node_ptr == nullptr) {
    throw MemoryAllocationExcept();
    return false;
  }
  // Insert the new Node
  if (IsEmpty()) {
    front_ptr_ = new_node_ptr;
    back_ptr_ = new_node_ptr;
  }
  else {
    // Get pointer to what will be the second node
    auto second_node_ptr = front_ptr_;
    front_ptr_ = new_node_ptr;
    new_node_ptr->SetNext(second_node_ptr);
    new_node_ptr->SetPrev(nullptr);
  }

  count_++;
  return true;
}

template <class DequeType>
bool LinkedDeque<DequeType>::RemoveFront() {
  bool result = false;
  if (!IsEmpty()) {
    auto node_to_delete = front_ptr_;
    if (front_ptr_ == back_ptr_) {
      // Special case: one node in Queue
      // Set front_ptr_ and back_ptr_ to nullptr
      front_ptr_.reset();
      back_ptr_.reset();
    } else {
        front_ptr_ = front_ptr_->GetNext();
        front_ptr_->SetPrev(nullptr);
      }
    node_to_delete->SetNext(nullptr);
    count_--;
    result = true;
  }
  return result;
}

template <class DequeType>
bool LinkedDeque<DequeType>::RemoveBack() {
  bool result = false;
  if (!IsEmpty()) {
    auto node_to_delete = back_ptr_;
    if (front_ptr_ == back_ptr_) {
      // Special case: one node in Queue
      // Set front_ptr_ and back_ptr_ to nullptr
      front_ptr_.reset();
      back_ptr_.reset();
    } else {
        back_ptr_ = back_ptr_->GetPrev();
        back_ptr_->SetNext(nullptr);
      }
    node_to_delete->SetPrev(nullptr);
    count_--;
    result = true;
  }
  return result;
}

template <class DequeType>
DequeType LinkedDeque<DequeType>::PeekFront() const throw(PrecondViolatedExcept) {
  if (IsEmpty())
    throw PrecondViolatedExcept("PeekFront() called with empty deque.");
    return front_ptr_->GetData();
}

template <class DequeType>
DequeType LinkedDeque<DequeType>::PeekBack() const throw(PrecondViolatedExcept) {
  if (IsEmpty())
    throw PrecondViolatedExcept("PeekBack() called with empty deque.");
    return back_ptr_->GetData();
}
