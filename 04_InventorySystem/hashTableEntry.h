#ifndef HASHTABLEENTRY_H
#define HASHTABLEENTRY_H
#include <string>
using namespace std;

class hashTableEntry
{
	string key;
	int vector_index_value;
	hashTableEntry* next;

	friend class hashTable;

public:
	hashTableEntry(string& key, int& value, hashTableEntry* next);
};

#endif

