/*************************************************************************
 * AUTHOR     : Matin Ghaffari
 * HW #03     : SLL Cycles
 * CLASS      : CS 1D
 * DATE       : 9/24/19
 * SECTION    : T-TH : 5:00-7:20
 *************************************************************************/

#include <iostream>

using namespace std;

struct Node {
	int data;
	Node *next;
};

class SinglyList {
	int count;
	Node *head;

public:
	// Default constructor
	SinglyList(): count{0}, head{nullptr} {}

	// Alternate constructor
	SinglyList(int cap);

	// Copy constructor
	SinglyList(const SinglyList &rhs);

	// Move constructor
	SinglyList( SinglyList &&rhs);

	// Destructor
	~SinglyList();

	// Overloaded copy assignment operator
	const SinglyList& operator=(const SinglyList& rhs);

	// Move assignment operator
	const SinglyList& operator=( SinglyList&& rhs);

	void AddToFront(int _data);

	Node *detectCycle(Node *head);

	Node* getNode(int pos);

	friend ostream& operator<<(ostream & os, const SinglyList &rhs);

};

// Copy constructor which has Lvalue parameter, which requires memory allocation
// Time complexity - O(n)     Space complexity - O(n)
SinglyList::SinglyList(const SinglyList &rhs)
: count{rhs.count},head{rhs.head} {

	cout << "\n\n*** Invoking the copy constructor ***\n\n";

	Node *temp = rhs.head;
	Node *curr = new Node;

	head = curr;
	while (temp != nullptr)
	{
		curr->data = temp->data;
		temp = temp->next;
		if (temp != nullptr)
		{
			curr->next = new Node;
			curr = curr->next;
		}
		else
			curr->next = nullptr;
	}
}

// Move constructor which has a Rvalue parameter, to prevent unnecessary
// memory allocation
// Time complexity - O(1)     Space complexity - O(1)
SinglyList::SinglyList( SinglyList &&rhs)
: count{rhs.count},head{rhs.head} {

	cout << "\n\n*** Invoking the move constructor ***\n\n";

	rhs.count = 0;
	rhs.head = nullptr;
}

// Destructor
// Time complexity - O(n)     Space complexity - O(n)
SinglyList:: ~SinglyList() {

	Node *curr;
	Node *temp;

	curr =head;

	while(curr != nullptr)
	{
		temp =curr;
		curr= curr->next;
		delete temp;
	}
	temp = nullptr;
}

// Overloaded copy assignment operator which has a Lvalue parameter which
// requires memory allocation to be assigned
// Time complexity - O(n)      Space complexity - O(n)
const SinglyList& SinglyList::operator=(const SinglyList& rhs) {

	cout << "\n\n*** Invoking the copy assignment ***\n";

	Node *newNode;
	Node *curr;
	Node *last;

	// Avoiding self assignment
	if(this != &rhs)
	{
		if(head != NULL)
		{
			Node *temp;
			curr =head;

			while(head != nullptr)
			{
				temp =curr;
				curr= curr->next;
				delete temp;
			}
		}

		if(rhs.head == nullptr)
			head = nullptr;
		else
		{
			curr = rhs.head;

			//copying the first element
			head = new Node;
			head->data = curr->data;
			head->next = nullptr;
			last = head;
			curr = curr->next;

			//copy the remaining elements
			while(curr != nullptr)
			{
				newNode = new Node;
				newNode->data = curr->data;
				newNode->next = nullptr;
				last->next = newNode;
				last = newNode;
				curr = curr->next;
			}
		}
	}
	return *this;
}

// Move assignment operator which has a Rvalue parameter to move data without
// unnecessary memory allocation
// Time complexity - O(1)       Space complexity - O(1)
const SinglyList& SinglyList::operator=( SinglyList&& rhs) {

	cout << "\n\n*** Invoking the move assignment ***\n";

	// Avoiding self assignment
	if (this != &rhs) {

		count = rhs.count;
		head = rhs.head;

		rhs.head = nullptr;
		rhs.count = 0;
	}
	return *this;
}

// Time complexity - O(1)       Space complexity - O(1)
void SinglyList::AddToFront(int _data) {

	cout << "\nAdding "<<_data <<" to the front\n";

	Node *p = new Node;

	p->next =nullptr ;
	p->data = _data;
	count++;

	p->next =head ;

	head = p;
	p =nullptr;
}

// Time complexity - O(n^2)       Space complexity - O(n)
Node* SinglyList::detectCycle(Node *head) {
	Node* fast = head;
	Node* slow = head;

	while(slow!=nullptr && fast!=nullptr && fast->next != nullptr)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(fast != slow) {
			slow = head;
			while(slow == fast) {
				fast = fast->next;
				slow = slow->next;
			}
			return slow;
		}
	}
	return nullptr;
}

// Time complexity - O(n)       Space complexity - O(n)
 Node* SinglyList::getNode(int pos) {
	 Node* temp = nullptr;
	 Node* tempHead =  head;
	if (pos < 0)
	{
		cout << "\n*** Invalid negative position *** \n";
		return nullptr;
	}
	if  (pos > count)
	{
		cout << "\n*** Invalid position, size exceeded *** \n";
		return nullptr;
	}
	else
	{
		for (int i = 0 ;  i < pos; ++i)
		{

			temp = tempHead->next;
			delete tempHead;
			tempHead = temp;
		}
		head = tempHead;
		temp =nullptr;
		tempHead =nullptr;
		return head;
	}
 }

 // Time complexity - O(n)       Space complexity - O(n)
 ostream& operator<<(ostream & os, const SinglyList &rhs) {
	 Node *p = rhs.head;
	 cout << " \n\n*******  Printing the list  ******\n\n";
	 while(p){
		 os << p->data << "\n";
		 p = p->next;
	 }
	 return os;
 }

int main() {

    // console header
	cout << endl;
	cout << "**************************************************** \n";
	cout << "*        Running CS1D HW03 SLL Cycles              * \n";
	cout << "*         Programmed by Matin Ghaffari             * \n";
	cout << "*              T-TH : 5:00-7:20                    * \n";
	cout << "*                   9/24/19                        * \n";
	cout << "**************************************************** \n";
	cout << endl;

	SinglyList obj;

	obj.AddToFront(2);
	obj.AddToFront(4);
	obj.AddToFront(5);
	obj.AddToFront(7);
	obj.AddToFront(9);
	obj.AddToFront(10);
	obj.AddToFront(12);

	cout << obj;
	cout << " \n\n-----------------------------------------------------\n\n";

	// Instantiating another object to test the copy constructor
	SinglyList obj1 = obj;

	cout << obj1;

	cout <<endl;

	// Instantiating another object to test the move constructor
	SinglyList obj2 = move(obj1);

	cout << obj2;

	obj2.AddToFront(9);
	cout << obj2;

	// Instantiating another object to test the copy assignment
	SinglyList obj3;

	obj3 = obj2;
	cout << obj3;

	obj3.AddToFront(8);
	cout << obj3;

	// Instantiating another object to test the move assignment
	SinglyList obj4;

	obj4 = move(obj3);
	cout << obj4;


	cout << "\n\n------- DETECT CYCLE Test case 1 -------- \n\n" ;
	SinglyList obj5;
	obj5.AddToFront(-4);
	obj5.AddToFront(0);
	obj5.AddToFront(2);
	obj5.AddToFront(3);

	cout << obj5;

	int position = 1;

	Node* result = obj5.detectCycle(obj5.getNode(position));

	if (result == nullptr)
	{
		cout << "\nNo cycle \n";
	}
	else
		cout << "\nTail connects to node index " << position<< endl;

	cout << obj5;


	cout << "\n\n------- DETECT CYCLE Test case 2 -------- \n\n" ;

	SinglyList obj6;
	obj6.AddToFront(2);
	obj6.AddToFront(1);

	cout << obj6;

	int position1 = 0;

	Node* result1 = obj6.detectCycle(obj6.getNode(position1));

	if (result1 == nullptr)
	{
		cout << "\nNo cycle \n";
	}
	else
		cout << "\nTail connects to node index " << position1<< endl;

	cout << obj6;


	cout << "\n\n------- DETECT CYCLE Test case 3 -------- \n\n" ;

	SinglyList obj7;
	obj7.AddToFront(1);

	cout << obj7;

	int position2 = -1;

	Node* result2 = obj7.detectCycle(obj7.getNode(position2));

	if (result2 == nullptr)
	{
		cout << "\nNo cycle \n";
	}
	else
		cout << "\nTail connects to node index " << position2<< endl;

	cout << obj7;


	cout << "\n\n" ;

	return 0;

}
