#include "BinarySearchTree.hpp"

#include <iostream>
#include <fstream>

void enterToContinue() {
  std::cout << "\nEnter to continue\n";
  std::cin.get();
}

int main(int argc, char *argv[]) {

  std::cout << "Press enter to begin Binary Search Tree Tests.\n\n";

  enterToContinue();

  if (argc != 2) {
      std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
      std::cout << "BinarySearchTree testing ends.\n";
      return 1;
  }

  std::cout << "Testing default constructor: ";

  std::shared_ptr<BinarySearchTree<int>> tree = std::make_shared<BinarySearchTree<int>>();
  std::shared_ptr<BinarySearchTree<int>> tree2 = std::make_shared<BinarySearchTree<int>>();

  if (tree != nullptr && tree2 != nullptr)
    std::cout << "Passed\n\n";
  else
    std::cout << "Failed\n";

  std::vector<int> treeValues;

  std::fstream infile;
  infile.open(argv[1]);

  if(!infile.is_open()) {
      std::cout << "Unable to open input-file: " << argv[1] << std::endl;
      std::cout << "BinarySearchTree testing ends.\n";
      return 1;
  }

  std::cout << "Input file opened.\nTesting Insert, Contains(Recursive/Iterative), GetSize...\n";

  std::cout << "Inserting: ";
  int v;
  while(infile >> v ) {
    if(!tree->ContainsRecursive(v))  {
        std::cout << v << ' ';
        tree->Insert(v);
        tree2->Insert(v);
        treeValues.push_back(v);
      }
  }

  std::cout << "\nTree construction complete\n";

  enterToContinue();

  if (tree->GetSize() == 10)
    std::cout << "GetSize: Passed\n";
  else
    std::cout << "GetSize: Failed\n";

  bool passed = true;
  int i = 1;
  while (i <= 10 || !passed) {
    if (!tree->ContainsRecursive(i))
      passed = false;
    i++;
  }

  if (passed)
    std::cout << "ContainsRecursive: Passed\n";
  else
    std::cout << "ContainsRecursive: Failed\n";

  passed = true;
  i = 1;
  while (i <= 10 || !passed) {
    if (!tree->ContainsIterative(i))
      passed = false;
    i++;
  }

  if (passed)
    std::cout << "ContainsIterative: Passed\n";
  else
    std::cout << "ContainsIterative: Failed\n";

  std::cout << "* If all passed so far - Insert looks good\n";

  enterToContinue();

  std::cout << "Testing LevelOrderDump - Should be 5 3 7 2 4 6 8 1 9 10\n";

  tree->LevelOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing MaxDepth(Recursive/Iterative) == 5\n";

  if (tree->MaxDepthRecursive() != 5)
    std::cout << "MaxDepthRecursive: Failed\n";
  else
    std::cout << "MaxDepthRecursive: Passed\n";

  if (tree->MaxDepthIterative() != 5)
    std::cout << "MaxDepthRecursive: Failed\n";
  else
    std::cout << "MaxDepthRecursive: Passed\n";

  enterToContinue();

  std::cout << "Testing DumpValuesAtLevel(Recursive/Iterative) - Should be same as LevelOrderDump\n";

  std::cout << "Recursive:\n";
  for (int i = 1; i <= tree->MaxDepthIterative(); i++)
    tree->DumpValuesAtLevelRecursive(std::cout, i);

  std::cout << "Iterative:\n";
  for (int i = 1; i <= tree->MaxDepthIterative(); i++)
    tree->DumpValuesAtLevelIterative(std::cout, i);

  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing InOrderDump - Should be 1->10\n";

  tree->InOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing PreOrderDump - Should be 5 3 2 1 4 7 6 8 9 10\n";

  tree->PreOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing PostOrderDump - Should be 1 2 4 3 6 10 9 8 7 5\n";

  tree->PostOrderDump(std::cout);
  std::cout << "How does it look\n";

  enterToContinue();

  std::cout << "Testing KthSmallest - Should be 1->10\n";
  for (int i = 1; i <= 10; i++)
    std::cout << tree->KthSmallest(i) << '\n';

  enterToContinue();

  std::cout << "Testing HasRootToLeafSum for 11 12 18 39 (true) 7 20 (false):\n";

  int a[6] = { 11, 12, 18, 39, 7, 20 };
  passed = true;
  for (int i = 0; i < 6; i++) {
    if (i < 4) {
      if (!tree->HasRootToLeafSum(a[i])) {
        passed = false;
        std::cout << "Uh-oh [" << a[i] << "] a true number is false\n";
      }
    } else {
        if (tree->HasRootToLeafSum(a[i])) {
          passed = false;
          std::cout << "Uh-oh [" << a[i] << "] a false number is true\n";
        }
      }
  }

  if (passed)
    std::cout << "HasRootToLeafSum: Passed\n";
  else
    std::cout << "HasRootToLeafSum: Failed\n";

  enterToContinue();

  std::cout << "Testing Remove:\nDeleting Leaves(1, 10)\n";

  std::cout << "Before:\n";
  tree->LevelOrderDump(std::cout);
  tree->Remove(1);
  tree->Remove(10);

  enterToContinue();

  std::cout << "After: ";
  tree->LevelOrderDump(std::cout);
  std::cout << "Deleting - One Subtree[right](8)\n";
  tree->Remove(8);

  enterToContinue();

  tree->LevelOrderDump(std::cout);
  std::cout << "Deleting - TwoSubtrees(5 root)\n";
  tree->Remove(5);

  enterToContinue();

  tree->LevelOrderDump(std::cout);
  std::cout << "Deleting - One Subtree[left](3)\n";
  tree->Remove(3);

  enterToContinue();

  tree->LevelOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing IntersectionWith - Should contain 2 4 6 7 9\n";

  enterToContinue();

  std::shared_ptr<BinarySearchTree<int>> the_intersection = tree->IntersectionWith(tree2);
  the_intersection->PreOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing UnionWith - Should contain 1->10\n";

  std::shared_ptr<BinarySearchTree<int>> the_union = the_intersection->UnionWith(tree2);
  the_union->PreOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Testing DifferenceOf - Should contain 1 3 5 8 10\n";

  std::shared_ptr<BinarySearchTree<int>> the_diff = the_intersection->DifferenceOf(the_union);
  the_diff->PreOrderDump(std::cout);
  std::cout << "How does it look?\n";

  enterToContinue();

  std::cout << "Making new BST with: ";
  std::shared_ptr<BinarySearchTree<int>> bst = std::make_shared<BinarySearchTree<int>>();
  int b[5] = { 5, 7, 6, 8, 9 };
  for (int i = 0; i < 5; i++) {
    std::cout << b[i] << ' ';
    bst->Insert(b[i]);
  }
  std::cout << '\n';

  std::cout << "Tree2 By Level:\n";
  tree2->LevelOrderDump(std::cout);
  std::cout << '\n';

  std::cout << "Testing IsBSubStructureOfA: ";
  if (bst->IsBSubstructureOfA(tree2->GetRoot(), bst->GetRoot()))
    std::cout << "Passed\n";
  else
    std::cout << "Failed\n";

  enterToContinue();

  std::cout << "Testing TwoTheSame with:\n";
  the_intersection->InOrderDump(std::cout);
  std::cout << '\n';
  the_diff->InOrderDump(std::cout);
  std::cout << '\n';

  if (!the_intersection->TwoTheSame(the_intersection->GetRoot(), the_diff->GetRoot()))
    std::cout << "Passed - these two trees do not have any common values\n";
  else
    std::cout << "Failed - Uh-oh, two same values were detected, but they shouldn't have any in common\n";

  enterToContinue();

  std::cout << "Testing TwoTheSame with:\n";
  bst->InOrderDump(std::cout);
  std::cout << '\n';
  the_intersection->InOrderDump(std::cout);
  std::cout << '\n';

  if (bst->TwoTheSame(bst->GetRoot(), the_intersection->GetRoot()))
    std::cout << "Passed - these two trees share a common value\n";
  else
    std::cout << "Failed - Uh-oh, two same values not detected, but it should've been\n";

  std::cout << "\nEnd of BST tests\n";

  return 0;
}
