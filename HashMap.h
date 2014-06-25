#include<iostream>
#include<string>
#include<fstream>
using namespace std;

template<typename T>
class HashMap{

private:
	struct Node{
		string key;
		T val;
		Node *next;
		Node(string key, T value, Node *next) : key(key), val(value), next(next) {}
		~Node() {}
	};
	enum {Default_size = 16};
	Node** m_data;
	int m_size;
	int m_used;
	int m_limit;

private:
	int hash(string);
	int getUsed() const {return m_used;}
	void grow();

public:
	HashMap();
	HashMap(int);
	~HashMap();
	bool get(const string, const T&);
	void set(const string, const T&);
	void status() const;
	void printKey();
};

template<typename T>
int HashMap<T> :: hash(string key) {
	int len = key.length();
	int sum = 0;
	for(int i=0; i<len; i++)
		sum += key[i] - 'A';
	return sum % m_size;
}

template<typename T>
void HashMap<T> :: grow() {
	cout<<"have to regrow"<<endl;
	Node** ptr = m_data;
	m_used = 0;
	m_size *= 2; 
	m_limit = m_size;
	m_data = new Node* [m_size];
	for(int i=0; i<m_size; i++) 
		m_data[i] = NULL;
	for(int i=0; i<m_size/2; i++) {
		Node *temp = ptr[i];
		while(temp){
			set(temp->key, temp->val);
			temp = temp->next;
		}
	}
	delete [] ptr;
}

template<typename T>
HashMap<T> :: HashMap() {
	m_data = new Node* [Default_size];
	for(int i=0; i<Default_size; i++)
		m_data[i] = NULL;
	m_size = Default_size;
	m_used = 0;
	m_limit = m_size;
}

template<typename T>
HashMap<T> :: HashMap(int size) {
	m_data = new Node* [size];
	for(int i=0; i<size; i++)
		m_data[i] = NULL;
	m_size = size;
	m_used = 0;
	m_limit = m_size * 0.8;
}

template<typename T>
HashMap<T> :: ~HashMap() {
	delete [] m_data;
	m_data = NULL;
}

template<typename T>
bool HashMap<T> :: get(const string key, const T &value) {
	int index = hash(key);
	Node *temp = m_data[index];
	while(temp) {
		if(temp->key == key) {
			temp->val = value;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

template<typename T>
void HashMap<T> :: set(const string key, const T &value) {
	if(m_limit == m_used)
		grow();
	int index = hash(key);
	Node *temp = m_data[index];
	while(temp) {
		if(temp->key == key){
			temp->val = value;
			return;
		}
		temp = temp->next;
	}
	temp = m_data[index];
	if(temp == NULL)
		m_used++;
    Node *ptr = new Node(key, value, temp);
	m_data[index] = ptr;
}

template<typename T>
void HashMap<T> :: status() const {
	const int n = 11;
	int hist[n] = {0};
	for(int i=0; i<m_size; i++) {
		int count = 0;
		Node *temp = m_data[i];
		while(temp) {
			count++;
			temp = temp->next;
		}
		if(count >10)
			count = 10;
		hist[count]++;
	}
	for(int i=0; i<n; i++)
		cout<<hist[i]<<endl;
}

template<typename T>
void HashMap<T> :: printKey() {        
	for(int i=0; i<m_size; i++){
		Node *temp = m_data[i];
		while(temp) {
			cout<<temp->key<<endl;
			temp = temp->next;
		}
	}
	
}
