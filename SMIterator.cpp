#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){

	this->currentNode = 0;
}

void SMIterator::first(){

	this->currentNode = this->map.head;
}

void SMIterator::next(){

	if (!valid())
		throw runtime_error{ "Invalid iterator. \n" };
	else {
		this->currentNode = this->map.elements[currentNode].next;
	}

}

bool SMIterator::valid() const{

	return (this->currentNode != NULL_TVALUE);
}

TElem SMIterator::getCurrent() const{

	if (!valid()) {
		throw runtime_error{ "Invalid iterator. \n" };
	}
	else {
		TElem* currentPair = new TElem;
		currentPair->first = this->map.elements[currentNode].info.first;
		currentPair->second = this->map.elements[currentNode].info.second;
		return *currentPair;
	}
	return NULL_TPAIR;
}


