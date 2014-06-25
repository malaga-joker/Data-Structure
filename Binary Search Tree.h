template <class T>
class BinarySearchTree {

protected: struct Node;
public:

BinarySearchTree() { 
	root = new Node;	
	root->left = 0;
	root->right = 0;
}

bool Member(const T &a) const { return (Member(a, root)); }

void Insert(const T &a) { Insert(a, root); }

void Delete(const T &a) { Delete(a, root); }

T DeleteMin() { return (DeleteMin(root)); }

bool IsEmpty() const {return root == 0; }

private:

bool Member(const T &a, Node *p) const;

void Insert(const T &a, Node * &p);

void Delete(const T &a, Node * &p);

T DeleteMin(Node * &p);

protected:

struct Node {
	T key;
	Node *left, *right;
	Node() {
		left = right = 0;
	}
	Node(const T &a) : key(a),left(0),right(0) {}
};

Node *root;
}; 


template <class T>
bool BinarySearchTree<T>:: Member(const T &x, Node *nodePtr) const {
	if (nodePtr == 0)
		return false; 
	else if (x == nodePtr->key)
		return true;
	else if (x < nodePtr->key)
		return ( Member(x, nodePtr->left));
	else
		return (Member(x, nodePtr->right));
}


template <class T> 
void BinarySearchTree<T>:: Insert(const T &x, Node * &nodePtr)  {
	Node *newnodePtr;
	if (nodePtr == 0) {
		newnodePtr = new Node(x);
		nodePtr = newnodePtr; 
	}
	else if (x <= nodePtr->key)
		Insert(x, nodePtr->left);
	else if (x > nodePtr->key)
		Insert(x, nodePtr->right);
}


template <class T> 
T BinarySearchTree<T>:: DeleteMin(Node * &nodePtr) {
   T min;
   Node *temp;
	if(nodePtr->left == 0) {
		min = nodePtr->key;
		temp = nodePtr;
		nodePtr = nodePtr->right;
		delete temp;
		return min;
	}
	else 
		return DeleteMin(nodePtr->left);
}


template <class T> 
void BinarySearchTree<T>::Delete(const T &x, Node * &nodePtr) {
   Node *temp;
   if (nodePtr != 0) {
     if (x < nodePtr->key)
		Delete(x, nodePtr->left);
     else if (x > nodePtr->key)
		Delete(x, nodePtr->right);
     else if (nodePtr->left == 0) {
		temp = nodePtr;
		nodePtr = nodePtr->right;
		delete temp;
    }
     else if (nodePtr->right == 0) {
		temp = nodePtr;
		nodePtr = nodePtr->left;
		delete temp;
    }
     else  
		nodePtr->key = DeleteMin(nodePtr->right);
   }
}
