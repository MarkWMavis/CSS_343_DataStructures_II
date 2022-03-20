#include "hashTableEntry.h"
/*
 * Hashtable Entry constructor
 */
hashTableEntry::hashTableEntry(string& key, int& value, hashTableEntry* next)
{
	this->key = key;
	this->vector_index_value = value;
	this->next = next;
}