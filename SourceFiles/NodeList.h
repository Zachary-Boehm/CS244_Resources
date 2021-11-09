#pragma once
//File name: "NodeListClass_H.h"
//By Dr. Alnaeli, UW-Stout
// Portions of code are adopted from the course text
#ifndef NODELIST
#define NODELIST

#include <iostream>
using namespace std;
//Class NodeList is a Doubly Linked List implementation based with Iterator.
//Classes Node and Iterators are nested and part of the NodeList class
//Here we are trying to implement something similar to the std list class. 
template <class Elem>
class NodeList {        // node-based list
private:
//no need for template prefix here. will be picked from the NodeList Class
//members are public by default inside the Node class. However, it is a private member of NodeList class
 class Node { // a node of the list
 public:
  Elem elem;        // element value
  Node* prev;        // previous in list
  Node* next;        // next in list
 };
public:
 // insert Iterator declaration here...
 //template <class Elem>
 class Iterator {       // an iterator for the list
 public:
  Elem& operator*();      // reference to the element (dereference operator)
  bool operator==(const Iterator& p) const; // compare positions
  bool operator!=(const Iterator& p) const;
  Iterator& operator++(); //++p pre-increament operator // move to next position
  /*-----------------------------------------------------------------*/
  Iterator operator++(Elem) // p++ post increment operator overloading
  {
   Iterator temp = *this; // save the original value
   ++*this;  //increment
   return temp; // return the older value
  }
  /*-----------------------------------------------------------------*/
  Iterator& operator--();     //--p, pre decrement move to previous position
  friend class NodeList<Elem>;   // give NodeList access to Iterator private members
 private:
  Node* v;        // pointer to the node
  Iterator(Node* u); // private constructor. Will only created from the NodeList. Created from node
 }; //end of class iterator
public:
 NodeList();         // default constructor
 int size() const;       // list size
 bool empty() const;       // is the list empty?
 Iterator begin() const;      // beginning position
 Iterator end() const;      // (just beyond) last position
 void insertFront(const Elem& e);   // insert at front
 void insertBack(const Elem& e);    // insert at rear
 void insert(const Iterator& p, const Elem& e); // insert e before p
 void eraseFront();       // remove first
 void eraseBack();       // remove last
 void erase(const Iterator& p);    // remove p
            // housekeeping functions omitted...
private:          // data members
 int     n;         // number of items
 Node*   header;        // head-of-list sentinel
 Node*   trailer;       // tail-of-list sentinel
};  //class NodeList 

template <class Elem>
  NodeList<Elem>::Iterator::Iterator(Node* u)   // constructor from Node*
{
 v = u;
}

template <class Elem>
Elem& NodeList<Elem>::Iterator::operator*()   // reference to the element
{
 return v->elem;
}

// compare positions
template <class Elem>
bool NodeList<Elem>::Iterator::operator==(const Iterator& p) const
{
 return v == p.v;
}

template <class Elem>
bool NodeList<Elem>::Iterator::operator!=(const Iterator& p) const
{
 return v != p.v;
}

// move to previous position
template <class Elem>
typename NodeList<Elem>::Iterator& NodeList<Elem>::Iterator::operator--()
{
 v = v->prev; return *this;
}

template <class Elem>
typename  NodeList<Elem>::Iterator& NodeList<Elem>::Iterator::operator++()
{
 v = v->next; return *this;
}

template <class Elem>
NodeList<Elem>::NodeList() {       // constructor
 n = 0;          // initially empty
 header = new Node;       // create sentinels
 trailer = new Node;
 header->next = trailer;      // have them point to each other
 trailer->prev = header;
}

template <class Elem>
int NodeList<Elem>::size() const       // list size
{
 return n;
}

template <class Elem>
bool NodeList<Elem>::empty() const      // is the list empty?
{
 return (n == 0);
}

template <class Elem>
typename NodeList<Elem>::Iterator NodeList<Elem>::begin() const  // begin position is first item
{
 return Iterator(header->next);
}

template <class Elem>
typename  NodeList<Elem>::Iterator NodeList<Elem>::end() const  // end position is just beyond last
{
 return Iterator(trailer);
}

template <class Elem>
void NodeList<Elem>::erase(const Iterator& p) {  // remove p
 Node* v = p.v;        // node to remove
 Node* w = v->next;       // successor
 Node* u = v->prev;       // predecessor
 u->next = w;  w->prev = u;     // unlink p   , link out p
 delete v;         // delete this node
 n--;          // one fewer element
}

template <class Elem>
void NodeList<Elem>::eraseFront()      // remove first
{
 erase(begin());
}
template <class Elem>
void NodeList<Elem>::eraseBack()      // remove last
{
 erase(--end());
}
template <class Elem>
void NodeList<Elem>::insert(const typename NodeList<Elem>::Iterator& p, const Elem& e) {
 Node* w = p.v;        // p's node
 Node* u = w->prev;       // p's predecessor
 Node* v = new Node;       // new node to insert
 v->elem = e;
 v->next = w;  w->prev = v;     // link in v before w
 v->prev = u;  u->next = v;     // link in v after u
 n++;
}
template <class Elem>
void NodeList<Elem>::insertFront(const Elem& e)  // insert at front
{
 insert(begin(), e);
}

template <class Elem>
void NodeList<Elem>::insertBack(const Elem& e)  // insert at rear
{
 insert(end(), e);
}

#endif

