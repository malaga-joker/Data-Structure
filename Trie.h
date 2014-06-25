#include<iostream>
#include<string>

#define size 26
using namespace std;

class Trie{
private:
	struct Node{
		  Node* children[size];
	    bool  mark;
	    Node() : mark(false) {
			for(int i = 0; i < size; i++) 
				children[i] = NULL;
		}
	};
	Node *root;

	Node* createNode() {
		  Node* node = new Node();
	    return node;
	}
	
	void destroy(Node *root) {
		if(root != NULL) {
        for(int i=0; i<size; i++) {
				  if(root->children[i]) 
				    destroy(root->children[i]);
		    }
		delete root;
		root = NULL;
	  }
	}

public:
	Trie() {root = createNode();}
	~Trie();
	void insert(string);
	bool search(string);
	void clear() { destroy(root);}  // for deubging 
};


Trie :: ~Trie() {
	destroy(root);
}

void Trie :: insert(string str) {
	int len = str.length();
	Node *p = root;
	int c;
	for(int i=0; i<len; i++) {
		c = str[i]-'a';
		if(p->children[c] == NULL){
			p->children[c] = createNode();
		}
		p = p->children[c];
	}
	p->mark = true;
}

bool Trie :: search(string str) {
	int len = str.length();
	Node *p = root;
	int c;
	for(int i=0; i<len; i++) {
		c = str[i] - 'a';
		if(p->children[c] == NULL){
			return false;
		}
		p = p->children[c];
	}
	if(p->mark == true)
	    return true;
	else
		return false;
}


