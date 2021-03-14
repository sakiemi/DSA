#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {

	this->rel = r;
	this->head = NULL_TVALUE;
	this->tail = NULL_TVALUE;
	this->numberOfElements = 0;
	this->firstEmpty = 0;
	this->elements = new Node[100];
	for (int i = 0; i < 100; ++i)
		this->elements[i].info.first = NULL_TVALUE;
}

TValue SortedMap::add(TKey k, TValue v) {

	int currentNode = this->head;
	Node newNode;
	newNode.info.first = k;
	newNode.info.second = v;

	if (this->head == NULL_TVALUE) {			// no elements in the map 
		newNode.previous = NULL_TVALUE;
		newNode.next = NULL_TVALUE;
		this->head = 0;
		this->tail = 0;
		elements[0] = newNode;
		this->numberOfElements++;
		return "";
	}

	while (currentNode != NULL_TVALUE && rel(elements[currentNode].info.first, k) == true) {		// we search where we should add the new node

		if (elements[currentNode].info.first == k) {	// we find an element with the same key
			TValue oldValue = elements[currentNode].info.second;
			elements[currentNode].info.second = v;		// we replace the old value with the new one
			return oldValue;							// we return the old value
		}

		currentNode = elements[currentNode].next;
	}

	this->firstEmpty = getFirstEmpty();

	if (currentNode == NULL_TVALUE) {			// we replace the tail
		this->elements[tail].next = firstEmpty;
		newNode.previous = this->tail;
		newNode.next = NULL_TVALUE;
		this->tail = firstEmpty;
		this->elements[firstEmpty] = newNode;
		this->numberOfElements++;
		return "";
	}

	if (currentNode == this->head) {		// we replace the head
		this->elements[head].previous = firstEmpty;
		newNode.next = this->head;
		newNode.previous = NULL_TVALUE;
		this->head = firstEmpty;
		this->elements[firstEmpty] = newNode;
		this->numberOfElements++;
		return "";
	}

	newNode.previous = elements[currentNode].previous;		// we add somewhere between head and tail
	newNode.next = currentNode;
	elements[firstEmpty] = newNode;

	this->elements[elements[currentNode].previous].next = firstEmpty;
	elements[currentNode].previous = firstEmpty;

	this->numberOfElements++;
	return "";
}

TValue SortedMap::search(TKey k) const {

	int currentNode = this->head;

	while (currentNode != NULL_TVALUE) {
		if (elements[currentNode].info.first == k)
			return elements[currentNode].info.second;
		currentNode = elements[currentNode].next;
	}

	return "";
}

TValue SortedMap::remove(TKey k) {

	if (this->head == NULL_TVALUE)
		return "";

	int currentNode = this->head;

	while (currentNode != NULL_TVALUE && elements[currentNode].info.first != k)
		currentNode = elements[currentNode].next;

	if (currentNode == NULL_TVALUE)				// we didn't find they key to be removed so we return NULL_TVALUE
		return "";


	if (currentNode == this->head) {		// remove the head
		if (elements[currentNode].next != NULL_TVALUE)
			elements[elements[currentNode].next].previous = NULL_TVALUE;
		this->head = elements[currentNode].next;
		elements[currentNode].info.first = NULL_TVALUE;
		this->numberOfElements--;
		return elements[currentNode].info.second;
	}

	if (currentNode == this->tail) {		// remove the tail
		if (elements[currentNode].previous != NULL_TVALUE)
			elements[elements[currentNode].previous].next = NULL_TVALUE;
		this->tail = elements[currentNode].previous;
		elements[currentNode].info.first = NULL_TVALUE;
		this->numberOfElements--;
		return elements[currentNode].info.second;
	}

	elements[elements[currentNode].next].previous = elements[currentNode].previous;		// we remove somewhere between head and tail
	elements[elements[currentNode].previous].next = elements[currentNode].next;
	elements[currentNode].info.first = NULL_TVALUE;
	this->numberOfElements--;
	return elements[currentNode].info.second;
}

int SortedMap::size() const {
	
	return this->numberOfElements;
}

bool SortedMap::isEmpty() const {

	return (this->numberOfElements == 0);
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

int SortedMap::getFirstEmpty()
{
	for (int i = 0; i < 100; ++i)
		if (this->elements[i].info.first == NULL_TVALUE)
			return i;
	return -1;
}

SortedMap::~SortedMap() {

	delete[] elements;

}
