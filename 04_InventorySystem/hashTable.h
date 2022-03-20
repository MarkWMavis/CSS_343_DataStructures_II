#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <ostream>
#include <iostream>
#include "hashTableEntry.h"
using namespace std;
class hashTable
{
	int size;
	hashTableEntry** hash_table;

public:
	hashTable(int size);
	~hashTable();

	unsigned long hashFunc(string key);
	void insert(string key, int value);
	int find(string key);
};
#endif

