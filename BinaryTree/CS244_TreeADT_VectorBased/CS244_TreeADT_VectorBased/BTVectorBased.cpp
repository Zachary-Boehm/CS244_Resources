//Dr. Saleh M. Alnaeli
// CS244_TreeADT_VectorBased.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "BTVectorBased.h"
using namespace std;
int main(){
	//std::vector<int> myvector;

	// set some initial content:
	/*for (int i = 1; i<10; i++) 
		myvector.push_back(i);
	myvector.resize(20);
	for (int i = 0; i<myvector.size (); i++)
		cout<<myvector[i];
*/
	cout << endl;

	VectorTree<string> myTree ;
	
	myTree.addLast("My Book");
	myTree.addLast("Chapter 1");
	myTree.addLast("Chapter 2");
	myTree.addLast("section 1.1.");
	myTree.addLast("section 1.2.");
	myTree.addLast("section 2.1.");
	myTree.addLast("section 2.2.");
	myTree.addLast("section 1.1.1");
	myTree.addLast("section 1.1.2");
	VectorTree<string>::Position p=myTree.last();
	myTree.addAsleft(p, "Section 1.1.2.1");
	p = myTree.pos(9);
	myTree.addAsright(p, "Section 1.1.2.2");

	p = myTree.pos(9);
	cout<<"left is " <<*myTree.left(p)<<endl;
	cout << "right is " << *myTree.right(p)<<endl;

	int i = 1;
	int j = 0;
	for (VectorTree<string>::Position p1 = myTree.root(); p1 <= myTree.last(); ++p1)		
		if (*p1 != "" )
			cout << *p1<<"   ";
		else
		cout << " emptyPos    ";

	cout << endl;

	myTree.preOrder(myTree.root());
	cout << endl;

	myTree.postOrder(myTree.root());
	cout << endl;

	myTree.inOrder(myTree.root());
	cout << endl;
	//myTree.
	myTree.printTreeLevel(myTree.root());
	cout << endl;

	
	return 0;
}