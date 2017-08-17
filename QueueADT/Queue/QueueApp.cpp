#include "LinkedQueue.hpp"
#include "ListQueue.hpp"
#include "ArrayCircularQueue.hpp"
#include "DynamicArrayCircularQueue.hpp"

#include <iostream>

using std::cout;

void printAndDelete(ListQueue<int>& Q) {
    while (!Q.IsEmpty()) {
      int data = Q.PeekFront();
      cout << data << ',';
      Q.Dequeue();
  }
  cout << '\n';
}

int main() {
  ListQueue<int> q;
  //QueueInterface<int>* q = new LinkedQueue<int>();
  //QueueInterface<int>* q = new ArrayCircularQueue<int>();
  //QueueInterface<int>* q = new DynamicArrayCircularQueue<int>();

  int add2q[] = { 4, 65, 3, 8, 9 , 23, 78, 99, 0, 11 };

  for (int i = 0; i < 10; ++i)
    q.Enqueue(add2q[i]);

  if (q.GetSize() == 10 && !(q.IsEmpty()))
    cout << "Size == 10 && q not empty\n";

  cout << "Front of queue should be 4 - it is " << q.PeekFront() << '\n';

  cout << "Copying queue...\n";

  ListQueue<int> cp = q;

  if (cp.GetSize() == 10 && !(cp.IsEmpty()))
    cout << "Size == 10 && q not empty\n";
  cout << "Front of queue should be 4 - it is " << cp.PeekFront() << '\n';

  cout << "q size = " << q.GetSize() << "; deleting q\n";
  printAndDelete(q);
  cout << "q size = " << q.GetSize() << '\n';


  if (q.GetSize() == 0 && cp.GetSize() == 10)
    cout << "Dequeue works ok\n";
  else
    cout << "uhoh\n";

  cout << "cp size = " << cp.GetSize() << '\n';
  printAndDelete(cp);
  cout << "cp size = " << cp.GetSize() << '\n';

  try {
    cout << q.PeekFront();
  }
  catch (PrecondViolatedExcept e) {
    cout << e.what() << '\n';
  }

  return 0;
}
