#include "LinkedList.hpp"
#include <cassert>

template <class ListType>
LinkedList::LinkedList(): head_(nullptr), list_count_(0) {}

template <class ListType>
LinkedList::LinkedList(const LinkedList<ListType>& L) {
  list_count_ = L.list_count_;
  Node<ListType>* original_chain_ptr = L.head_;
  if (original_chain_ptr == nullptr) {
    head_ = nullptr;
  } else {
    // Copy first node.
    head_ = new Node<ListType>();
    head_->SetData(original_chain_ptr->GetData());

    // Copy remaining nodes.
    Node<ListType>* new_chain_ptr = head_;
    original_chain_ptr = original_chain_ptr->GetNext();

    while (original_chain_ptr != nullptr) {
      // Get next data from original chain.
      ListType next_data = original_chain_ptr->GetData();
      // Create a new node containing the next data.
      Node<ListType>* new_node_ptr = new Node<ListType>(next_data);
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

template <class ListType>
LinkedList::~LinkedList() {
  Clear();
}

template <class ListType>
bool LinkedList::IsEmpty() const {
  return list_count_ == 0 && head_ == nullptr;
}

template <class ListType>
int LinkedList::GetLength() const {
  return list_count_;
}

template <class ListType>
bool LinkedList::Insert(int position, const ListType& entry) {
  bool able_to_insert = (position >= 1) && (position <= list_count_ + 1);
  if (able_to_insert) {
    // Create a new node containing the new entry
    Node<ListType>* new_node = new Node<ListType>(entry);
    // Attach the node to the chain
    if (position == 1) {
      new_node->SetNext(head_);
      head_ = new_node;
    } else {
        // Find node that will be before the new node
        Node<ListType>* prev = GetNodeAt(position - 1);
        new_node->SetNext(prev->GetNext());
        prev->SetNext(new_node);
    }
    list_count_++;
  }
  return able_to_insert;
}

template <class ListType>
bool LinkedList::Remove(int position) {
  bool able_to_remove = (position >= 1) && (position <= list_count_);
  if (able_to_remove) {
    Node<ListType>* current = nullptr;
    if (position == 1) {
      // Remove the first node in the chain
      current = head_;
      head_ = head_->GetNext();
    } else {
        Node<ListType>* prev = GetNodeAt(position - 1);
        current = prev->GetNext();
        prev = SetNext(current->GetNext());
    }
    // Return node to memory
    current->SetNext(nullptr);
    delete current;
    current = nullptr;

    list_count_--;
  }
  return able_to_remove;
}

template <class ListType>
void LinkedList::Clear() {
  while (!IsEmpty())
    Remove(1);
}

template <class ListType>
ListType LinkedList::GetEntry(int position) const throw(PrecondViolatedExcept) {
  // Enforce Precondition
  bool able_to_get = (position >= 1) && (position <= list_count_);
  if (able_to_get) {
    Node<ListType>* node = GetNodeAt(position);
    return node->GetData();
  } else {
      std::string message = "GetEntry() called with an empty list or invalid position.";
      throw(PrecondViolatedExcept(message));
  }
}

template <class ListType>
ListType LinkedList::Replace(int position, const ListType& entry) const throw(PrecondViolatedExcept) {
  // Enforce Precondition
  bool able_to_set = (position >= 1) && (position <= list_count_);
  if (able_to_set) {
    // First get to the node that will be replaced
    Node<ListType>* old_entry = GetNodeAt(position);
    // Then get a copy of its data
    ListType old_entry_data = old_entry->GetData();
    // Now replace the nodes data with entry
    old_entry->SetData(entry);
    return old_entry_data;
  } else {
      std::string message = "Replace() called with an empty list or invalid position.";
      throw(PrecondViolatedExcept(message));
  }
}

template <class ListType>
Node<ListType>* LinkedList::GetNodeAt(int position) const {
  assert((position >= 1) && (position <= list_count_));
  // Count from the beginning of the chain
  Node<ListType>* current = head_;
  for (int skip = 1; skip < position; skip++)
    current = current->GetNext();

  return current;
}
