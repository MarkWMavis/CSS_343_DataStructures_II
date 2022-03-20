#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>

using namespace std;

class transaction
{
	string action;
	int customerIDNumber;
	string typeOfMedia;
	string movieTitle;

	friend class inventory;
	
public:
	friend ostream& operator<<(ostream& os, const transaction& t);
	transaction();
	transaction(string action, int customerIDNumber, string typeOfMedia, string movieTitle);
	~transaction();
};

#endif