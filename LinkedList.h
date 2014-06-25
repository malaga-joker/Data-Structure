#include<iostream>
#include<cassert>
#include<string>

using namespace std;

struct ListNode{
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
};

class LinkedList {
public:

	ListNode *head;
	ListNode *tail;

	class iterator;
	friend class iterator;

	class iterator {
		
	    friend class LinkedList;

	private:
		ListNode *nodepointer;
		iterator(const ListNode *setptr) {nodepointer = const_cast<ListNode*> (setptr);}
	public:
		iterator()  {nodepointer = NULL;}

		int& operator*() const  {return (*nodepointer).val;}

		iterator& operator++() {
			nodepointer = nodepointer->next;
			return *this;
		}

		bool operator==(const iterator& it)const {return nodepointer == it.nodepointer;}

		bool operator!=(const iterator& it)const {return nodepointer != it.nodepointer;}
	};

	LinkedList()  {head = NULL; tail = NULL;}

	iterator begin() {
		iterator it(head);
	    return it;
	}

	iterator end() {
		iterator it(NULL);
	    return it;
	}

	void push_back(int);
};


void LinkedList :: push_back(int data) {
	if (head == NULL)
		head = new ListNode(data);
	else {
		ListNode *p = head;
		while (p->next != NULL)
			p = p->next;
		p->next = new ListNode(data);
	}
}

