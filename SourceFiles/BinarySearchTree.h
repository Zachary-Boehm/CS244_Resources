

// BinarySearchTreeCS442_Fall2020Alnaeli.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Binary Search Tree ADT Implementation with Templateand Iterators
//Dear CS 244 Students,
//Note: Please never share it with the public.
//Find attached Binary Search Tree ADT Implementation with Templateand Iterators.It is very clean implementation.
//Please reviewand run the code before Tuesday.I will explain it all.
//You need to create a new projectand create two files, a header file(BinarySearchTreeTemplateIter.h) and application file for the main method.
// The header file: BinarySearchTreeTemplateIter.h
//Important Notes: 
//Note 0: some parts of the code are taken from different resources including textbooks.  (e.g., Data Structures and Algorithms in C++ Second Edition by
//Michael T.Goodrich Department of Computer Science University of California, Irvine
//Roberto Tamassia Department of Computer Science Brown University
//David M.Mount Department of Computer Science Universityof Maryland
//Most of the methods and the internal structure have benn changed and implemented in a better way
//1:By all means, this is an educational project that was developed by Dr. Alnaeli for the CPS 265 Class and is not written to be used by any other parties.
//2:Some ideas and interfaces were either taken or enhanced from/by the course textbook 
//3: This work is protected under the compyrights regulations.
//4:Things to consider and take to the account when studying this code:
//1: The first super Parent is used as a sentinel node and so are the deepest external nodes
//Reason: simplifying the implementation of update methods and iterator's methods e.g., end()
//2:Only internal nodes are used to hold data and information.
//3:Iterator Begin method returns the first node expected to be visited by inorder traversal algorith
//4:Iterator end method returns an iterator that points to the sentinel root node
//5:method size returns number of the nodes that currently hold data (internals).
//6: if you have any question please contact me via Piazza, Skype for Business, or email.
//7: All sentinel nodes can be replaced with pointers to save memory if needed.
//8:If you prefer to have the methods implemented in a different file, move them to a file with extension template and make sure to included that file here
//9: For simplicity I didn't use exceptions.  I would strongly recommend creating your customized exception classes and use them for more robustness
#ifndef BinarySearchTree_H
#define BinarySearchTree_H
#include <list> 
#include <iostream>
#include <queue>
#include <string>
using std::list;
using std::cout;
using std::endl;
using std::queue;
using std::string;

template <class Elem>
class LinkedBinarySearchTree {
protected: // insert Node declaration here... 
 class Node { // a nested class Node of the tree 
 public:  // make fields public so that they are accessible by the iterator class
  Elem elt; // element value 
  Node* par; // parent.. NOTE: some implementation has no parent reference
  Node* left; // left child 
  Node* right; // right child 
  Node() : elt(), par(NULL), left(NULL), right(NULL) { } // constructor 
 };
public:
 class Iterator { // nested class Iterator declaration in the tree 
 private: Node* v; // pointer to the class Node 
 public:
  Iterator(Node* newV = NULL) : v(newV) { } // Iterator constructor 
  Elem& operator*() // get element 
  {
   return v->elt;
  }
  Iterator left() const // get left child 
  {
   return Iterator(v->left);
  }
  Iterator right() const // get right child 
  {
   return Iterator(v->right);
  }
  Iterator parent() const // get parent 
  {
   return Iterator(v->par);
  }
  bool isRoot() const // virtual root of the tree? sentinel node 
  {
   return v->par->par == NULL;
  }
  bool isExternal() const // an external node? 
  {
   return v->left == NULL && v->right == NULL;
  }

  Iterator sibling(); // Returns the Iterator of p's sibling (or null if no sibling exists).
  Iterator& operator++();// move to next node until sentinel node is riched
  bool operator==(const Iterator& p) const; // compare positions
  bool operator!=(const Iterator& p) const;
  friend class LinkedBinarySearchTree; // give tree access 
 };
 typedef std::list<Iterator> IteratorList; // list of Iterators 
 LinkedBinarySearchTree(); // constructor 
 int size() const; // number of nodes 
 bool empty() const; // is tree empty? 
 Iterator root() const; // get the root 
 IteratorList Iterators() const; // list of nodes 
 void addRoot(); // add root to empty tree 
 void expandExternal(const Iterator& p); // expand external node by creating children for it
 Iterator removeAboveExternal(const Iterator& p); // remove p, assuming that it is an external, and its parent 


 // iterator to ﬁrst entry. Remember: Inorder Traversal :) so the leftmost node in the tree
 Iterator begin();
 Iterator end(); //iterator to the sentinel super root
 int depth(const Iterator& p); // depth of node pointed by P
 int height(const Iterator& p); //height of node pointed by p
 //--Searching---
 Iterator finder(const Elem& k, const Iterator& itr);

 // find entry with key k
 Iterator find(const Elem& k);

 Iterator inserter(const Elem& k);
 Iterator insert(const Elem& k);

 //print number of all allocated nodes in the tree including the super root and its unused right child
 int getAllocatedNodeNumber() {
  return allocatedNodeNumber;
 }
 void levelWiseTravese();
 //deletion
 void erase(const Elem&);
 Iterator eraser(Iterator&);
 //the following methods are only for testing. I do not recommend using them
 Iterator addLeft(const Iterator& p, Elem e);
 Iterator addRight(const Iterator& p, Elem e);
 /////////////////
protected: // local utilities 
 void preorder(Node* v, IteratorList& pl) const; // preorder utility 
 void inorder(Node* v, IteratorList& pl) const; // preorder utility 
private:
 Node* _root; // pointer to the root 
 int n; // number of nodes 
 int allocatedNodeNumber;  // number of the dynamically allocated nodes including the sentinel nodes
}; ////// end of BST class body

//implementations
//Nested Iterator Class Methods:
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::Iterator::sibling() {
 if (v->par == NULL) return NULL;  // p must be the root
 if (v->par->left == v)
  return v->par->right;
 else
  return v->par->left;
}
//Binary Search Methods--------------------------------------------

template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::begin() {
 Iterator itr = root(); // start at virtual root 
 while (!itr.isExternal())
  itr = itr.left(); // ﬁnd leftmost node 
 return itr.parent(); //
}

template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::end() { return root().parent(); } //retruns an iterator to sentinel node

                      //compare Iterators
template <class Elem>
bool LinkedBinarySearchTree<Elem>::Iterator::operator==(const Iterator& p) const
{
 return v == p.v;
}

template <class Elem>
bool LinkedBinarySearchTree<Elem>::Iterator::operator!=(const Iterator& p) const
{
 return v != p.v;
}

template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator& LinkedBinarySearchTree<Elem>::Iterator::operator++() {
 Iterator p(v);
 Iterator w = p.right(); //v.right(); 
 if (!w.isExternal()) { // have right subtree? 
  do { p = w; w = w.left(); } // move down left chain 
  while (!w.isExternal());
 }
 else {
  w = p.parent(); // get parent 
  while (p == w.right()) // move up right chain 
  {
   p = w; w = w.parent();
  }
  v = w.v; // and ﬁrst link to left 
 }
 return *this;
}

//---------------------------------------------------------
template <class Elem>
LinkedBinarySearchTree<Elem>::LinkedBinarySearchTree() // constructor 
{
 _root = NULL;
 n = 0; // will be initialized with 1 after calling addRoot() 
 addRoot();


}
template <class Elem>
void LinkedBinarySearchTree<Elem>::addRoot() // add root to empty tree 
{
 if (!_root == NULL)
  cout << "Already has a root" << endl; // can throw an exception 
 else {
  _root = new Node;
  n = 1;
  allocatedNodeNumber += 1;
  expandExternal(Iterator(_root));
  expandExternal(Iterator(_root->left)); // this is to expand the virtual root node since it is goign to be used to hold a value, eventually
 }
}
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::root() const // get the root 
{
 return Iterator(_root->left);
}

template <class Elem>
int LinkedBinarySearchTree<Elem>::size() const // number of nodes 
{
 return n;
}

template <class Elem>
bool LinkedBinarySearchTree<Elem>::empty() const // is tree empty? 
{
 return size() == 0;
}

//BST----
//--Searching---
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::finder(const Elem& k, const Iterator& itr) {
 if (itr.isExternal()) return itr;   // value not found
 if (k < itr.v->elt) return finder(k, itr.left()); // search left subtree
 else if (itr.v->elt < k) return finder(k, itr.right()); // search right subtree
 else return itr;     // found it here
}

// find entry with key k
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::find(const Elem& k) {
 Iterator itr = finder(k, root());    // search from virtual root
 if (!itr.isExternal()) return itr;  // found it
 else {
  cout << "\nNOT FOUND FROM METHD find\n";
  return end();
 }     // didn't find it so return the root sentinel node
}
//---Insertion methods-----------------------
// insert utility
//Iterator inserter(const Iterator& p, const Elem& k);
//Iterator insert(const Elem& k);
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::inserter(const Elem& x) {
 Iterator p = finder(x, root());    // search from virtual root
 while (!p.isExternal())    // value already exists?
  p = finder(x, p.right());    // look further
 expandExternal(p);    // add new internal node
 p.v->elt = x;   // set entered new value. you can use : // *p = x;

 n++;      // one more entry
 return p;      // return insert position
}


template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::insert(const Elem& k)
{
 Iterator p = inserter(k);
 return Iterator(p);
}
//-----------------------
//---Erase-------------
// remove utility
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::eraser(Iterator& v) {
 Iterator p;
 if (v.left().isExternal()) p = v.left();  // remove from left
 else if (v.right().isExternal()) p = v.right(); // remove from right
 else {      // both internal?
  p = v.right();     // go to right subtree
  do { p = p.left(); } while (!p.isExternal()); // get leftmost node

  Iterator iterPart = p.parent();
  *v = *iterPart; // copy w's parent to v
 }
 n--;      // one less entry
 allocatedNodeNumber -= 1;// one allocted-node fewer
 return removeAboveExternal(p);   // remove w and parent
}

// remove value k
template <class Elem>
void LinkedBinarySearchTree<Elem>::erase(const Elem& k) {
 Iterator p = finder(k, root());    // search from virtual root
 if (p.isExternal())     // not found?
  cout << "Not Existing" << endl; //throw exception for a better implementation
 eraser(p);      // remove it
}

//--------------
template <class Elem>
int LinkedBinarySearchTree<Elem>::depth(const Iterator& p) {
 if (p.isRoot())
  return 0;
 else
  return 1 + depth(p.parent());
}

// Returns the height of the subtree rooted at Iterator p.
template <class Elem>
int LinkedBinarySearchTree<Elem>::height(const Iterator& p) {
 int h = 0;   // base case if p is external 
      //for (Iterator<E> c : children(p)) 
 if (p.left().v != NULL)
  h = h > (1 + height(p.left())) ? h : (1 + height(p.left()));
 if (p.right().v != NULL)
  h = h > (1 + height(p.right())) ? h : (1 + height(p.right()));
 return h;
}

//expands node pointed by p by creating children (R/L) for it.
template <class Elem>
void LinkedBinarySearchTree<Elem>::expandExternal(const Iterator& p)
{
 Node* v = p.v; // p’s node 
 v->left = new Node; // add a new left child 
 v->left->par = v; // v is its parent 
 v->right = new Node; // and a new right child 
 v->right->par = v; // v is its parent 
 allocatedNodeNumber += 2;
 //n += 2; // two more nodes externals will not be counted since they are just sentinel.
}


// remove p and parent 
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::removeAboveExternal(const Iterator& p) {
 Node* w = p.v; Node* v = w->par; // get p’s node and parent
 Node* sib = (w == v->left ? v->right : v->left);
 if (v == _root) { // child of root? 
  _root = sib; // ...make sibling root 
  sib->par = NULL;
 }
 else {
  Node* gpar = v->par; // w’s grandparent 
  if (v == gpar->left)
   gpar->left = sib; // replace parent by sib 
  else gpar->right = sib; sib->par = gpar;
 }
 delete w; delete v; // delete removed nodes 
      //n -= 1; // one fewer ... n -= 2; // two fewer nodes 
 allocatedNodeNumber -= 1;// one allocted-node fewer

 return Iterator(sib);
}

// list of iterator to all nodes 
template <class Elem>
typename LinkedBinarySearchTree<Elem>::IteratorList LinkedBinarySearchTree<Elem>::Iterators() const { // list of iterator to all nodes 
 IteratorList pl;
 inorder(_root->left, pl); // inorder traversal 
 return IteratorList(pl); // return resulting list 
}
// preorder traversal 
template <class Elem>
void LinkedBinarySearchTree<Elem>::preorder(Node* v, IteratorList& pl) const {
 pl.push_back(Iterator(v)); // add this node 
 if (v->left != NULL) // traverse left subtree 
  preorder(v->left, pl);
 if (v->right != NULL) // traverse right subtree 
  preorder(v->right, pl);
}

// Inorder traversal 
template <class Elem>
void LinkedBinarySearchTree<Elem>::inorder(Node* v, IteratorList& pl) const {

 if ((v->left != NULL) && (v->left != NULL)) // traverse left subtree if not external
  inorder(v->left, pl);

 if ((v->left != NULL) && (v->left != NULL)) // push the node if not external
  pl.push_back(Iterator(v)); // add this node to thelist since it is an internal node

 if ((v->right != NULL) && (v->right != NULL)) // traverse right subtree if not external
  inorder(v->right, pl);
}

//printing all data stored in the node in a levelwise manner
template <class Elem>
void LinkedBinarySearchTree<Elem>::levelWiseTravese() {
 queue <Iterator> myQueue;
 Iterator p;
 int preDepth = depth(_root->left);
 myQueue.push(_root->left); //Initialize myQueue to contain virtual root
 while (!myQueue.empty()) {  //while not empty do
  p = myQueue.front(); // p is the current oldest entry in the queue 
  myQueue.pop(); // remove from queue
  if (depth(p) != preDepth) { //if a new level, then start a new line
   preDepth = depth(p);  // update the level
   cout << endl;
  }
  cout << *p << "    ";     //print the data and some spaces ////perform the “visit” action for position p
          // add p’s children to the end of the queue for later visits if they are not externals 
  if (!p.left().isExternal())
   myQueue.push(p.left());
  if (!p.right().isExternal())
   myQueue.push(p.right());
 }

}
//testing methods. I do not recommend using them as BST ADT methods.
//Please use them very carefully:
// Creates a new right child of Iterator p storing element e; returns its Iterator.
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::addRight(const Iterator& p, Elem e)
{
 Node* v = p.v; // p’s node 
 if (v->right == NULL) {
  v->right = new Node; // and a new right child 
  v->right->par = v; // v is its parent 

 }
 n++; //one more node 
 Iterator rightP = Iterator(v->right);
 *rightP = e;
 expandExternal(rightP);
 return rightP;
}

// Creates a new left child of Iterator p storing element e; returns its Iterator. Updates the data if already existing
template <class Elem>
typename LinkedBinarySearchTree<Elem>::Iterator LinkedBinarySearchTree<Elem>::addLeft(const Iterator& p, Elem e)
{
 Node* v = p.v; // p’s node 
 if (v->left == NULL) {
  v->left = new Node; // and a new left child 
  v->left->par = v; // v is its parent 

 }
 n++; //one more node 
 Iterator leftP = Iterator(v->left);
 *leftP = e;
 expandExternal(leftP);
 return leftP;
}

#endif

