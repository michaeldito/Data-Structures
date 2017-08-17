#include "SortedListPriorityQueue.hpp"
#include <iostream>

using std::cout;

int main() {
  SortedListPriorityQueue<int> pq;

  cout << "Inserting: ";
  for (int i = 0; i <= 10; i++)
    if (i % 2 == 0) {
      cout << i << ", ";
      pq.Enqueue(i);
    }

  for (int i = 0; i <= 10; i++)
    if (i % 2) {
      if (i < 9)
        cout << i << ", ";
      else
        cout << i << '\n';
      pq.Enqueue(i);
    }

  if (pq.GetSize() == 11 && !pq.IsEmpty())
    cout << "PQ has 11 elements\n";

  cout << "Copying pq...\n";

  SortedListPriorityQueue<int> cp = pq;

  for (int i = 10; i >= 0; i--) {
    cout << "Front of pq should be " << i << " - it is " << pq.PeekFront() << '\n';
    pq.Dequeue();
  }

  cout << "pq size = " << pq.GetSize() << "; cp size = " << cp.GetSize() << '\n';
  for (int i = 10; i >= 0; i--) {
    cout << "Front of cp should be " << i << " - it is " << cp.PeekFront() << '\n';
    cp.Dequeue();
  }

  if (pq.IsEmpty() && cp.IsEmpty())
    cout << "Both are empty\n";
  else
    cout << "Both are not empty\n";

  return 0;
}
