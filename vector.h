#include<string>
#include<cassert>

using namespace std;

template <class T>
class V {
public:
	
	V(int capacity = 10);
	~V();
	bool IsEmpty() const;
	int NumberOfItems() const;
	void Resize(int);
	void AddLast(const T&);
	T& operator[](int);
	void RemoveLast();

private:

	T *array;
	int number_of_items;
	int size;
};

template <class T>
V<T>::V(int capacity) {
	assert (capacity > 0);
	array = new T[capacity];
	size = capacity;
	number_of_items = 0;
}

template <class T>
bool V<T>::IsEmpty() const {
	return (number_of_items == 0);
}

template <class T>
int V<T>::NumberOfItems() const {
	return number_of_items;
}

template <class T>
void V<T>::AddLast(const T &newItem)  {
	if (number_of_items == size)
		Resize(2 * size);
	array[number_of_items++] = newItem;
}


template <class T>
void V<T>::Resize(int capacity) {
	T* newArray = new T[capacity];
	int saveNumberOfItems = number_of_items;
	if (number_of_items > capacity)
	saveNumberOfItems = capacity;
	for (int i = 0; i < saveNumberOfItems; i++)
		newArray[i] = array[i];
	delete [] array;
	array = newArray;
	number_of_items = saveNumberOfItems;
	size = capacity;
}


template <class T>
T& V<T>::operator[](int index) {
	assert(index < number_of_items && index >= 0);
	return array[index];
}

template <class T>
void V<T>::RemoveLast() {
	assert(number_of_items > 0);
	--number_of_items;
}

template <class T> 
V<T>::~V() {
	delete [] array;
}
