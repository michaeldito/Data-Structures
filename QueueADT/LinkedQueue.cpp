#include "LinkedQueue.hpp"

template <class QueueType>
LinkedQueue<QueueType>::LinkedQueue(): count_(0) {}

template <class QueueType>
LinkedQueue<QueueType>::LinkedQueue(const LinkedQueue& Q)  throw(MemoryAllocationExcept) {
  count_ = Q.count_;
  auto original_chain_ptr = Q.front_ptr_;
  if (original_chain_ptr == nullptr) {
    front_ptr_ = nullptr;
  } else {
    // Copy first node.
    front_ptr_ = std::make_shared<Node<QueueType>>();
    front_ptr_->SetData(original_chain_ptr->GetData());

    // Copy remaining nodes.
    auto new_chain_ptr = front_ptr_;
    if (new_chain_ptr == nullptr) {
      throw MemoryAllocationExcept();
    }
    original_chain_ptr = original_chain_ptr->GetNext();

    while (original_chain_ptr != nullptr) {
      // Get next data from original chain.
      QueueType next_data = original_chain_ptr->GetData();
      // Create a new node containing the next data.
      auto new_node_ptr = std::make_shared<Node<QueueType>>(next_data);
      if (new_node_ptr == nullptr) {
        throw MemoryAllocationExcept();
      }
      // Link new node to end of new chain.
      new_chain_ptr->SetNext(new_node_ptr);
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

template <class QueueType>
LinkedQueue<QueueType>::~LinkedQueue() {
  front_ptr_.reset();
  back_ptr_.reset();
}

template <class QueueType>
bool LinkedQueue<QueueType>::IsEmpty() const {
  return front_ptr_ == nullptr;
}

template <class QueueType>
int LinkedQueue<QueueType>::GetSize() const {
  return count_;
}

template <class QueueType>
bool LinkedQueue<QueueType>::Enqueue(const QueueType& entry) throw(MemoryAllocationExcept) {
  auto new_node_ptr = std::make_shared<Node<QueueType>>(entry);
  if (new_node_ptr == nullptr) {
    throw MemoryAllocationExcept();
    return false;
  }
  // Insert the new Node
  if (IsEmpty())
    front_ptr_ = new_node_ptr;
  else
    back_ptr_->SetNext(new_node_ptr);

  back_ptr_ = new_node_ptr;
  count_++;
  return true;
}

template <class QueueType>
bool LinkedQueue<QueueType>::Dequeue() {
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
      }
    node_to_delete->SetNext(nullptr);
    count_--;
    result = true;
  }
  return result;
}

template <class QueueType>
QueueType LinkedQueue<QueueType>::PeekFront() const throw(PrecondViolatedExcept) {
  if (IsEmpty())
    throw PrecondViolatedExcept("PeekFront() called with empty queue.");
    return front_ptr_->GetData();
}
