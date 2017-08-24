#include "BinarySearchTree.hpp"

#include <iostream>
#include <fstream>

int main( int argc, char *argv[] ) {

    std::cout << "BinarySearchTree testing begins.\n\n";



    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "BinarySearchTree testing ends.\n";
        return 1;
    }

    std::cout << "Testing default constructor: ";
    BinarySearchTree *tree = new BinSearchTree();
    BinarySearchTree *tree2 = new BinSearchTree();
    std::cout << "Passed\n";
    std::vector<int> treeValues;

    std::fstream infile;
    infile.open(argv[1]);

    if(infile.is_open()) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "BinarySearchTree testing ends.\n";
        return 1;
    }

    std::cout << "Testing Contains(Recursive/Iterative), Insert, GetSize...\n "

    int v;
    while(infile >> v ) {
        if(!tree->ContainsRecursive(v))  {
            tree->Insert(v);
            tree2->Insert(v);
            treeValues.push_back(v);
        }
    }

    if (tree->GetSize() == 10)
      std::cout << "GetSize: Passed\n";

    bool passed = true;
    for (int i = 1; i <= 10; i++)
      if (!tree->ContainsRecursive(i))
        passed = false;

    if (passed)
      std::cout << "ContainsRecursive: Passed\n";

    passed = true;
    for (int i = 1; i <= 10; i++)
      if (!tree->ContainsIterative(i))
        passed = false;

    if (passed)
      std::cout << "ContainsIterative: Passed\n";

    std::cout << "* If all passed so far - Insert looks good\n";

    std::cout << "Testing LevelOrderDump - Should be 5 3 7 2 4 6 8 1 9 10\n";
    tree->LevelOrderDump(cout);
    std::cout << "How does it look?\n";

    std::cout << "Testing MaxDepth(Recursive/Iterative) => 5\n";
    if (tree->MaxDepthRecursive() != 5)
      std::cout << "MaxDepthRecursive: Failed";
    else
      std::cout << "MaxDepthRecursive: Passed";
    if (tree->MaxDepthIterative() != 5)
      std::cout << "MaxDepthRecursive: Failed";
    else
      std::cout << "MaxDepthRecursive: Passed";

    std::cout << "Testing DumpValuesAtLevel(Recursive/Iterative) - Should be same as LevelOrderDump\n";
    std::cout << "Recursive:\n";
    for (int i = 1; i <= tree->MaxDepthIterative(); i++)
      tree->DumpValuesAtLevelRecursive(cout, i);
    std::cout << "Iterative:\n";
    for (int i = 1; i <= tree->MaxDepthIterative(); i++)
      tree->DumpValuesAtLevelIterative(cout, i);
    std::cout << "How does it look?\n";

    std::cout << "Testing InOrderDump - Should be 1->10\n";
    tree->InOrderDump(cout);
    std::cout << "How does it look?\n";

    std::cout << "Testing PreOrderDump - Should be 5 3 2 1 4 7 6 8 9 10\n";
    tree->PreOrderDump();
    std::cout << "How does it look?\n";

    std::cout << "Testing PostOrderDump - Should be 1 2 4 36 7 8 9 10 5\n";
    tree->PostOrderDump();
    std::cout << "How does it look\n";

    std::cout << "Testing KthSmallest - Should be 10->1\n";
    for (int i = 1; i <= 10; i++)
      cout << tree->KthSmallest(i) << '\n';

    std::cout << "Testing HasRoomToLeafSum for 11 12 18 39 (true) 7 20 (false): ";
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
            std::cout << "Uh-oh []" << a[i] << "] a false number is true\n";
          }
      }
    }
    if (passed)
      std::cout << "HasRootToLeafSum: Passed\n";
    else
      std::cout << "HasRootToLeafSum: Failed\n";

    std::cout << "Testing Remove:\nDeleting Leaves(1, 10)\n";
    std::cout << "Before: ";
    tree->LevelOrderDump();
    tree->Remove(1);
    tree->Remove(10);
    std::cout << "After: ";
    tree->LevelOrderDump();
    std::cout << "Deleting - One Subtree[right](8)\n";
    tree->>Remove(8);
    tree->LevelOrderDump();
    std::cout << "Deleting - TwoSubtrees(5 root)\n";
    tree->Remove(5);
    tree->LevelOrderDump();
    std::cout < "Deleting - One Subtree[left](3)\n";
    tree->Remove(3);
    tree->LevelOrderDump();
    std::cout << "How does it look?\n";

    std::cout << "Testing IntersectionWith - Should be 2 4 6 7 9\n";
    BinarySearchTree* the_intersection = tree->IntersectionWith(tree2);
    the_intersection->PreOrderDump(cout);
    std::cout << "How does it look?\n";

    std::cout << "Testing UnionWith - Should be 1->10\n";
    BinarySearchTree* the_union = the_intersection->UnionWith(tree2);
    the_union->PreOrderDump(cout);
    std::cout << "How does it look?\n";

    std::cout << "Testing DifferenceOf - Should be 1 3 5 8 10\n";
    BinarySearchTree* the_diff = the_union->DifferenceOf(the_intersection);
    the_diff->PreOrderDump(cout);
    std::cout << "How does it look?\n";


    BinarySearchTree* bst = new BinarySearchTree();
    int b[5] = { 5, 7, 6, 8, 9 };
    for (int i = 0; i < 5; i++)
      bst->Insert(b[i]);

    std::cout << "Testing IsBSubStructureOfA: ";
    if (bst->IsBSubstructureOfA(tree2, bst->GetRoot()))
      std::cout << "Passed\n";
    else
      std::cout << "Failed\n";

    std::cout << "Testing TwoTheSame: ";
    if (!the_intersection->TwoTheSame(the_intersection->GetRoot(), the_diff->GetRoot()))
      std::cout << "Passed - these two trees do not have any common values\n";
    else
      std::cout << "Failed - Uh-oh, two same values were detected, but they shouldn't have any in common\n";

    if (bst->TwoTheSame(bst->GetRoot(), the_intersection->GetRoot()))
      std::cout << "Passed - these two trees share a common value\n";
    else
      std::cout << "Failed - Uh-oh, two same values not detected, but it should've been\n";



    std::cout << "\nEnd of BST tests\n"

  return 0;
}
