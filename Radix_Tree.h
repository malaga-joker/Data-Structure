#include<iostream>
#include<string>
using namespace std;

class RNode {
private:
	friend class RadixTree;
	int bit_number;
	char  *key;
	string data;
	RNode *left;
	RNode *right;
public:
	RNode();
	RNode(char*, string, int, RNode*, RNode*);
	~RNode();
	void   initial(char*, string, int, RNode*, RNode*);
	string getData();
	void   setData(string);
	string getKey();
	RNode* getLeft();
	RNode* getRight();
};

//--------------------------------------------------------------------------------

class RadixTree {
private:
	RNode *root;
private:
	int    getbit_number(char*, int);
	int    first_different_bit_number(char*, char*);
	bool   key_compare(char*, char*);
	void   key_copy(RNode*, RNode*);
	RNode *search(char*);
	void   remove(RNode*);
public:
	RadixTree();
	~RadixTree();
	RNode *insert(char*,string);
	string find(char*);
	bool   Delete(char*);
};

//-----------------------------------------------------------------------------------

void RNode :: initial(char *key, string data, int bit_number, RNode *left, RNode *right) {
	this->key = key;
	this->data = data;
	this->bit_number = bit_number;
	this->left = left;
	this->right = right;
}

RNode :: RNode() {
	initial("","",-1,this,this);
}

RNode :: RNode(char *key, string data, int bit_number, RNode *left, RNode *right) {
	initial(key, data, bit_number, left, right);
}

RNode :: ~RNode() {
}

string RNode :: getData() {
	return data;
}

void RNode :: setData(string str) {
	data = str;
}

string RNode :: getKey() {
	return key;
}

RNode* RNode :: getLeft() {
	return left;
}

RNode* RNode :: getRight() {
	return right;
}

//-------------------------------------------------------------------------------------

RadixTree :: RadixTree() {
	root = new RNode();
}

RadixTree :: ~RadixTree() {
	remove(root);
}

int RadixTree :: getbit_number(char* key, int n) {
	if (n < 0) return 2; 
    int k = (n & 0x7);
    return ( (*(key + (n >> 3))) >> k) & 0x1;
}

bool RadixTree :: key_compare(char *key1, char *key2) {
	if(!key1 || !key2)
		return false;
	return strcmp(key1,key2) == 0;
}

void RadixTree :: key_copy(RNode *src, RNode *dest) {
	if(src == dest)
		return;
	if (strlen(dest->key) < strlen(src->key))
                dest->key = (char*) realloc(dest->key, 1 + strlen(src->key));
        strcpy(dest->key, src->key);
		dest->data = src->data;
}

int RadixTree :: first_different_bit_number(char *key1, char *key2) {
	if(!key1 || !key2)
		return 0;
        int n = 0;
        int d = 0;
        while ( (key1[n] == key2[n]) && (key1[n] != 0) && (key2[n] != 0) )
                n++;
        while (getbit_number(&key1[n], d) == getbit_number(&key2[n], d))
                d++;
        return ((n << 3) + d);
}

RNode* RadixTree :: insert(char *key, string data) {
	RNode *p, *t, *x;
	p = root;
	t = root->right;
	while(p->bit_number < t->bit_number) {
		p = t;
		t = getbit_number(key, t->bit_number) ? t->right : t->left;
	}
	if(key_compare(key,t->key))
	    return NULL;
	int index = first_different_bit_number(key,t->key);
	p = root;
	x = p->right;
	while((p->bit_number < x->bit_number) && (x->bit_number < index)) {
		p = x;
		x = getbit_number(key, x->bit_number) ? t->right : t->left;
	}
	t = new RNode();
	t->initial(key, data, index, (getbit_number(key, index) ? x : t), 
		(getbit_number(key, index) ? t : x));

	if (getbit_number(key, p->bit_number))
                p->right = t;
    else
                p->left = t;
    
	return t;
}

RNode* RadixTree :: search(char *key) {
	RNode *p, *q;
	p = root;
	q = root->right;
	while(p->bit_number < q->bit_number) {
		p = q;
		q = getbit_number(key,q->bit_number) ? q->right : q->left;
	}
	if(!key_compare(key,q->key))
		return NULL;
	return q;
}

string RadixTree :: find(char *key) {
	RNode *result = search(key);
	if(!result) {
		return "key is not in the dectionary, result ont found!";
	}
	else
		return result->data;
}

void RadixTree :: remove(RNode *ptr) {
	RNode *left = ptr->left;
	RNode *right = ptr->right;
	if( (left->bit_number >= ptr->bit_number) && (left != ptr) && (left != root)) 
		remove(left);
	if( (right->bit_number >= ptr->bit_number) && (right != ptr) && (right != root)) 
		remove(right);
	delete ptr;
}
