// CS244_TreeADTLinkedIterator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Appliation (main)
#include <iostream>     
#include "binaryTreeClass.h"
#include <list>
using namespace std;

int main() {

    LinkedBinaryTree BTreeObj;
    BTreeObj.addRoot();
    LinkedBinaryTree::Position iter = BTreeObj.root();
    *iter = 100;
    if (iter.isRoot()) cout << "It is a root" << endl;
    BTreeObj.expandExternal(iter);

    *iter.left() = 75;
    *iter.right() = 150;
    cout << *iter << "   " << *iter.left() << "  " << *iter.right() << endl;

    BTreeObj.expandExternal(iter.left());


    *iter.left().left() = 25;
    *iter.left().right() = 85;

    // BTreeObj.expandExternal(iter.right());
    /*
    *iter.right().left() = 125;
    *iter.right().right() = 175
    ;*/
    LinkedBinaryTree::Position Leftiter = BTreeObj.addLeft(iter.right(), 125);
    LinkedBinaryTree::Position Rightiter = BTreeObj.addRight(iter.right(), 175);



    //    100     level 0
    //  75    150   level 1
    // 25  85  125  175  level 2
    list<LinkedBinaryTree::Position> L(BTreeObj.positions());
    cout << "preorder print" << endl;
    for (list<LinkedBinaryTree::Position>::iterator iter = L.begin(); iter != L.end(); ++iter) {
        cout << (*(*iter)) << " ";  // iterator to the current item used for print the item stored by the current iterator.
    }
    cout << endl;
    cout << BTreeObj.depth(iter) << endl;
    cout << BTreeObj.depth(iter.right().right()) << endl;

    cout << BTreeObj.height(iter) << endl;
    cout << BTreeObj.height(iter.right().right()) << endl;



    cout << *iter.right().sibling() << endl;
    cout << *iter.left().sibling() << endl;
    cout << endl;
    return 0;
}// end main