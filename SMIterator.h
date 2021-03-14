#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	SMIterator(const SortedMap& map);
	const SortedMap& map;
	int currentNode;

	//TODO - Representation

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

