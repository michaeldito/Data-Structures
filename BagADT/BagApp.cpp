#include <iostream>
#include "ArrayBag.hpp"
#include "LinkedBag.hpp"

using std::string;
using std::cout;
using std::endl;

int main()
{
//  ArrayBag<int> int_bag;
  LinkedBag<int> int_bag;

  cout << "Inserting: ";
  for (int i = 0; i < 10; ++i) {
    cout << i;
    int_bag.Add(i);
  }
  cout << endl;

  cout << "Size: " << int_bag.GetSize() << endl;

  if (int_bag.IsEmpty())
    std::cout << "Bag is empty" << endl;
  else
    std::cout << "Bag is not empty" << endl;

  cout << "Removing 1\n";
  int_bag.Remove(1);
  cout << "Size: " << int_bag.GetSize() << endl;
  if (int_bag.Contains(1))
    cout << "Remove is broken" << endl;
  else
    cout << "Remove is good" << endl;

  cout << "Converting to Vector...Printing Vector" << endl;
  std::vector<int> int_vector_bag = int_bag.ToVector();
  for (std::size_t i = 0; i < int_vector_bag.size(); ++i)
    cout << int_vector_bag[i];
  cout << endl;

  cout << "Inserting 2\n";
  int_bag.Add(2);
  cout << "Bag contains number 2: " << int_bag.GetFrequencyOf(2) << " times" << endl;

  cout << "Converting to Vector...Printing Vector" << endl;
  int_vector_bag = int_bag.ToVector();
  for (std::size_t i = 0; i < int_vector_bag.size(); ++i)
    cout << int_vector_bag[i];
  cout << endl;

  cout << "Creating a copy...\n";
  LinkedBag<int> copy = int_bag;

  cout << "Converting Copy to Vector...Printing Vector" << endl;
  int_vector_bag = copy.ToVector();
  for (std::size_t i = 0; i < int_vector_bag.size(); ++i)
    cout << int_vector_bag[i];
  cout << endl;

  cout << "Clearing Bag...\n";
  int_bag.Clear();
  cout << "Size: " << int_bag.GetSize() << endl;

  return 0;
}
