#include<iostream>
#include<cassert>
#include"Vector.h"

using namespace std;

template <class T>
class PriorityQueue {
private:
	V<T> container;
public:
	T DeleteMin();
	void Insert(const T&a);
	int Getsize() {return container.NumberOfItems();}
	T& operator[](int);

};


template <class T>
T PriorityQueue<T>::DeleteMin() {
	assert(container.NumberOfItems() > 0);
	T minElement = container[0];

	//move the last element to the begining
	container[0] = container[container.NumberOfItems() - 1];
	int cur = 0;
	int lastPos = container.NumberOfItems() - 1;

	while ( (2*cur + 1 < lastPos) && (container[cur] > 
	                container[2*cur + 1] || container[cur] > container[2*cur + 2]) ) {
         T tempItem = container[cur];
         if ( container[2*cur + 1] > container[2*cur + 2] ) {
           container[cur] = container[2*cur + 2];
           container[2*cur + 2] = tempItem;
           cur = 2*cur + 2;
       }
          else {
           container[cur] = container[2*cur + 1];
           container[2*cur + 1] = tempItem;
           cur = 2*cur + 1;
       }
	}
	container.RemoveLast();
	return minElement;

}//End function DeleteMax


template <class T>
void PriorityQueue<T>::Insert(const T &a) {
	container.AddLast(a);
	T temp;
	int cur = container.NumberOfItems() - 1; // cur is the index of current position
	while ( (cur > 0) && (container[cur] < container[(cur - 1)/2]) ) {
		//push element up the tree by swapping it with its parent of smaller priority
		temp = container[cur];
		container[cur] = container[(cur - 1)/2];
		container[(cur - 1)/2] = temp;
		cur = (cur - 1)/2;
	}
}

template <class T>
T& PriorityQueue<T>::operator[](int index) {
	assert(index < container.NumberOfItems() && index >= 0);
	return container[index];
}

