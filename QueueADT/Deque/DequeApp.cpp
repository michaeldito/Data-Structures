#include "LinkedDeque.hpp"
#include "ArrayDeque.hpp"
#include <iostream>

using std::cout;

int main() {
  std::string names[] = { "John", "Sally", "Jimmy", "Kira", "Bella", "Dean" };
  //DequeInterface<std::string>* dq = new LinkedDeque<std::string>();
  ArrayDeque<std::string>* dq = new ArrayDeque<std::string>();
  cout << "Adding names to deque...\n";

  int front = 2, back = 3;
  while (front >= 0 && back <= 5) {
    dq->AddToFront(names[front]);
    dq->AddToBack(names[back]);
    front--;
    back++;
  }

  dq->print();

  cout << "Size = " << dq->GetSize() << '\n';

  while (!dq->IsEmpty() && dq->GetSize() > 0) {
    cout << "Front = " << dq->PeekFront() << '\n';
    cout << "Back  = " << dq->PeekBack() << '\n';
    dq->RemoveFront();
    dq->RemoveBack();
  }

  return 0;
}
