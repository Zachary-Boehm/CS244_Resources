//Header:
#pragma once
#ifndef BinaryTree_H
#define BinaryTree_H
#include <list> 
using std::list;

typedef int Elem; // base element type 
class LinkedBinaryTree { 
protected: // insert Node declaration here... CS 244students, you can use a class if not hapy with struct
 struct Node { // a node of the tree 
  Elem elt; // element value 
  Node* par; // parent.. NOTE: some implementation has no parent reference
  Node* left; // left child 
  Node* right; // right child 
  Node() : elt(), par(NULL), left(NULL), right(NULL) { } // constructor 
 }; 
public: // insert Position declaration here... 
 class Position { // position in the tree 
 private: Node* v; // pointer to the node 
 public:
  Position(Node* newV = NULL) : v(newV) { } // constructor 
  Elem& operator*() // get element 
  {
   return v->elt;
  }
  Position left() const // get left child 
  {
   return Position(v->left);
  }
  Position right() const // get right child 
  {
   return Position(v->right);
  }
  Position parent() const // get parent 
  {
   return Position(v->par);
  }
  bool isRoot() const // root of the tree? 
  {
   return v->par == NULL;
  }
  bool isExternal() const // an external node? 
  {
   return (v->left == NULL && v->right == NULL);
  }
  // Returns the Position of p's sibling (or null if no sibling exists).
  Position sibling() {   
   if (v->par == NULL) return NULL;  // p must be the root
   if (v->par->left == v)  //Am I a left child of my parent? the print the right chld of my parent :)
    return Position(v->par->right);
   else
    return Position(v->par->left); //I am the right child of my parent :)
  }
  friend class LinkedBinaryTree; // give tree access 
 }; 
  typedef std::list<Position> PositionList; // list of positions 
public: 
 LinkedBinaryTree(); // constructor 
  int size() const; // number of nodes 
  bool empty() const; // is tree empty? 
  Position root() const; // get the root 
  PositionList positions() const; // list of all tree nodes 
  void addRoot(); // add root to empty tree 
  void expandExternal(const Position& p); // expand external node. Probably to add children
  Position addRight(const Position& p, Elem e);
  Position addLeft(const Position& p, Elem e);
  //Position removeAboveExternal(const Position& p); // remove p and parent 
               // housekeeping functions omitted... 
  int depth(const Position& p);
  int height(const Position& p);

protected: // local utilities 
 void preorder(Node* v, PositionList& pl) const; // preorder utility 
 void inorder(Node* v, PositionList& pl) const; // preorder utility 
private: 
 Node* _root; // pointer to the root 
   int n; // number of nodes 
}; 
 //implementations
 LinkedBinaryTree::LinkedBinaryTree() // constructor 
  : _root(NULL), n(0) { }
 int LinkedBinaryTree::size() const // number of nodes 
 { return n; } 
 bool LinkedBinaryTree::empty() const // is tree empty? 
 { return size() == 0; } 
 LinkedBinaryTree::Position LinkedBinaryTree::root() const // get the root 
 { return Position(_root); }
 void LinkedBinaryTree::addRoot() // add root to empty tree 
 { _root = new Node; n = 1; } 

  int LinkedBinaryTree::depth(const Position& p) {
  if (p.isRoot()) 
   return 0; 
  else 
   return 1 + depth(p.parent()); 
 }

  // Returns the height of the subtree rooted at Position p.
   int LinkedBinaryTree::height(const Position& p) {
   int h = 0;   // base case if p is external 
   //that is, if both p.left().v and p.right().v are NULL then return h. 
   //In which case the coming if statements will not execute so h stays 0 for the base case.
   //for (Position<E> c : children(p)) 

   if (p.left().v !=  NULL)
    h =  h > (1 + height(p.left())) ? h: (1 + height(p.left()));
   if (p.right().v != NULL)
    h = h > (1 + height(p.right())) ? h : (1 + height(p.right()));

   return h; 
   } 

 void LinkedBinaryTree::expandExternal(const Position& p) // expand external node
 { Node* v = p.v; // p’s node 
 v->left = new Node; // add a new left child 
 v->left->par = v; // v is its parent 
 v->right = new Node; // and a new right child 
 v->right->par = v; // v is its parent 
 n += 2; // two more nodes 
 }

 // Creates a new right child of Position p storing element e; returns its Position.
 LinkedBinaryTree::Position 
  LinkedBinaryTree::addRight(const Position& p, Elem e) 
 {
  Node* v = p.v; // p’s node 
  if (v->right == NULL) {
   v->right = new Node; // and a new right child 
   v->right->par = v; // v is its parent 
   n++; //one more node 
  }
  Position rightP=Position(v->right);
  *rightP = e;
  return rightP;
 }

 // Creates a new left child of Position p storing element e; returns its Position. Updates the data if already existing
 LinkedBinaryTree::Position
  LinkedBinaryTree::addLeft(const Position& p, Elem e)
 {
  Node* v = p.v; // p’s node 
  if (v->left == NULL) {
   v->left = new Node; // and a new left child 
   v->left->par = v; // v is its parent 
   n++; //one more node 
  }
  Position leftP = Position(v->left);
  *leftP = e;
  return leftP;
 }

 

 LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const { // list of all nodes 
 PositionList pl; 
 preorder( _root, pl); // preorder traversal 
 //inorder(_root, pl); // inorder traversal 
 return PositionList(pl); // return resulting list 
 } 
 // preorder traversal 
 void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const { 
  pl.push_back(Position(v)); // add this node 
  if (v->left != NULL) // traverse left subtree 
   preorder(v->left, pl);
  if (v->right != NULL) // traverse right subtree 
   preorder(v->right, pl);
 }

 // preorder traversal 
 void LinkedBinaryTree::inorder(Node* v, PositionList& pl) const {
  
  if (v->left != NULL) // traverse left subtree 
   inorder(v->left, pl);

  pl.push_back(Position(v)); // add this node 

  if (v->right != NULL) // traverse right subtree 
   inorder(v->right, pl);
 }

 ////useful for implementation with sentinel nodes
 //LinkedBinaryTree::Position // remove p and parent 
 // LinkedBinaryTree::removeAboveExternal(const Position& p) {
 // Node* w = p.v; Node* v = w->par; // get p’s node and parent
 // Node* sib = (w == v->left ? v->right : v->left);
 // if (v == _root) { // child of root? 
 //  _root = sib; // ...make sibling root 
 //  sib->par = NULL;
 // }
 // else {
 //  Node* gpar = v->par; // w’s grandparent 
 //  if (v == gpar->left)
 //   gpar->left = sib; // replace parent by sib 
 //  else gpar->right = sib; sib->par = gpar;
 // }
 // delete w; delete v; // delete removed nodes 
 // n -= 2; // two fewer nodes 
 // return Position(sib);
 //}

#endif



// //Appliation (main)
// #include <iostream>     
// #include "binaryTreeClass.h"
// #include <list>
// using namespace std;

// int main() {

//  LinkedBinaryTree BTreeObj;
//  BTreeObj.addRoot();
//  LinkedBinaryTree::Position iter = BTreeObj.root();
//  *iter = 100;
//  if (iter.isRoot()) cout << "It is a root" << endl;
//  BTreeObj.expandExternal(iter);

//  *iter.left() = 75;
//  *iter.right() = 150;
//  cout << *iter<<"   "<< *iter.left() << "  " << *iter.right() << endl;

//  BTreeObj.expandExternal(iter.left());
 
 
//  *iter.left().left() = 25;
//  *iter.left().right() = 85;

//    // BTreeObj.expandExternal(iter.right());
//    /*
//    *iter.right().left() = 125;
//    *iter.right().right() = 175
//    ;*/
//  LinkedBinaryTree::Position Leftiter = BTreeObj.addLeft(iter.right(), 125);
//  LinkedBinaryTree::Position Rightiter = BTreeObj.addRight(iter.right(), 175);

 
 
//  //    100     level 0
//  //  75    150   level 1
//  // 25  85  125  175  level 2
//  list<LinkedBinaryTree::Position> L(BTreeObj.positions());
//  cout << "preorder print" << endl;
//  for (list<LinkedBinaryTree::Position>::iterator iter = L.begin(); iter != L.end(); ++iter) {
//   cout << (*(*iter)) << " ";  // iterator to the current item used for print the item stored by the current iterator.
//  }
//  cout << endl;
//  cout << BTreeObj.depth(iter) << endl;
//  cout << BTreeObj.depth(iter.right().right()) << endl;

//  cout << BTreeObj.height(iter) << endl;
//  cout << BTreeObj.height(iter.right().right()) << endl;

 

//  cout<<*iter.right().sibling()<<endl;
//  cout << *iter.left().sibling() << endl;
//   cout << endl;
//  return 0;
// }// end main
