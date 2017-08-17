#include "ArrayList.hpp"
//#include "LinkedList.hpp"
#include "LinkedListV2.hpp"

#include <iostream>

using std::cout;
using std::cerr;

void print(LinkedListV2<int> list) {
  for (int i = 1; i <= list.GetLength(); ++i)
    cout << list.GetEntry(i) << ',';
  cout << '\n';
}

int main() {
//  ListInterface<int>* list;
//  ListInterface<int>* list;
 LinkedListV2<int> list;

  for (int i = 1; i < 10; ++i)
    list.Insert(i, i);

  if (!list.IsEmpty())
    cout << "Length of list: " << list.GetLength() << '\n';

  cout << "Printing: ";
  print(list);

  cout << "Removing even numbers...\n";
  int i = 1;
  while (i < list.GetLength()) {
    if (list.GetEntry(i) % 2 == 0) { // if nodes data is even
      list.Remove(i);
    }
    i++;
  }

  cout << "Length of list: " << list.GetLength() << '\n';

  for (int i = 0; i < list.GetLength(); ++i) {
    try {
      int item = list.GetEntry(i);
    }
    catch (PrecondViolatedExcept e) {
      cerr << e.what() << '\n';
    }
  }

  cout << "Printing: ";
  print(list);

  try{
    cout << "Replacing 3 and 7...\n";
    int nv = list.Replace(2, 100);
    cout << nv << ',';
    nv = list.Replace(4, 100);
    cout << nv << ',';
    nv = list.Replace(10, 100);
    cout << nv << ',';
  }
  catch(PrecondViolatedExcept e){
    cout << e.what();
  }

  cout << "\nPrinting: ";
  print(list);


  cout << "Copying List...\n";
  LinkedListV2<int> list2 = list;


  cout << "Clearing list...\n";
  list.Clear();

  cout << "Printing list 2 for deep copy check\n";
  print(list2);

  if (list.IsEmpty())
    cout << "Length of list: " << list.GetLength() << '\n';
  if (list2.IsEmpty())
    cout << "List 2 also empty :[\n";

  if (!list2.IsEmpty()) {
    cout << "Clearing list2...\n";
    list2.Clear();
    if (list2.IsEmpty()) {
      cout << "list2 now empty.\n";
    }
  }

  return 0;
}
