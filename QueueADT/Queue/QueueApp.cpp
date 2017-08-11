#include "LinkedQueue.hpp"
#include "ListQueue.hpp"
#include "ArrayCircularQueue.hpp"
#include "DynamicArrayCircularQueue.hpp"

#include <iostream>

using std::cout;

int main() {
  QueueInterface<int>* q = new ListQueue<int>();
  //QueueInterface<int>* q = new LinkedQueue<int>();
  //QueueInterface<int>* q = new ArrayCircularQueue<int>();
  //QueueInterface<int>* q = new DynamicArrayCircularQueue<int>();

  int add2q[] = { 4, 65, 3, 8, 9 , 23, 78, 99, 0, 11 };

  for (int i = 0; i < 10; ++i)
    q->Enqueue(add2q[i]);

  if (q->GetSize() == 10 && !(q->IsEmpty()))
    cout << "Size == 10 && q not empty\n";

  cout << "Front of queue should be 4 - it is " << q->PeekFront() << '\n';

  cout << "\nCopying queue...\n";
  QueueInterface<int>* cp = q;

  if (cp->GetSize() == 10 && !(cp->IsEmpty()))
    cout << "Size == 10 && q not empty\n";
  cout << "Front of queue should be 4 - it is " << cp->PeekFront() << '\n';

  cout << "q size = " << q->GetSize() << '\n';
  for (int i = 0; i < 10; ++i) {
    q->Dequeue();
  }
  cout << "cp size = " << cp->GetSize() << '\n';
  for (int i = 0; i < 10; ++i) {
    cp->Dequeue();
  }

  if (q->GetSize() == 0 && cp->GetSize() == 0)
    cout << "Dequeue works ok\n";

  cout << q->PeekFront();

  return 0;
}
