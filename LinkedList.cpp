/*
* File:   LinkedList.cpp
* Author: Alex McGill (40276245)
*
* Last modified 02/04/2017
* Implements the LinkedList class.
*/

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include "linked_list.h"

using namespace std;

//creates an empty list
LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

//creates a list with an initial value to store
LinkedList::LinkedList(int value)
{
	head = new Node;
	head->data = value;
	tail = head;
}

//copy constructor (performs a deep copy)
LinkedList::LinkedList(const LinkedList& rhs)
{
	Node *temp = new Node;
	Node *current = new Node;
	if (rhs.head != nullptr)
	{
		temp = rhs.head;
		// Allocate a new node
		head = new Node;
		// Copy the value from rhs
		head->data = temp->data;
		// Set next to nullptr
		head->next = nullptr;
		// Set the tail of existing list to point to first as the next node
		// Point current to first
		current = head;
		// increment temp to next item in rhs
		temp = temp->next;

		while (temp != nullptr)
		{

			// Allocate new memory for a new node
			current->next = new Node;
			// Point to this new node
			current = current->next;
			// Copy over the data
			current->data = temp->data;
			// By default set the next to null
			current->next = nullptr;
			// Move along rhs list
			temp = temp->next;
		}
	}
	delete temp;
	delete current;
}


//destroys (cleans up) the list
LinkedList::~LinkedList()
{
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		Node *destroy = new Node;
		destroy = temp;
		temp = temp->next;
		delete destroy;
	}
	delete temp;
	head = nullptr;
}

//adds a value to the head of the list
void LinkedList::push(int value)
{
	Node *temp = new Node;
	temp->data = value;
	temp->next = head;
	head = temp;
	delete temp;
}

//gets the last element from the list, without removing it
//requires: list not empty
int LinkedList::peekTail()
{
	// Make sure tail is not equal to nullptr
	assert(tail != nullptr);
	
	return tail->data;
}

//prints the list in order from head to tail
string LinkedList::toString() const
{
	string str = string();
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		// Convert and add temp data to the string str
		str += to_string(temp->data);
		// Check that temp isn't the last node
		if (temp->next != nullptr)
		{
			str += " ";
		}
		temp = temp->next;
	}
	delete temp;
	return str;
}

//removes and returns the value at the head of the list
//requires: list not empty
int LinkedList::pop()
{
	assert(head != nullptr);
	Node *temp = new Node;
	int value = 0;

	temp = head;

	if (temp != nullptr)
	{
		value = head->data;
		// Set head to the 2nd node in the list
		head = head->next;
	}
	delete temp;
	return value; 
}

//adds a value to the end of the list
void LinkedList::append(int value)
{
	Node *last = new Node;
	last->data = value;
	last->next = nullptr;
	if (head != nullptr && tail != nullptr)
	{
		tail->next = last;
		tail = last;
	}
	else
	{
		head = last;
		tail = last;
	}
	delete last;
}

//appends the deep copies of the nodes of rhs on to the end of this list
void LinkedList::appendList(const LinkedList& rhs)
{
	Node *temp = new Node;
	Node *current = new Node;
	Node *first = new Node;
	if (rhs.head != nullptr)
	{
		temp = rhs.head;

		// Copy the value from rhs
		first->data = temp->data;
		// Set next to nullptr
		first->next = nullptr;
		// Set the tail of existing list to point to first as the next node
		tail->next = first;
		// Point current to first
		current = first;
		// increment temp to next item in rhs
		temp = temp->next;

		while (temp != nullptr)
		{
			// Allocate new memory for a new node
			current->next = new Node;
			// Point to this new node
			current = current->next;
			// Copy over the data
			current->data = temp->data;
			// By default set the next to null
			current->next = nullptr;
			// Move along rhs list
			temp = temp->next;
		}
	}
	delete temp;
	delete current;
	delete first;
}

//inserts a value immediately after the first occurrence of afterValue,
//if afterValue is not in the list then inserts at the tail
void LinkedList::insertAfter(int value, int afterValue)
{
	Node *temp = new Node;
	// aim is the new node that will be inserted
	Node *aim = new Node;
	// found is a flag to make sure it doesnt insert more than once
	int found = 0;
	aim->data = value;
	temp = head;
	while (temp != nullptr && found == 0)
	{
		if (temp->data == afterValue)
		{
			aim->next = temp->next;
			temp->next = aim;
			found = 1;
		}
		temp = temp->next;
	}
	if (found == 0)
	{
		tail->next = aim;
		aim->next = nullptr;
	}
	delete temp;
	delete aim;
}


//removes all occurrences of value from the list
void LinkedList::removeAllOccurences(int value)
{
	Node *prev = new Node;
	Node *current = new Node;

	prev = nullptr;
	current = head;
	// When first node is the value
	while (current != nullptr && current->data == value)
	{
		prev = current;
		current = current->next;
		head = current;
		delete prev;
	}
	// When the first node isn't the value..
	while (current != nullptr)
	{
		if (current->data == value)
		{
			prev->next = current->next;
			delete current;
			current = prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	delete prev;
	delete current;
}

//reverses the list
void LinkedList::reverse()
{
	Node *prev = new Node;
	Node *current = new Node;
	Node *next = new Node;

	prev = nullptr;
	current = head;
	while (current != nullptr)
	{
		// Switch the values
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	delete prev;
	delete current;
	delete next;
}

//checks if two lists are equal in state (contain the same values in the same order)
bool LinkedList::operator ==(const LinkedList& other) const
{

	Node *list1 = new Node;
	Node *list2 = new Node;

	list1 = head;
	list2 = other.head;

	// As long as each list has data
	while (list1 != nullptr && list2 != nullptr)
	{
		// Check if the data values are not equal
		if (list1->data != list2->data)
		{
			return false;
		}
		list1 = list1->next;
		list2 = list2->next;
	}

	// Check if both lists have the same size
	if (list1 == nullptr && list2 == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
	delete list1;
	delete list2;
}

//checks if two lists are not equal in state
bool LinkedList::operator !=(const LinkedList& other) const
{
	Node *list1 = new Node;
	Node *list2 = new Node;

	list1 = head;
	list2 = other.head;

	// As long as each list has data
	while (list1 != nullptr && list2 != nullptr)
	{
		// Check if the data values are equal
		if (list1->data != list2->data)
		{
			return true;
		}
		list1 = list1->next;
		list2 = list2->next;
	}
	// Check if both lists have the same size
	if (list1 == nullptr && list2 == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
	delete list1;
	delete list2;
}

//pushes a new value onto the head of the list
LinkedList& LinkedList::operator +(int value)
{
	// Call the push method on this
	this->push(value);
	return *this;
}

//copy assignment operator (performs a deep copy)
LinkedList& LinkedList::operator =(const LinkedList& rhs)
{
	// Create a new linked list
	LinkedList *newList = new LinkedList();
	Node *temp = new Node;
	temp = rhs.head;
	while (temp != nullptr)
	{
		// Call the append method on the new list using the data from temp
		newList->append(temp->data);
		temp = temp->next;
	}
	delete temp;

	this->head = newList->head;
	return *this;
}

//pushes values from an input stream onto the front of the list
std::istream& operator >> (std::istream &in, LinkedList &value)
{
	Node *temp = new Node;
	int val;
	// While the in stream isn't empty..
	while (!in.eof())
	{
		// Set val as the input and remove any whitespace
		in >> val >> ws;
		if (in.fail())
		{
			break;
		}
		value.push(val);
	}
	delete temp;
	return in;
}

//writes the values, in order, to an output stream
std::ostream& operator<<(std::ostream &out, const LinkedList &value)
{
	Node *temp = new Node;
	string str = string();
	temp = value.head;

	while (temp != nullptr)
	{
		out << temp->data;
		if (temp->next != nullptr)
		{
			out << " ";
		}
		temp = temp->next;
	}
	delete temp;
	return out;
}
