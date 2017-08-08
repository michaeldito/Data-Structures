#include <iostream>
#include "ArrayStack.hpp"
#include "LinkedStack.hpp"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

int main() {
  string food[5] = { "eggs", "pancakes", "hashbrowns", "sausage", "bacon" };
  //LinkedStack<string> myStack;
  ArrayStack<string> myStack;
  try {
    string item = myStack.Peek();
  }
  catch (PrecondViolatedExcept e) {
    cerr << e.what() << endl;
  }

  for(unsigned int i = 0; i < 5; ++i) {
    try {
      myStack.Push(food[i]);
    }
    catch (MemoryAllocationExcept e) {
      cerr << e.what() << endl;
    }
  }

  if (myStack.IsEmpty())
    cout << "Stack is not empty; Push is bad.\n";
  else
    cout << "Stack has items; Push is good.\n";

  cout << "Stack size: " << myStack.GetSize() << '\n';

  try {
    cout << "Top of stack should be bacon. It is - " << myStack.Peek() << '\n';
  }
  catch (PrecondViolatedExcept e) {
    cerr << e.what() << endl;
  }

  while (!myStack.IsEmpty())
    myStack.Pop();

  if (myStack.IsEmpty())
    cout << "Stack Pop is Good; Stack is empty\n";

  return 0;
}
