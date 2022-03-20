#include "hashTable.h"
#include <cmath>
/*
 * Hashtable constructor 
 */
hashTable::hashTable(int size)
{
	this->size = size;							//Initializing the size of the hashTable
	this->hash_table = new hashTableEntry * [size];	//Dynamically allocating a hashTableEntry in the heap of size 100 hashTableEntries
	for (int i = 0; i < size; i++)
	{
		hash_table[i] = nullptr;
	}
}

/*
 * Hashtable destructor responsible for destructing all hashtable entries in the table
 */
hashTable::~hashTable()
{
	//cout << "Hash Table Destructor Called" << endl;
	for (int i = 0; i < size; i++)
	{
		hashTableEntry* cp = hash_table[i];
		while (cp != nullptr)
		{
			hashTableEntry* tp = cp;
			cp = cp->next;
			delete tp;
		}
	}
	delete[] hash_table;
};

unsigned long hashTable::hashFunc(string key)
{
	//
	unsigned long hash = 5381;
	int c;
	for (size_t i = 0; i < key.size(); i++)	//Looping through the string 
	{
		c = key[i];			// Grabbing the Ascii value
		hash = ((hash << 5) + hash) + c; //Bit shifting the hash number 5 times to the left and adding hash value and the ascii value of key[i] 
	}
	return hash;
}

/*
 * Responsible for inserting the hashTableEntry into the hashtable
 */
void hashTable::insert(string key, int value)
{
	//Dividing the hash by the size of the string so that we don't get any indexes above the number of elements in the hashTable
	//and assign that value to the index
	int index = hashFunc(key) % size;
	
	//Create new hashTableEntry that holds the key(movieTitle), the value of the index where the movie is in movies vector inventory, and a
	//null
	hash_table[index] = new hashTableEntry(key, value, hash_table[index]);
}
/*
 * Responsible for converting the title back into the hash_table index value to get the value of vector index that the movie is at in inventory 
 */
int hashTable::find(string movie_title)
{
	const unsigned int hash_table_index = hashFunc(movie_title) % size;			//Turning movie_title into the hashtable index value
	hashTableEntry* table_entry_pointer = hash_table[hash_table_index];			//hashTableEntry Pointer at the the location in the table where
																				//the key, the vector index, and the pointer to the next Entry are
																				//located
	//While the table_entry_pointer is not nullptr, 
	while (table_entry_pointer != nullptr)
	{
		//If the pointers key is equal to the movie title
		if (table_entry_pointer->key == movie_title)
		{
			//Return the vector index value
			return table_entry_pointer->vector_index_value;
		}
		else
		{
			//If not, move to the next hashTableEntry in the chain
			table_entry_pointer = table_entry_pointer->next;
		}
	}

	//Handling an error
	return -1;
}