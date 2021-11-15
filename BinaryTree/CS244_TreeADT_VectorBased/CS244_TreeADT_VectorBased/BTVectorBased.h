//Dr. Saleh M. Alnaeli
#ifndef BinrayTreeVector
#define BinrayTreeVector
#include <vector>
#include <iostream>

using namespace std;
template <typename E>
class VectorTree {
public:					// publicly accessible types
	typedef typename std::vector<E>::iterator Position; // a position in the tree
private:					// member data
	std::vector<E> V;				// tree contents
protected:					// protected utility functions
	//Position pos(int i)				// map an index to a position
	//{
	//	return V.begin() + i;
	//}
	int idx(const Position& p) const		// map a position to an index
	{
		return p - V.begin();
	}

public:					// publicly accessible types
	//typedef typename std::vector<E>::iterator Position; // a position in the tree
	VectorTree() : V(1) {}		// constructor
	int size() const				{ return V.size() - 1; }
	Position left(const Position& p)		{ return pos(2 * idx(p)); }
	Position right(const Position& p)		{ return pos(2 * idx(p) + 1); }
	Position parent(const Position& p)		{ return pos(idx(p) / 2); }
	bool hasLeft(const Position& p) const	{ return 2 * idx(p) <= size(); }
	bool hasRight(const Position& p) const 	{ return 2 * idx(p) + 1 <= size(); }
	bool isRoot(const Position& p) const	{ return idx(p) == 1; }
	Position root()				{ return pos(1); }
	Position last()				{ return pos(size()); }
	void addLast(const E& e)			{ V.push_back(e); }
	void removeLast()				{ V.pop_back(); }

	Position pos(int i)				// map an index to a position
	{
		return V.begin() + i;
	}

	void swap(const Position& p, const Position& q)
	{
		E e = *q; *q = *p; *p = e;
	}

	void preOrder(const Position& p)
	{
		cout <<endl<< *p<<"    ";
		if (hasLeft(p)){
			Position leftChild = left(p);
			preOrder(leftChild);
		}
		if (hasRight(p)){  // if p has right subtree [0, n]
			Position rightChild = right(p);
			preOrder(rightChild);
		}
	}

	void postOrder(const Position& p)
	{	
		if (hasLeft(p)){
			Position leftChild = left(p);
			postOrder(leftChild);
		}
		if (hasRight(p)){
			Position rightChild = right(p);
			postOrder(rightChild);
		}
		cout << endl << *p << "    ";
	}


	void inOrder(const Position& p)
	{
		if (hasLeft(p)){
			Position leftChild = left(p);
			inOrder(leftChild);
		}
		cout << endl << *p << "    ";
		if (hasRight(p)){
			Position rightChild = right(p);
			inOrder(rightChild);
		}
	}

	void addAsleft(const Position& p, const E& e)
	{
		int newPosIndx = (2 * idx(p));
		if (V.size() <= newPosIndx)
			V.resize(newPosIndx + 1);
		//E tmp = V[newPosIndx];
		V[newPosIndx] = e;
		//return tmp;
	}

	void addAsright(const Position& p, const E& e)
	{
		int newPosIndx = (2 * idx(p) + 1);
		if (V.size() <= newPosIndx)
			V.resize(newPosIndx + 1);
		V[newPosIndx] = e;
		//V[2 * idx(p) + 1]=e;
	}

void printTreeLevel(const Position& p){
		//try to print the tree by level:
		int level = 0; // level is equal to the height of the nodes in that level
		int ite = 1; // iteration number
			for (Position p = root(); p <= last(); ++p){
				cout << *p << "    ";
				int intP = pow(2, level);
				if (ite == intP){
					cout << endl;
					level ++;
					ite = 0;
				}
				ite++;
			}	
	}



	/*				*
				*       *
			*     *   *   *
		*    *  *  * * * * * */



////0   1xBook   2xCh1   3xCh2   4xSec1.1   5xSec1.2    6xsec2.1     7xsec2.2  " "  ""  ""   ""   ""   ""
//ins v =7 then indx v.leftchild =14 
////Insert sech2.2.1 in a proper place in the tree.
//loop indx(v) to(v.child-1 ==13)
//pushback(sech2.2.1)
//V.resize(13) 

};

#endif